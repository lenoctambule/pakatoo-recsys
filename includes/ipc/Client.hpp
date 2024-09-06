#pragma once

# include "ipc/Request.hpp"
# include <sys/socket.h>

# define BUFFSIZE 65536

typedef enum e_clientstate
{
    Receiving,
    Responding,
    Done,
} t_clientstate;

class Client
{
    private :
        Request         _req;
        t_clientstate   _status;
        int             _fd;
        int             _lfd;

        Client();
    public :
        Client(int fd, int lfd);
        Client(Client const &a);
        ~Client();
        Client  &operator=(Client const &a);

        void            receive();
        void            respond();
        t_clientstate   status();
};