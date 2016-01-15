#ifndef BUFFER__H
#define BUFFER__H
#define BUFF_LEN 1024
#include <strings.h>
namespace network{
class Buffer{
public:
    Buffer() : rcursor_(0), wcursor_(0), offset_(0) {
        bzero(buffer_, BUFF_LEN);
    }
    bool CanRead() { return offset_ != BUFF_LEN; }
    bool CanWrite() { return offset_ != 0; }
    void IncReadCursor(size_t rlen) {
        rcursor_ = (rcursor_ + rlen) % BUFF_LEN;
        offset_ += rlen;
    }
    void IncWriteCursor(size_t wlen) {
        wcursor_ = (wcursor_ + wlen) % BUFF_LEN; 
        offset_ -= wlen;
    }
    size_t GetReadCapacity() { return BUFF_LEN - offset_; }
    size_t GetWriteCapacity() { return offset_; }
    void* GetReadBuffer() { return buffer_ + rcursor_; }
    void* GetWriteBuffer() { return buffer_ + wcursor_; }
private:
    char buffer_[BUFF_LEN];
    size_t rcursor_;
    size_t wcursor_;
    size_t offset_;
};
}
#endif
