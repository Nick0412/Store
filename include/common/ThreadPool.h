#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <deque>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <type_traits>

namespace Common {
    class ThreadPool {
    private:
        std::deque<std::function<void()>> task_queue;
        std::vector<std::thread> workers;
        std::mutex queue_mutex;
        std::condition_variable worker_notification;
        bool should_stop;

        void run()
        {
            while (true)
            {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(queue_mutex);
                    while (task_queue.empty())
                    {
                        if (should_stop)
                        {
                            return;
                        }
                        // wait
                        worker_notification.wait(lock);
                    }
                    task = std::move(task_queue.front());
                    task_queue.pop_front();
                }
                task();
            }
        }

    public:
        ThreadPool();
        ThreadPool(std::size_t num_workers);
        ~ThreadPool();

        template<typename F, typename ...Args>
        std::future<typename std::invoke_result<F(Args...)>::type> submit(F&& f, Args&&... args);
    };
}

#endif
