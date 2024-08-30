#pragma once

# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/fcntl.h>
# include "interface/Shell.hpp"

class SocketIPC
{
    private :
        Shell       _shell;
        std::string _ip;
        ushort      _port;
        int         _socket;
        sockaddr_in _addr;

        SocketIPC();
        SocketIPC(SocketIPC const &a);
        SocketIPC   &operator=(SocketIPC const &a);

        int         init_server();
        int         init_sockaddr();

    public :
        SocketIPC(std::string _ip, ushort port);
        ~SocketIPC();

        void    start_server();
};