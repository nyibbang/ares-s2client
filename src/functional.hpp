#pragma once

#include <optional>
#include "utility.hpp"

#define ARES_FUNCTIONAL_DEFINE_CALLOPS()            \
  template <typename... Args>                       \
  constexpr auto operator()(Args&&... args) {       \
    return impl(*this, fwd<Args>(args)...);         \
  }                                                 \
  template <typename... Args>                       \
  constexpr auto operator()(Args&&... args) const { \
    return impl(*this, fwd<Args>(args)...);         \
  }

namespace ares {

template <typename T = void>
struct Constant_function {
  T value;

  constexpr Constant_function() = default;

  constexpr Constant_function(T&& value) : value{fwd<T>(value)} {}

  template <typename... Args>
  constexpr auto operator()(Args&&...) const {
    return value;
  }
};

template <>
struct Constant_function<void> {
  constexpr Constant_function() = default;

  template <typename... Args>
  constexpr void operator()(Args&&...) const {}
};

// template <typename Predicate, typename Proc>
// struct Maybe_function {
//  Predicate pred;
//  Proc proc;
//
//  Maybe_function() = default;
//
//  Maybe_function(Predicate&& pred, Proc&& proc)
//      : pred{fwd<Predicate>(pred)}, proc{fwd<Proc>(proc)} {}
//
//  ARES_FUNCTIONAL_DEFINE_CALLOPS()
//
// private:
//  template <typename Obj, typename... Args>
//  static auto impl(Obj& obj, Args&&... args) {
//    auto&& pred_res = obj.pred();
//    if constexpr (std::is_void_v<
//                      std::invoke_result_t<decltype(obj.proc), Args&&...>>) {
//      return ) ? std::optional{obj.proc(fwd<Args>(args)...)}
//                        : std::nullopt;
//    } else {
//    }
//  }
//};

// template <typename Predicate>
// struct Maybe_transfo {
//  Predicate pred;
//
//  Maybe_transfo() = default;
//
//  Maybe_transfo(Predicate&& pred) : pred{fwd<Predicate>(pred)} {}
//
//  ARES_FUNCTIONAL_DEFINE_CALLOPS()
//
// private:
//  template <typename Obj, typename Func>
//  static auto impl(Obj& obj, Func&& func) {
//    return Maybe_function{obj.pred, fwd<Func>(func)};
//  }
//};

template <typename... Functions>
struct Compose;

template <typename FirstFunction, typename... NextFunctions>
struct Compose<FirstFunction, NextFunctions...> {
  FirstFunction first_func;
  Compose<NextFunctions...> next_funcs;

  constexpr Compose() = default;

  constexpr Compose(FirstFunction&& first_func, NextFunctions&&... next_funcs)
      : first_func(fwd<FirstFunction>(first_func)),
        next_funcs{fwd<NextFunctions>(next_funcs)...} {}

  ARES_FUNCTIONAL_DEFINE_CALLOPS()

 private:
  template <typename Obj, typename... Args>
  static constexpr auto impl(Obj& obj, Args&&... args) {
    if constexpr (sizeof...(NextFunctions) == 0u) {
      return obj.first_func(fwd<Args>(args)...);
    } else if constexpr (std::is_void_v<std::invoke_result_t<
                             decltype(obj.next_funcs), Args&&...>>) {
      return obj.first_func(), obj.next_funcs(fwd<Args>(args)...);
    } else {
      return obj.first_func(obj.next_funcs(fwd<Args>(args)...));
    }
  }
};

template <>
struct Compose<> : Constant_function<void> {};

template <typename FirstFunction, typename... NextFunctions>
Compose(FirstFunction&&, NextFunctions&&...)
    ->Compose<FirstFunction, NextFunctions...>;
Compose()->Compose<>;

}  // namespace ares
