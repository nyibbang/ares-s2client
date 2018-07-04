#include "debug.hpp"
#include <iomanip>

namespace ares {

Print_state::Print_state(std::ostream &out, std::chrono::milliseconds period)
    : out{&out}, period{period} {}

void Print_state::operator()(Interfaces intf) {
  const auto now = clock::now();
  if (now < last_print + period) {
    return;
  }
  const auto obs = intf.observation;
  *out << "Loop count: " << std::setw(7) << obs->GetGameLoop() << std::setw(0)
       << " | Minerals: " << std::setw(5) << obs->GetMinerals() << std::setw(0)
       << " | Vespene: " << std::setw(5) << obs->GetVespene() << std::setw(0)
       << " | Food: " << std::setw(3) << obs->GetFoodUsed() << std::setw(0)
       << "/" << std::setw(3) << obs->GetFoodCap() << std::setw(0)
       << " (W: " << std::setw(3) << obs->GetFoodWorkers() << std::setw(0)
       << ", A: " << std::setw(3) << obs->GetFoodArmy() << std::setw(0) << ")"
       << std::endl;
  last_print = now;
}

}  // namespace ares
