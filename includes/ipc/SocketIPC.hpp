#pragma once

# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/fcntl.h>
# include <unistd.h>
# include <poll.h>
# include "interface/Shell.hpp"

# define BUFFSIZE 65536

typedef struct s_client
{
    Request     req;
    std::string resp;
    sockaddr_in addr;
    int         fd;
} t_client;

class SocketIPC
{
    private :
        Shell                   _shell;
        std::string             _ip;
        ushort                  _port;
        int                     _socket;
        sockaddr_in             _addr;
        std::vector<pollfd>     _cfds;
        std::deque<t_client>    _reqs;

        SocketIPC();
        SocketIPC(SocketIPC const &a);
        SocketIPC   &operator=(SocketIPC const &a);

        int         init_server();
        int         init_sockaddr();
        void        loop();
        void        accept_client();
        void        disconnect_client(size_t id);

    public :
        SocketIPC(std::string ip, ushort port);
        ~SocketIPC();

        void        start_server();
};