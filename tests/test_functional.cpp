#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <functional.hpp>
#include "mock_function.hpp"

using namespace ::ares;
using namespace ::ares::testing;
using namespace ::testing;

TEST(FunctionalCompose, ConstructibleByDefault) {
  Compose c;
  EXPECT_NO_THROW(c());
  EXPECT_NO_THROW(c(127)); // still polymorphic
}

TEST(FunctionalCompose, FunctionResultPassesToNext) {
  Mock_function<int(int)> f1;
  Mock_function<std::string(int)> f2;
  Mock_function<float(std::string)> f3;
  Compose c{f3, f2, f1};
  InSequence seq;
  EXPECT_CALL(f1, Call(11)).WillOnce(Return(13));
  EXPECT_CALL(f2, Call(13)).WillOnce(Return("foobar"));
  EXPECT_CALL(f3, Call(StrEq("foobar"))).WillOnce(Return(127.37f));
  EXPECT_FLOAT_EQ(127.37f, c(11));
}

TEST(FunctionalCompose, FunctionReturningVoid) {
  Mock_function<void(int)> f1;
  Mock_function<int()> f2;
  Compose c{f2, f1};

  InSequence seq;
  EXPECT_CALL(f1, Call(8));
  EXPECT_CALL(f2, Call()).WillOnce(Return(42));
  EXPECT_EQ(42, c(8));
}

TEST(FunctionalCompose, WithOnlyOneFunction) {
  Mock_function<int(int)> f;
  Compose c{f};
  EXPECT_CALL(f, Call(3829)).WillOnce(Return(326));
  EXPECT_EQ(326, c(3829));
}

TEST(FunctionMaybeFunction, ConstructibleByDefault) {
  Maybe_function mf;
  EXPECT_NO_THROW(mf());
  EXPECT_NO_THROW(mf(321)); // still polymorphic
}

TEST(FunctionMaybeFunction, DoesNotCallProcIfPredReturnsFalse) {
  Mock_function<bool()> pred;
  ::testing::StrictMock<Mock_function<int(int)>> proc;
  Maybe_function mf{pred, proc};
  EXPECT_CALL(pred, Call()).WillOnce(Return(false));
  mf(342789);
}

TEST(FunctionMaybeFunction, ReturnsNulloptIfPredReturnsFalse) {
  Mock_function<bool()> pred;
  Mock_function<int(int)> proc;
  Maybe_function mf{pred, proc};
  EXPECT_CALL(pred, Call()).WillOnce(Return(false));
  EXPECT_EQ(std::nullopt, mf(342789));
}

TEST(FunctionMaybeFunction, ReturnsOptOfProcResultIfPredReturnsTrue) {
  Mock_function<bool()> pred;
  Mock_function<int(int)> proc;
  Maybe_function mf{pred, proc};
  EXPECT_CALL(pred, Call()).WillOnce(Return(true));
  EXPECT_CALL(proc, Call(31283)).WillOnce(Return(213789));
  const auto& res = mf(31283);
  EXPECT_TRUE(res);
  EXPECT_EQ(213789, *res);
}
