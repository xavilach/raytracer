#ifndef THREAD_POOL_HH_
#define THREAD_POOL_HH_

#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <functional>
#include <condition_variable>
#include <future>

namespace Raytracer
{
class ThreadPool
{
public:
    ThreadPool();
    ThreadPool(int count);
    ~ThreadPool();

    template <typename F, typename... Args>
    void enqueue(F &&f, Args &&... args)
    {
        std::function<void()> task = std::bind(std::forward<F>(f), std::forward<Args>(args)...);

        {
            std::unique_lock<std::mutex> lock(m_lock);
            m_tasks.push(task);
        }

        m_condition.notify_one();
    }

private:
    void run();

private:
    std::vector<std::thread> m_threads;
    std::queue<std::function<void()>> m_tasks;

    std::mutex m_lock;
    std::condition_variable m_condition;

    bool m_running;
};
} // namespace Raytracer

#endif /*THREAD_POOL_HH_*/
