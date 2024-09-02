#include "ipc/SocketIPC.hpp"

int main()
{
    SocketIPC server("127.0.0.1", 4560);

    server.start_server();
    return (0);
}