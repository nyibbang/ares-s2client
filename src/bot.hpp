#pragma once

#include <sc2api/sc2_agent.h>
#include <chrono>

namespace ares {

class Bot : public sc2::Agent {
 public:
  Bot();

  void OnGameStart() final override;
  void OnStep() final override;
  void OnUnitCreated(const sc2::Unit* unit) final override;
  void OnUnitIdle(const sc2::Unit* unit) final override;

 private:
  std::chrono::system_clock::time_point _lastStepPrint;
};
}
