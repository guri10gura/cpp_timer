#include <chrono>
#include <future>

using namespace std;

class WaitLock
{
private:
    std::mutex mtx;
    std::condition_variable cv;

public:
    void wait()
    {
        std::unique_lock<std::mutex> ul(mtx);
        cv.wait(ul);
    }
    /**
     * return true: timeout
     *        false: other
     */
    bool wait(const chrono::milliseconds &max_wait_time)
    {
        std::unique_lock<std::mutex> ul(mtx);
        return (cv.wait_for(ul, max_wait_time) == cv_status::timeout);
    }
    void unlock()
    {
        std::lock_guard<std::mutex> lock(mtx);
        cv.notify_one();
    }
};
