

#include <functional>
#include <chrono>
#include <future>
#include <cstdio>

using namespace std;

class WaitLock
{
private:
    std::mutex mtx;
    std::condition_variable cv;
    bool ready;

public:
    void wait()
    {
        if (!mtx.try_lock())
        {
            throw std::logic_error("try_lock error");
        }
        std::unique_lock<std::mutex> ul(mtx);
        cv.wait(ul);
    }
    bool wait(const chrono::milliseconds &max_wait_time)
    {
        if (!mtx.try_lock())
        {
            throw std::logic_error("try_lock error");
        }
        std::unique_lock<std::mutex> ul(mtx);
        return (cv.wait_for(ul, max_wait_time) == cv_status::timeout);
    }

    void unlock()
    {
        ready = true;
        std::lock_guard<std::mutex> lock(mtx);
        cv.notify_one();
    }
};
