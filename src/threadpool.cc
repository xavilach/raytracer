#include "threadpool.hh"

Raytracer::ThreadPool::ThreadPool() : ThreadPool(std::thread::hardware_concurrency())
{
}

Raytracer::ThreadPool::ThreadPool(int count) : m_running(true)
{
    for (int i = 0; i < count; i++)
    {
        m_threads.push_back(std::thread(&ThreadPool::run, this));
    }
}

Raytracer::ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(m_lock);
        m_running = false;
    }

    m_condition.notify_all();

    for (std::thread &th : m_threads)
    {
        th.join();
    }
}

void Raytracer::ThreadPool::run()
{
    std::function<void()> task;

    for (;;)
    {
        {
            std::unique_lock<std::mutex> lock(m_lock);

            m_condition.wait(lock, [this] { return !this->m_tasks.empty() || !this->m_running; });

            if (!this->m_running)
            {
                return;
            }

            task = m_tasks.front();
            m_tasks.pop();
        }

        task();
    }
}
