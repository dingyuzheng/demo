#include "epoller.h"
#include "channel.h"
#include <assert.h>
#include <strings.h>
#include "util.h"
using namespace network;
Epoller::Epoller()
{
    ep_fd_ = epoll_create(EVENT_MAX);
    set_fd_nonblock(ep_fd_);
    assert(ep_fd_ != -1);
    bzero(events_, EVENT_MAX * sizeof (struct epoll_event));
}
Epoller::~Epoller()
{
}
void Epoller::AddChannel(Channel* channel, int32_t event)
{
    struct epoll_event ev;
    bzero(&ev, sizeof ev);
    int32_t fd = channel->GetFd();
    ev.data.fd = fd;
    ev.events = event;
    if ( epoll_ctl(ep_fd_, EPOLL_CTL_ADD, fd, &ev) == -1 )
        assert(0);
    channels_[fd] = channel;
}
void Epoller::UpdateChannel(Channel* channel, int32_t event)
{
    struct epoll_event ev;
    bzero(&ev, sizeof ev);
    int32_t fd = channel->GetFd();
    ev.data.fd = fd;
    ev.events = event;
    if ( epoll_ctl(ep_fd_, EPOLL_CTL_MOD, fd, &ev) == -1 )
        assert(0);
    channels_[fd] = channel;
}
void Epoller::DelChannel(Channel* channel)
{
    struct epoll_event ev;
    bzero(&ev, sizeof ev);
    int32_t fd = channel->GetFd();
    ev.data.fd = fd;
    if ( epoll_ctl(ep_fd_, EPOLL_CTL_DEL, fd, &ev) == -1 )
        assert(0);
    channels_[fd] = NULL;
}
void Epoller::Poll()
{
    int32_t nevent = epoll_wait(ep_fd_, events_, EVENT_MAX, -1);
    for ( int32_t i = 0; i < nevent; ++i )
    {
        int32_t cur_fd = events_[i].data.fd;
        channels_[cur_fd]->HandleEvent( events_[i].events, this );
    }
}
