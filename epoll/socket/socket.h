#ifndef SOCKET__H
#define SOCKET__H
#include <sys/types.h>
namespace network{
class SockAddr;
class Socket{
public:
    static Socket* Create();
    static void Destroy(Socket*& socket);
    int GetSockFd() const { return fd_; }
    
    void Bind(const SockAddr& sock_addr) const;
    void Listen(int backlog) const;
    Socket* Accept() const;
    bool Connect(const SockAddr& remote_addr) const;
    
    ssize_t Read(void* buf, size_t count) const;
    ssize_t Write(const void* buf, size_t count) const;
    void Close() const;
private:
    Socket(int fd) { fd_ = fd; }
    ~Socket(){}
    
    int fd_;
};
}
#endif
