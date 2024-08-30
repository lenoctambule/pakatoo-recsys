#include "interface/SocketIPC.hpp"

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