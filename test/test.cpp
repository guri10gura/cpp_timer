
#include <signal.h>
#include "gtest/gtest.h"
#include "timer.hpp"
#include "wait_lock.h"

std::mutex mtx;
std::condition_variable cv;

std::timed_mutex tmtx;

bool is_called_func1 = false;
bool is_called_func2 = false;
bool isReady = false;


void test_func1(){
    is_called_func1 = true;
    printf("test_func1\n");

    isReady = true;
    std::lock_guard<std::mutex> lock(mtx);
    cv.notify_one();
}

void test_func2(int a, int b){
    is_called_func2 = true;
    printf("test_func2\n");

    isReady = true;
    std::lock_guard<std::mutex> lock(mtx);
    //std::lock_guard<std::timed_mutex> lock(tmtx);
    cv.notify_one();
}

void SetUp() {
    printf("SetUp\n");
    is_called_func1 = false;
    is_called_func2 = false;
}

/*************************************
 *                TEST
 *************************************/
TEST(TimerTest, timeout) {

    timer t1(1000, &test_func1);
    std::unique_lock<std::mutex> ul(mtx);
    cv.wait(ul, []{return isReady;});

    EXPECT_EQ(true, is_called_func1);
    EXPECT_EQ(false, is_called_func2);
}

TEST(TimerTest, not_timeout) {
    timer t2(1000, &test_func2, 5, 7);

    //std::unique_lock<std::timed_mutex> ul(tmtx);
    std::unique_lock<std::mutex> ul(mtx);
    cv.wait_for(ul, std::chrono::milliseconds(3000), []{return isReady;} );

    EXPECT_EQ(false, is_called_func1);
    EXPECT_EQ(false, is_called_func2);

  //EXPECT_EQ(1, factorial(0));
}

TEST(TimerTest, Positive) {
  //EXPECT_EQ(1, factorial(1));
  //EXPECT_EQ(2, factorial(2));
  //EXPECT_EQ(120, factorial(5));
}

// 失敗するべきテスト
TEST(TimerTest, Failure) {
  //EXPECT_EQ(42, factorial(0));
}

