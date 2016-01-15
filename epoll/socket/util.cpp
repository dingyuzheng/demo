#include "util.h"
#include <unistd.h>
#include <fcntl.h>
namespace network{
void set_fd_nonblock(int fd){
    fcntl( fd, F_SETFL, fcntl(fd, F_GETFL)|O_NONBLOCK );
}
}
