#include "channel.h"
#include "log.h"
#include "socket.h"
#include "epoller.h"
#include <errno.h>
#include <assert.h>
using namespace network;
Channel::~Channel()
{ 
    Socket::Destroy(sock_); 
}
int32_t Channel::GetFd()
{
    return sock_->GetSockFd();
}
void AcceptorChannel::HandleEvent(int32_t event, Epoller* poll)
{
    Socket* new_conn = NULL;
    while ( ( new_conn = sock_->Accept() ) != NULL ) 
        poll->AddChannel(new ConnectionChannel(new_conn), EPOLLIN|EPOLLET);
}
void ConnectionChannel::HandleEvent(int32_t event, Epoller* poll)
{
    if ( event & EPOLLIN )
    {
        ssize_t rlen = -1;
        while ( buffer_.CanRead() &&
            (rlen = sock_->Read( buffer_.GetReadBuffer(), buffer_.GetReadCapacity())) > 0 )
        {
            buffer_.IncReadCursor(rlen);
        }

        if ( rlen == -1 && errno != EAGAIN  && errno != EWOULDBLOCK)
            assert(0);

        poll->UpdateChannel(this, EPOLLOUT|EPOLLET);
    }
    else if ( event & EPOLLOUT )
    {
        ssize_t wlen = -1;
        while ( buffer_.CanWrite() &&
            (wlen = sock_->Write( buffer_.GetWriteBuffer(), buffer_.GetWriteCapacity())) > 0 )
        {
            buffer_.IncWriteCursor(wlen);
        }
        
        if ( wlen == -1 && errno != EAGAIN )
            assert(0);
        
        poll->DelChannel(this);
        LogDebug("destroy socket:fd=%d\n", sock_->GetSockFd());
        Socket::Destroy(sock_);
    }
    else 
    {
        poll->DelChannel(this);
        LogDebug("destroy socket:fd=%d\n", sock_->GetSockFd());
        Socket::Destroy(sock_);
    }
}
