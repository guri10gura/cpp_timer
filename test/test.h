
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

