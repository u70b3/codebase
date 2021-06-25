#pragma once

#include <condition_variable>
#include <mutex>

namespace kid {

class WaitEvent {
public:
    WaitEvent() : done_(false) {}
    void Wait() {
        std::unique_lock<std::mutex> lk(lock_);
        while (!done_) {
            cv_.wait(lk);
        }
    }
    void Signal() {
        {
            std::unique_lock<std::mutex> lk(lock_);
            done_ = true;
        }
        cv_.notify_one();
    }
private:
    std::mutex lock_;
    std::condition_variable cv_;
    bool done_;
};

}

