#pragma once

#include "interfaces.hpp"
#include <chrono>
#include <iostream>

namespace ares {

struct Print_state {
  using clock = std::chrono::steady_clock;

  explicit Print_state(std::ostream &out,
                       std::chrono::milliseconds period = std::chrono::seconds{
                           1});
  void operator()(Interfaces intf);

  std::ostream *out;
  std::chrono::milliseconds period;
  clock::time_point last_print = clock::now();
};

}  // namespace ares
