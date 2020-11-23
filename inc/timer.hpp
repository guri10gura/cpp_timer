#include <functional>
#include <chrono>
#include <future>
#include <cstdio>


class timer
{
private:
    timer() = delete;
    timer(timer&) = delete;
    bool is_canceled = false;
public:
    template <typename callable, typename... arguments>
    timer(int delay_ms, callable&& f, arguments&&... args)
    {
        std::function<typename std::result_of<callable(arguments...)>::type()> task(std::bind(std::forward<callable>(f), std::forward<arguments>(args)...));
        auto func = [delay_ms, task, canceled = &is_canceled]() {
                std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
                if(!*canceled){
                    task();
                }
            };
        std::thread(func).detach();
    }

    void cancel(){
        is_canceled = true;
    }
};

