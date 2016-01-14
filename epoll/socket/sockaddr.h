#ifndef SOCKADDR__H
#define SOCKADDR__H
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "log.h"

namespace network{
class SockAddr{
public:
    SockAddr(){
        bzero(&addr_, sizeof addr_);
    }
    SockAddr(const char* ip, int port){
        bzero(&addr_, sizeof addr_);
        addr_.sin_family = AF_INET;
        addr_.sin_port = htons(port);
        addr_.sin_addr.s_addr = inet_addr(ip);
        LogError("init SockAddr:ip=%s,port=%d\n", ip, port);
    }
    void SetAddr(const struct sockaddr_in& addr){
        addr_ = addr;
    }
    const struct sockaddr_in& GetAddr() const {
        return addr_;
    }
private:
    struct sockaddr_in addr_;
};
}
#endif
