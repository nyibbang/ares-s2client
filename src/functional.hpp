#pragma once

#include <optional>
#include "utility.hpp"

#define ARES_FUNCTIONAL_DEFINE_CALLOPS()             \
  template <typename... Args>                        \
  constexpr auto operator()(Args&&... args) {        \
    return impl(*this, std::forward<Args>(args)...); \
  }                                                  \
  template <typename... Args>                        \
  constexpr auto operator()(Args&&... args) const {  \
    return impl(*this, std::forward<Args>(args)...); \
  }

namespace ares {

template <typename T = void>
struct Constant_function {
  T value;

  constexpr Constant_function() = default;

  constexpr Constant_function(T&& value) : value{std::forward<T>(value)} {}

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

template <typename... Functions>
struct Compose;

template <typename Func1, typename... FuncN>
struct Compose<Func1, FuncN...> {
  Func1 func_1;
  Compose<FuncN...> funcs_n;

  constexpr Compose() = default;

  template <typename AFunc1, typename... AFuncN,
            typename = std::enable_if_t<!std::is_same_v<Compose, AFunc1>>>
  constexpr Compose(AFunc1&& afunc_1, AFuncN&&... afuncs_n)
      : func_1(std::forward<AFunc1>(afunc_1)),
        funcs_n{std::forward<AFuncN>(afuncs_n)...} {}

  ARES_FUNCTIONAL_DEFINE_CALLOPS()

 private:
  template <typename Obj, typename... Args>
  static constexpr auto impl(Obj& obj, Args&&... args) {
    if constexpr (sizeof...(FuncN) == 0u) {
      return obj.func_1(std::forward<Args>(args)...);
    } else if constexpr (std::is_void_v<std::invoke_result_t<
                             decltype(obj.funcs_n), Args&&...>>) {
      return obj.funcs_n(std::forward<Args>(args)...), obj.func_1();
    } else {
      return obj.func_1(obj.funcs_n(std::forward<Args>(args)...));
    }
  }
};

template <>
struct Compose<> : Constant_function<> {};

template <typename Func1, typename... FuncN>
Compose(Func1&&, FuncN&&...)->Compose<Func1, FuncN...>;
Compose()->Compose<>;

template <typename Predicate, typename Proc>
struct Maybe_function {
  Predicate pred;
  Proc proc;

  constexpr Maybe_function() = default;

  constexpr Maybe_function(Predicate&& pred, Proc&& proc)
      : pred{std::forward<Predicate>(pred)}, proc{std::forward<Proc>(proc)} {}

  ARES_FUNCTIONAL_DEFINE_CALLOPS()

 private:
  template <typename Obj, typename... Args>
  using ObjProcResult =
      std::invoke_result_t<decltype(std::declval<Obj>().proc), Args...>;
  template <typename Obj, typename... Args>
  static constexpr std::optional<
      std::conditional_t<std::is_void_v<ObjProcResult<Obj, Args&&...>>, Unit,
                         ObjProcResult<Obj, Args&&...>>>
  impl(Obj& obj, Args&&... args) {
    if (!obj.pred()) {
      return std::nullopt;
    }

    if constexpr (std::is_void_v<ObjProcResult<Obj, Args&&...>>) {
      obj.proc(std::forward<Args>(args)...);
      return Unit{};
    } else {
      return obj.proc(std::forward<Args>(args)...);
    }
  }
};

template <typename Predicate, typename Proc>
Maybe_function(Predicate&& pred, Proc&& proc)->Maybe_function<Predicate, Proc>;
Maybe_function()->Maybe_function<std::true_type, Constant_function<>>;

template <typename Predicate>
struct Maybe_transfo {
  Predicate pred;

  constexpr Maybe_transfo() = default;

  constexpr Maybe_transfo(Predicate&& pred)
      : pred{std::forward<Predicate>(pred)} {}

  ARES_FUNCTIONAL_DEFINE_CALLOPS()

 private:
  template <typename Obj, typename Func>
  static constexpr auto impl(Obj& obj, Func&& func) {
    return Maybe_function{obj.pred, std::forward<Func>(func)};
  }
};

template <typename Predicate>
Maybe_transfo(Predicate&& pred)->Maybe_transfo<Predicate>;

}  // namespace ares
