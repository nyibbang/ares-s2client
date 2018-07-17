#pragma once

#include <gmock/gmock.h>

namespace ares::testing {

template <typename F>
struct Mock_function : ::testing::MockFunction<F> {
  template <typename... Args>
  decltype(auto) operator()(Args&&... args) {
    return ::testing::MockFunction<F>::Call(std::forward<Args>(args)...);
  }
};

}  // namespace ares::testing
