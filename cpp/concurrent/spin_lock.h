#pragma once
#include <atomic>

class spinlock_mutex
{
    std::atomic_flag flag;

public:
    spinlock_mutex() : flag(ATOMIC_FLAG_INIT)
    {
    }

    void lock()
    {
        while (flag.test_and_set(std::memory_order_acquire))
        {
        }
    }

    bool try_lock()
    {
        if (flag.test_and_set(std::memory_order_acquire))
            return false;
        return true;
    }

    void unlock()
    {
        flag.clear(std::memory_order_release);
    }
};
