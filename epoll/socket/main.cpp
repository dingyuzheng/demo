#include <stdio.h>
#include "log.h"
#include "socket.h"
#include "sockaddr.h"
#include "util.h"
#include "channel.h"
#include "epoller.h"

#define EVENT_MAX 8196
#define PORT 8080
using namespace network;
int main(int argc, char** argv)
{
    SockAddr local_addr("127.0.0.1", PORT);
    Socket* server = Socket::Create();
    server->Bind(local_addr);
    server->Listen(EVENT_MAX);

    AcceptorChannel* acceptor = new AcceptorChannel(server);
    Epoller epoll;
    epoll.AddChannel(acceptor, EPOLLIN|EPOLLET);
    for(;;)
        epoll.Poll();

    return 0;
}

