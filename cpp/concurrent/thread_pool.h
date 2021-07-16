#pragma once

#include <cassert>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>
#include <functional>
#include <future>

class ThreadPool
{
public:
    explicit ThreadPool(size_t threadCount) : pool_(std::make_shared<Pool>())
    {
        assert(threadCount > 0);
        pool_->isClosed = false;
        for (size_t i = 0; i < threadCount; i++)
        {
            std::thread([pool = pool_]
                        {
                            std::unique_lock<std::mutex> locker(pool->mtx);
                            while (true)
                            {
                                if (!pool->tasks.empty())
                                {
                                    auto task = std::move(pool->tasks.front());
                                    pool->tasks.pop();
                                    locker.unlock();
                                    task();
                                    locker.lock();
                                }
                                else if (pool->isClosed)
                                    break;
                                else
                                    pool->cond.wait(locker);
                            }
                        })
                .detach();
        }
    }

    ThreadPool() : ThreadPool(std::thread::hardware_concurrency())
    {
        ;
    }

    ThreadPool(ThreadPool &&) = default;

    ~ThreadPool()
    {
        if (static_cast<bool>(pool_))
        {
            {
                std::unique_lock<std::mutex> locker(pool_->mtx);
                pool_->isClosed = true;
            }
            pool_->cond.notify_all();
        }
    }

    template <class F, class... Args>
    auto AddTask(F &&f, Args &&...args)
        -> std::future<typename std::result_of<F(Args...)>::type>
    {
        // 返回值类型与传入函数返回值类型保持一致
        using return_type = typename std::result_of<F(Args...)>::type;
        // 把传入函数 f 包一个 package_task
        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        // 返回值就是 package_task 的返回值
        std::future<return_type> res = task->get_future();

        {
            std::unique_lock<std::mutex> locker(pool_->mtx);
            // 线程池已停止后，不允许入队
            if (pool_->isClosed)
                throw std::runtime_error("AddTask on stopped ThreadPool is invalid");

            pool_->tasks.emplace([task]()
                                 { (*task)(); });
        }

        pool_->cond.notify_one();
        return res;
    }

private:
    struct Pool
    {
        std::mutex mtx;
        std::condition_variable cond;
        bool isClosed;
        std::queue<std::function<void()>> tasks;
    };
    std::shared_ptr<Pool> pool_;
};
