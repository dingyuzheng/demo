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

#define PORT 8080
int main(int argc, char** argv)
{
    int conn_fd, rwlen, cursor;
    const char* send_buf = "abcdefghijklmnopqrstuvwxyz";
    char recv_buf[1024];
    struct sockaddr_in remote_addr;
    bzero(&remote_addr, sizeof(remote_addr));

    remote_addr.sin_family = AF_INET;
    remote_addr.sin_port = htons(PORT);
    remote_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    cursor = 0;
    while(1)
    {
        if ( (conn_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1 )
        {
            printf("error:socket()\n)");
            exit(1);
        }
        if ( connect( conn_fd, (struct sockaddr*) & remote_addr, sizeof( remote_addr ) ) == -1 )
        {
            printf("error:connect():port=%d\n", PORT);
            exit(1);
        }
        if ( ( rwlen = write( conn_fd, send_buf + cursor, 1 ) <= 0) )
        {
            printf("error:write():cursor=%d\n", cursor);
            exit(1);
        }
        printf("send request to server:%c\n", send_buf[cursor]);
        cursor = ( cursor + 1 ) % 26;
        if ( ( rwlen = read( conn_fd, recv_buf, 1024) ) <= 0 )
        {
            printf("error:read()\n");
            exit(1);
        }
        recv_buf[rwlen] = '\0';
        printf("recv responce from server:%s\n", recv_buf);
    }

    return 0;
}
