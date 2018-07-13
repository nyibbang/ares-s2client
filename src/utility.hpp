#pragma once

#include <type_traits>

#define ARES_INTERNAL_FWD(v) std::forward<decltype(v)>(v)

namespace ares {

template <typename T>
auto deref(T&& t) {
  return *std::forward<T>(t);
}

struct Unit {};

}  // namespace ares
