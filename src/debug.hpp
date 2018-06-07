#include <chrono>
#include <iostream>

namespace ares {

struct Print_state {
  using clock = std::chrono::steady_clock;

  Print_state(std::ostream &out, std::chrono::milliseconds period = seconds{1});
  void operator()(Agent::Interfaces intf);

  std::ostream *out;
  std::chrono::milliseconds period;
  clock::time_point last_print = clock::now();
};


}
