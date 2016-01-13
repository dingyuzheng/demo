#ifndef SOCKET__H
#define SOCKET__H
namespace network{
class Socket{
public:
    Socket(int fd) : fd_(fd){}
    ~Socket(){}
private:
    int fd_;
};
}
#endif
