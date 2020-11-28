
#include <signal.h>
#include "gtest/gtest.h"
#include "wait_lock.h"
#include "timer.hpp"

std::mutex mtx;
std::condition_variable cv;

std::timed_mutex tmtx;

bool is_called_func1 = false;
bool is_called_func2 = false;
bool isReady = false;

WaitLock localLock;

class TimerTest : public ::testing::Test
{
  void SetUp()
  {
    printf("SetUp\n");
    is_called_func1 = false;
    is_called_func2 = false;
  }
};

void test_func1()
{
  is_called_func1 = true;
  printf("test_func1\n");

  localLock.unlock();
}

void test_func2(int a, int b)
{
  is_called_func2 = true;
  printf("test_func2\n");

  localLock.unlock();
}

/*************************************
 *                TEST
 *************************************/
TEST_F(TimerTest, timeout)
{

  timer t1(1000, &test_func1);
  localLock.wait();

  EXPECT_EQ(true, is_called_func1);
  EXPECT_EQ(false, is_called_func2);
}

TEST_F(TimerTest, timeout2)
{

  timer t1(1000, &test_func1);
  localLock.wait();

  EXPECT_EQ(true, is_called_func1);
  EXPECT_EQ(false, is_called_func2);
}

TEST_F(TimerTest, not_timeout)
{
  timer t2(2000, &test_func2, 5, 7);
  localLock.wait(std::chrono::milliseconds(1000));

  EXPECT_EQ(false, is_called_func1);
  EXPECT_EQ(false, is_called_func2);
}

TEST_F(TimerTest, Positive)
{
  //EXPECT_EQ(1, factorial(1));
  //EXPECT_EQ(2, factorial(2));
  //EXPECT_EQ(120, factorial(5));
}

TEST_F(TimerTest, Failure)
{
  //EXPECT_EQ(42, factorial(0));
}
