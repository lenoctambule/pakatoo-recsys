#include "ipc/SocketIPC.hpp"

SocketIPC::~SocketIPC()
{
}

int SocketIPC::init_server()
{
    int optval = 1;

    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket < 0)
        return 0;
    if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int)) < 0)
        return 0;
    if (bind(_socket, (sockaddr *)&_addr, sizeof(_addr)) < 0)
        return 0;
    if (fcntl(_socket, F_SETFD, FD_CLOEXEC) < 0)
		return 0;
    return 1;
}

int SocketIPC::init_sockaddr()
{
    _addr.sin_family        = AF_INET;
    _addr.sin_port          = htons(_port);
    return inet_pton(AF_INET, _ip.c_str(), &(_addr.sin_addr));
}

SocketIPC::SocketIPC(std::string ip, ushort port) :
    _ip(ip),
    _port(port)
{
    if (!init_sockaddr())
        throw std::runtime_error("Invalid IP.");
    if (!init_server())
        throw std::runtime_error("Socket initialization failed.");
}

void    SocketIPC::accept_client()
{
    int fd;
    sockaddr_in addr;
    socklen_t   addr_len;

    fd = accept(_socket, (sockaddr *)&addr, &addr_len);
    if (fd < 0)
        return ;
    if (fcntl(fd, F_SETFD, FD_CLOEXEC) < 0)
        close(fd);
    _reqs.push_back(t_client{.req=Request(),
                            .addr=addr,
                            .fd=fd});
    _cfds.push_back(pollfd{.fd=fd,
                            .events=POLLIN,
                            .revents=0});
}

void    SocketIPC::disconnect_client(size_t id)
{
    close(_cfds[id].fd);
    _cfds.erase(_cfds.begin() + id);
    _reqs.erase(_reqs.begin() + id - 1);
}

void    SocketIPC::loop()
{
    char    chunk[BUFFSIZE];
    ssize_t rd_len;
    ssize_t wr_len;

    while (poll(_cfds.data(), _cfds.size(), 0) >= 0)
    {
        if (_cfds[0].revents & POLLIN)
            accept_client();
        for (size_t i = 1; i < _cfds.size(); i++)
        {
            if (_cfds[i].revents & POLLIN)
            {
                rd_len = recv(_cfds[i].fd, chunk, BUFFSIZE, 0);
                if (rd_len <= 0)
                    disconnect_client(i);
                _reqs[i-1].req.receive_chunk(chunk, rd_len);
                if (_reqs[i-1].req.isFinished())
                    _reqs[i-1].resp = _shell.handle_request(_reqs[i-1].req);
            }
            else if (_cfds[i].revents & POLLOUT)
            {
                wr_len = send(_cfds[i].fd, _reqs[i-1].resp.c_str(), BUFFSIZE, 0);
                if (wr_len <= 0 && _reqs[i-1].req.trunc_sent(wr_len) == true)
                    disconnect_client(i);
            }
        }
    }
}

void    SocketIPC::start_server()
{
    if (listen(_socket, 100) < 0)
    {
        close(_socket);
        throw std::runtime_error("Socket listen failed");
    }
    _cfds.push_back(pollfd{.fd=_socket, .events=POLLIN, .revents=0});
    loop();
}