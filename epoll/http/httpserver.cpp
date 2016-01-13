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

#define EVENAT_MAX 8192
#define PORT 8080
#define BUFSIZE 1024
void set_fd_nonblock(int fd);
int main(int argc, char** argv)
{
    int ep_fd, listen_fd, cur_fd, remote_fd, nevent, rwlen, buf_cursor;
    socklen_t remote_addr_len;
    char buf[EVENAT_MAX][BUFSIZE];
    epoll_event ep_ev, events[EVENAT_MAX];
    struct sockaddr_in local_addr, remote_addr;
    bzero(&remote_addr_len, sizeof(remote_addr_len));
    bzero(&local_addr, sizeof(local_addr));
    bzero(&remote_addr, sizeof(remote_addr));

    if ( (listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1 )
    {
        printf("error:socket()\n)");
        exit(1);
    }
    set_fd_nonblock(listen_fd);

    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(PORT);
    local_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if ( bind( listen_fd, (struct sockaddr*)&local_addr, sizeof(local_addr) ) == -1 )
    {
        printf("error:bind():port=%d\n", PORT);
        exit(1);
    }

    if ( listen(listen_fd, EVENAT_MAX) == -1 )
    {
        printf("error:listen():listen_fd=%d\n", listen_fd);
        exit(1);
    }

    if ( (ep_fd = epoll_create(EVENAT_MAX)) == -1 )
    {
        printf("error:epoll_create():size=%d\n", EVENAT_MAX);
        exit(1);
    }
    set_fd_nonblock(ep_fd);

    bzero(&ep_ev, sizeof(ep_ev));
    ep_ev.data.fd = listen_fd;
    ep_ev.events = EPOLLIN|EPOLLET;
    if ( epoll_ctl(ep_fd, EPOLL_CTL_ADD, listen_fd, &ep_ev) == -1 )
    {
        printf("error:epoll_ctl()\n");
        exit(1);
    }

    for(;;)
    {
        if ( ( nevent = epoll_wait( ep_fd, events, EVENAT_MAX, -1 ) ) == -1 )
        {
            printf("error:epoll_wait()\n");
            exit(1);
        }

        for( int i = 0; i < nevent; ++i )
        {
            cur_fd = events[i].data.fd;
            if ( cur_fd == listen_fd )
            {
                while ( ( remote_fd = accept( cur_fd, ( struct sockaddr* ) &remote_addr, &remote_addr_len ) ) != -1 ) 
                {
    		    set_fd_nonblock(remote_fd);
                    ep_ev.data.fd = remote_fd;
                    ep_ev.events = EPOLLIN|EPOLLET;
                    if ( epoll_ctl(ep_fd, EPOLL_CTL_ADD, remote_fd, &ep_ev) == -1 )
                    {
                        printf("error:epoll_ctl()\n");
                        exit(1);
                    }
                    //printf("accept new connection:%d\n", remote_fd);
                }
            }
            else if ( events[i].events & EPOLLIN )
            {
                rwlen = 0;
                buf_cursor = 0;
                while( ( rwlen = read( cur_fd, buf[i] + buf_cursor, BUFSIZE - buf_cursor ) ) > 0 )
                {
                    buf_cursor += rwlen; 
                }

                if ( rwlen == -1 && errno != EAGAIN  && errno != EWOULDBLOCK)
                {
                    printf("error:read():cur_fd=%d\n", cur_fd);
                    exit(1);
                }

                ep_ev.data.fd = cur_fd;
                ep_ev.events = EPOLLOUT|EPOLLET;
                if ( epoll_ctl(ep_fd, EPOLL_CTL_MOD, cur_fd, &ep_ev) == -1 )
                {
                    printf("error:epoll_ctl()\n");
                    exit(1);
                }

                buf[i][buf_cursor] = '\0';
                printf("recv client request:%s:fd=%d\n", buf[i], cur_fd);
            }
            else if ( events[i].events & EPOLLOUT )
            {
                rwlen = 0;
                buf_cursor = 0;
                int size = strlen(buf[i]);
                while ( buf_cursor < size )
                {
                    if ( ( rwlen = write( cur_fd, buf[i] + buf_cursor, size - buf_cursor ) ) == -1 ) 
                    {
                        if ( errno != EAGAIN )
                        {
                            printf("error:write():cur_fd=%d\n", cur_fd);
                            exit(1);
                        }
			break;
                    }
                    buf_cursor += rwlen;
                }
                printf("send client responce:%s,fd=%d\n", buf[i], cur_fd);
                close(cur_fd);
            }
            else 
            {
                close(cur_fd);
            }
        }
    }

    return 0;
}

void set_fd_nonblock(int fd)
{
    fcntl( fd, F_SETFL, fcntl(fd, F_GETFL)|O_NONBLOCK );
}
