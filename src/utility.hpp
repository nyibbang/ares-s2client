#pragma once

#include <type_traits>

#define ARES_INTERNAL_FWD(v) std::forward<decltype(v)>(v)

namespace ares {

template <typename T>
constexpr decltype(auto) source(T&& t) {
  return *std::forward<T>(t);
}

struct Source {
  template <typename T>
  constexpr decltype(auto) operator()(T&& t) const {
    return source(std::forward<T>(t));
  }
};

struct Unit {};

}  // namespace ares
