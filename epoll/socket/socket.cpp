#include "socket.h"
#include "sockaddr.h"
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
using namespace network;

Socket* Socket::Create()
{
    int new_fd = socket(AF_INET, SOCK_STREAM, 0);
    if ( new_fd == -1 )
    {
        LogError("error:socket()\n");
        return NULL;
    }
    else 
        return new Socket(new_fd);
}
void Socket::Destroy(Socket*& socket)
{
    socket->Close();
    delete socket;
    socket = NULL;
}
void Socket::Bind(const SockAddr& sock_addr) const
{
    if ( bind(fd_, (struct sockaddr*)&sock_addr, sizeof sock_addr) == -1 )
        LogError("error:bind()\n");
}
void Socket::Listen(int backlog) const
{
    if ( listen(fd_, backlog) == -1 )
        LogError("error:listen()\n");
}
Socket* Socket::Accept() const
{
    struct sockaddr_in addr;
    bzero(&addr, sizeof addr);
    socklen_t addr_len = sizeof addr;
    int new_fd = accept(fd_, (struct sockaddr*)& addr, &addr_len);
    if ( new_fd == -1 )
        return NULL;
    else
        return new Socket(new_fd);
}
bool Socket::Connect(const SockAddr& remote_addr) const
{
    const struct sockaddr* addr = (const struct sockaddr*)&(remote_addr.GetAddr());
    return connect(fd_, addr, sizeof(*addr)) == 0;
}
ssize_t Socket::Read(void* buf, size_t count) const
{
    return read(fd_, buf, count);
}
ssize_t Socket::Write(const void* buf, size_t count) const
{
    return write(fd_, buf, count);
}
void Socket::Close() const
{
    if (fd_ != -1)
        close(fd_);
}
