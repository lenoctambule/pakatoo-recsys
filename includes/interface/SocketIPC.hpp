#pragma once

# include <sys/socket.h>
# include "interface/Shell.hpp"

class SocketIPC
{
    private :
        std::string _ip;
        Shell       _shell;
        ushort      _port;
        Shell       _shell;

        SocketIPC();
        SocketIPC(SocketIPC const &a);
        SocketIPC   &operator=(SocketIPC const &a);

    public :
        SocketIPC(std::string _ip, ushort port);
        ~SocketIPC();

        void    start_server();
};