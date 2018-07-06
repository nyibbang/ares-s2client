#pragma once

#include <type_traits>

#define ARES_INTERNAL_FWD(v) std::forward<decltype(v)>(v)

namespace ares {

template <typename T>
constexpr auto fwd(std::remove_reference_t<T>& t) noexcept {
  return static_cast<T&&>(t);
}

template <typename T>
constexpr auto fwd(std::remove_reference_t<T>&& t) noexcept {
  return static_cast<T&&>(t);
}

template <typename T>
auto deref(T&& t) {
  return *fwd<T>(t);
}

struct Unit {};

}  // namespace ares
