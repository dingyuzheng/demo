#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <map>

#include "log.h"
#include "socket.h"
#include "sockaddr.h"

#define EVENAT_MAX 8192
#define PORT 8080
#define BUFSIZE 1024
using namespace network;
void set_fd_nonblock(int fd);
int main(int argc, char** argv)
{
    int ep_fd, cur_fd, nevent, rwlen, buf_cursor;
    char buf[EVENAT_MAX][BUFSIZE];
    epoll_event ep_ev, events[EVENAT_MAX];
    typedef std::map<int, Socket*> SockMap;
    SockMap sockMap;

    SockAddr local_addr("127.0.0.1", PORT);
    Socket* server = Socket::Create();
    server->Bind(local_addr);
    server->Listen(EVENAT_MAX);
    set_fd_nonblock(server->GetSockFd());

    if ( (ep_fd = epoll_create(EVENAT_MAX)) == -1 )
    {
        LogError("error:epoll_create():size=%d\n", EVENAT_MAX);
        exit(1);
    }
    set_fd_nonblock(ep_fd);

    bzero(&ep_ev, sizeof(ep_ev));
    ep_ev.data.fd = server->GetSockFd();
    ep_ev.events = EPOLLIN|EPOLLET;
    if ( epoll_ctl(ep_fd, EPOLL_CTL_ADD, server->GetSockFd(), &ep_ev) == -1 )
    {
        LogError("error:epoll_ctl()\n");
        exit(1);
    }

    for(;;)
    {
        if ( ( nevent = epoll_wait( ep_fd, events, EVENAT_MAX, -1 ) ) == -1 )
        {
            LogError("error:epoll_wait()\n");
            exit(1);
        }

        for( int i = 0; i < nevent; ++i )
        {
            cur_fd = events[i].data.fd;
            if ( cur_fd == server->GetSockFd() )
            {
                Socket* new_conn = NULL;
                while ( ( new_conn = server->Accept() ) != NULL ) 
                {
                    int new_fd = new_conn->GetSockFd();
    		        set_fd_nonblock(new_fd);
                    ep_ev.data.fd = new_fd;
                    ep_ev.events = EPOLLIN|EPOLLET;
                    if ( epoll_ctl(ep_fd, EPOLL_CTL_ADD, new_fd, &ep_ev) == -1 )
                    {
                        LogError("error:epoll_ctl()\n");
                        exit(1);
                    }
                    sockMap[new_fd] = new_conn;
                }
            }
            else if ( events[i].events & EPOLLIN )
            {
                rwlen = 0;
                buf_cursor = 0;
                while( ( rwlen = sockMap[cur_fd]->Read(buf[i] + buf_cursor, BUFSIZE - buf_cursor) ) > 0 )
                {
                    buf_cursor += rwlen; 
                }

                if ( rwlen == -1 && errno != EAGAIN  && errno != EWOULDBLOCK)
                {
                    LogError("error:read():cur_fd=%d\n", cur_fd);
                    exit(1);
                }

                ep_ev.data.fd = cur_fd;
                ep_ev.events = EPOLLOUT|EPOLLET;
                if ( epoll_ctl(ep_fd, EPOLL_CTL_MOD, cur_fd, &ep_ev) == -1 )
                {
                    LogError("error:epoll_ctl()\n");
                    exit(1);
                }

                buf[i][buf_cursor] = '\0';
                LogError("recv client request:%s:fd=%d\n", buf[i], cur_fd);
            }
            else if ( events[i].events & EPOLLOUT )
            {
                rwlen = 0;
                buf_cursor = 0;
                int size = strlen(buf[i]);
                while ( buf_cursor < size )
                {
                    if ( ( rwlen = write( cur_fd, buf[i] + buf_cursor, size - buf_cursor ) ) == -1 ) 
                    if ( ( rwlen = sockMap[cur_fd]->Write( buf[i] + buf_cursor, size - buf_cursor ) ) == -1 ) 
                    {
                        if ( errno != EAGAIN )
                        {
                            LogError("error:write():cur_fd=%d\n", cur_fd);
                            exit(1);
                        }
			break;
                    }
                    buf_cursor += rwlen;
                }
                LogError("send client responce:%s,fd=%d\n", buf[i], cur_fd);
                Socket::Destroy(sockMap[cur_fd]);
                LogDebug("destroy socket:fd=%d\n", cur_fd);
            }
            else 
            {
                Socket::Destroy(sockMap[cur_fd]);
                LogDebug("destroy socket:fd=%d\n", cur_fd);
            }
        }
    }

    return 0;
}

void set_fd_nonblock(int fd)
{
    fcntl( fd, F_SETFL, fcntl(fd, F_GETFL)|O_NONBLOCK );
}
