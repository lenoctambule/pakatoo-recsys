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
    socklen_t   addr_len = sizeof(addr);

    fd = accept(_socket, (sockaddr *)&addr, &addr_len);
    std::cerr << "Accepted client fd=" << fd << std::endl;
    if (fd < 0)
        return ;
    if (fcntl(fd, F_SETFD, FD_CLOEXEC) < 0)
        close(fd);
    _clients.push_back(Client(fd, _shell));
    _cfds.push_back(pollfd{.fd=fd,
                            .events=POLLIN | POLLOUT,
                            .revents=0});
}

void    SocketIPC::disconnect_client(size_t id)
{
    std::cerr << "Disconnected client fd=" << _cfds[id].fd << std::endl;
    close(_cfds[id].fd);
    _cfds.erase(_cfds.begin() + id);
    _clients.erase(_clients.begin() + id - 1);
}

void    SocketIPC::loop()
{
    while (poll(_cfds.data(), _cfds.size(), 0) >= 0)
    {
        if (_cfds[0].revents & POLLIN)
            accept_client();
        for (size_t i = 1; i < _cfds.size(); i++)
        {
            if (_cfds[i].revents & POLLIN && _clients[i-1].status() == Receiving)
                _clients[i-1].receive();
            else if (_cfds[i].revents & POLLOUT && _clients[i-1].status() == Responding)
                _clients[i-1].respond();
            if (_clients[i-1].status() == Done)
                disconnect_client(i);
        }
    }
}

void    SocketIPC::start_server()
{
    if (listen(_socket, 1024) < 0)
    {
        close(_socket);
        throw std::runtime_error("Socket listen failed");
    }
    _cfds.push_back(pollfd{.fd=_socket, .events=POLLIN, .revents=0});
    loop();
}