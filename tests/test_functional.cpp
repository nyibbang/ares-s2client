#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "functional.hpp"
#include "mock_function.hpp"

using namespace ::ares;
using namespace ::testing;

TEST(FunctionalCompose, ConstructibleByDefault) {
  Compose c;
  EXPECT_NO_THROW(c());
}

TEST(FunctionalCompose, FunctionResultPassesToNext) {
  tests::Mock_function<int(int)> f1;
  tests::Mock_function<std::string(int)> f2;
  tests::Mock_function<float(std::string)> f3;
  Compose c{f3, f2, f1};
  InSequence seq;
  EXPECT_CALL(f1, Call(11)).WillOnce(Return(13));
  EXPECT_CALL(f2, Call(13)).WillOnce(Return("foobar"));
  EXPECT_CALL(f3, Call(StrEq("foobar"))).WillOnce(Return(127.37f));
  EXPECT_FLOAT_EQ(127.37f, c(11));
}

TEST(FunctionalCompose, FunctionReturningVoid) {
  tests::Mock_function<void(int)> f1;
  tests::Mock_function<int()> f2;
  Compose c{f2, f1};

  InSequence seq;
  EXPECT_CALL(f1, Call(8));
  EXPECT_CALL(f2, Call()).WillOnce(Return(42));
  EXPECT_EQ(42, c(8));
}

TEST(FunctionalCompose, WithOnlyOneFunction) {
  tests::Mock_function<int(int)> f;
  Compose c{f};
  EXPECT_CALL(f, Call(3829)).WillOnce(Return(326));
  EXPECT_EQ(326, c(3829));
}
