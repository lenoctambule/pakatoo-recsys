#include "ipc/Client.hpp"

Client::Client(int fd, Shell &shell) :
    _shell(shell),
    _status(Receiving),
    _fd(fd),
    _start(time(0))
{

}

Client::Client(Client const &a) :
    _shell(a._shell),
    _req(a._req),
    _status(a._status),
    _fd(a._fd),
    _start(time(0))
{
}

Client  &Client::operator=(Client const &a)
{
    _req    = a._req;
    _status = a._status;
    _fd     = a._fd;
    _start  = a._start;

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
    {
        _resp   = _shell.handle_request(_req);
        _status = Responding;
    }
}

void    Client::respond()
{
    ssize_t             len;

    len = send(_fd, _resp.c_str(), _resp.size(), 0);
    if (len <= 0)
    {
        _status = Done;
        return ;
    }
    _resp.erase(0, len);
    if (_resp.size() == 0)
        _status = Done;
}

t_clientstate    Client::status() {
    if (difftime(time(0), _start) > TIMEOUT)
       _status = Done;
    return _status;
}