#include <stdio.h>
#include "sockaddr.h"
using namespace network;
int main()
{
    SockAddr addr("127.0.0.1", 8080);
    return 0;
}
