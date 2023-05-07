#include "common/ThreadPool.h"

namespace Common {
    // Create a thread pool with as many workers as cores
    ThreadPool::ThreadPool() : should_stop(false)
    {
        std::size_t num_workers = std::thread::hardware_concurrency();
        workers.reserve(num_workers);
        for (std::size_t i = 0; i < num_workers; i++)
        {
            workers.emplace_back(std::thread(std::bind(&ThreadPool::run, this)));
        }
    }

    ThreadPool::ThreadPool(std::size_t num_workers) : should_stop(false)
    {
        workers.reserve(num_workers);
        for (std::size_t i = 0; i < num_workers; i++)
        {
            workers.emplace_back(std::thread(std::bind(&ThreadPool::run, this)));
        }
    }


    ThreadPool::~ThreadPool()
    {
        {
            const std::lock_guard<std::mutex> lock(queue_mutex);
            should_stop = true;
        }
        worker_notification.notify_all();
        for (auto& worker : workers)
        {
            worker.join();
        }
    }
}
