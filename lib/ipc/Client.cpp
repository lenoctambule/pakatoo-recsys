#include "ipc/Client.hpp"

Client::Client(int fd, int lfd) :
    _fd(fd),
    _lfd(lfd)
{

}

Client::Client(Client const &a) :
    _req(a._req),
    _status(a._status),
    _fd(a._fd),
    _lfd(a._lfd)
{
}

Client  &Client::operator=(Client const &a)
{
    _req    = a._req;
    _status = a._status;
    _fd     = a._fd;
    _lfd    = a._lfd;

    return *this;
}

Client::~Client()
{

}

void    Client::receive()
{
    char    chunk[BUFFSIZE];

    ssize_t rd_len = recv(_fd, chunk, BUFFSIZE, 0);
    if (rd_len <= 0)
    {
        _status = Done;
        return ;
    }
    _req.receive_chunk(chunk, rd_len);
    if (_req.isFinished())
        _status = Responding;
}

void    Client::respond()
{
    const std::string   raw = _req.get_raw();
    ssize_t             len;

    len = send(_fd, raw.c_str(), raw.size(), 0);
    if (len <= 0)
    {
        _status = Done;
        return ;
    }
    _req.trunc_sent(len);
    if (_req.get_raw().size() == 0)
    {
        _status = Done;
        std::cout << _req << std::endl;
        return ;
    }
}

t_clientstate    Client::status() {
    return _status;
}