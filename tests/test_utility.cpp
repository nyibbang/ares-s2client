#include <gtest/gtest.h>
#include <utility.hpp>

using namespace ::ares;
using namespace ::testing;

TEST(UtilitySource, DereferencesPointer) {
  int a = 42;
  int* p = &a;
  auto&& b = source(p);
  EXPECT_EQ(a, b);
  EXPECT_EQ(&a, &b);
}
