#ifndef CHANNEL__H
#define CHANNEL__H
#include <stdint.h>
#include "buffer.h"
namespace network{
class Socket;
class Epoller;
class Channel{
public:
    explicit Channel(Socket* sock) : sock_(sock){}
    ~Channel();
    virtual void HandleEvent(int32_t event, Epoller* poll) = 0;
    int32_t GetFd();
protected:
    Socket* sock_;
    Buffer buffer_;
};
class ConnectionChannel : public Channel{
public:
    explicit ConnectionChannel(Socket* sock) : Channel(sock){}
    void HandleEvent(int32_t event, Epoller* poll);
};
class AcceptorChannel : public Channel{
public:
    explicit AcceptorChannel(Socket* sock) : Channel(sock){}
    void HandleEvent(int32_t event, Epoller* poll);
};

}
#endif
