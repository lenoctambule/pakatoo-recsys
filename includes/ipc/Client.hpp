#pragma once

# include "ipc/Request.hpp"
# include "interface/Shell.hpp"
# include <sys/socket.h>

# define BUFFSIZE 65536
# define TIMEOUT 1000

typedef enum e_clientstate
{
    Receiving,
    Responding,
    Done,
} t_clientstate;

class Client
{
    private :
        Shell           &_shell;
        Request         _req;
        t_clientstate   _status;
        std::string     _resp;
        int             _fd;
        int             _lfd;
        clock_t         _start;

        Client();
    public :
        Client(int fd, Shell &shell);
        Client(Client const &a);
        ~Client();
        Client  &operator=(Client const &a);

        void            receive();
        void            respond();
        t_clientstate   status();
};