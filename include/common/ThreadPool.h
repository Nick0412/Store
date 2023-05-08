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

        /**
         * 
         * Helper template provided to us by type traits to get the result
         * 
         * template< class F, class... ArgTypes >
         * using invoke_result_t = typename invoke_result<F, ArgTypes...>::type;
         * 
         * See this page for reference: https://en.cppreference.com/w/cpp/types/result_of
         */
        template <typename F, typename ...Args>
        std::future<std::invoke_result_t<F, Args...>> submit(F&& f, Args&&... args)
        {
            using return_type = std::invoke_result_t<F, Args...>;
            auto task = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
            std::future<return_type> res = task->get_future();
            {
                const std::lock_guard<std::mutex> lock(queue_mutex);
                task_queue.emplace_back([task] { (*task)(); });
            }
            worker_notification.notify_one();
            return res;
        }
    };
}

#endif
