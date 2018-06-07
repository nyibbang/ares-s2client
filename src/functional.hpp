#pragma once

#include <utility>

namespace ares {

template <typename T>
struct Constant_function {
  T value;
  template <typename... Args>
  T operator()(Args&&...) const {
    return value;
  }
};

template <typename F, typename P>
struct Domain_projection_function {
  F f;
  P proj;
  template <typename... Args>
  auto operator()(Args&&... args) {
    return f(proj(std::forward<Args>(args))...);
  }
};

}
