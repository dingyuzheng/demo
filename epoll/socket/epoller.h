#ifndef EPOLLER__H
#define EPOLLER__H
#include <stdint.h>
#include <sys/epoll.h>
#include <map>
namespace network{
class Channel;
class Epoller{
public:
    Epoller();
    ~Epoller();
    void Poll();
    void AddChannel(Channel* channel, int32_t event);
    void UpdateChannel(Channel* channel, int32_t event);
    void DelChannel(Channel* channel);
private:
    enum{
        EVENT_MAX = 8192,
    };
    typedef std::map<int32_t, Channel*> ChannelMap;
    
    int32_t ep_fd_;
    struct epoll_event events_[EVENT_MAX];
    ChannelMap channels_;
};
}
#endif
