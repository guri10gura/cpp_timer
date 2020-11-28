
#include "timer.hpp"

#include <signal.h>
#include "gtest/gtest.h"


class TTimerTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
      printf("############# SetUp #############\n");
  }

  // virtual void TearDown() {}

};

TEST(TTimerTest, timeoutYyy) {


    EXPECT_EQ(true, false);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

