#include "ipc/SocketIPC.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
        return std::cerr << "Invalid args" << std::endl, (1);
    SocketIPC server(av[1]);

    server.start_server();
    return (0);
}