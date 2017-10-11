#pragma once

template <typename T>
struct Polymorphic_constant_function {
  T value;
  template <typename... Args>
  T operator()(Args&&...) const noexcept {
    return value;
  }
};

template <typename T>
auto make_polymorphic_constant_function(T&& value) {
  return Polymorphic_constant_function<T>{std::forward<T>(value)};
}

template <typename F, typename P>
struct Domain_projection_function {
  F f;
  P proj;
  template <typename... Args>
  auto operator()(Args&&... args) {
    return f(proj(std::forward<Args>(args))...);
  }
};

template <typename F, typename P>
auto make_domain_projection_function(F&& f, P&& proj) {
  return Domain_projection_function<F, P>{std::forward<F>(f),
                                          std::forward<P>(proj)};
}
