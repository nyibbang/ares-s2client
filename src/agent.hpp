#pragma once

#include <sc2api/sc2_agent.h>
#include <boost/signals2/signal.hpp>
#include <functional>
#include <variant>

namespace ares {

class Agent : public sc2::Agent {
 public:
  struct Interfaces {
    const sc2::ObservationInterface *observation;
    sc2::QueryInterface *query;
    sc2::DebugInterface *debug;
    sc2::ActionInterface *actions;
  };

  template <typename... Args>
  using signal_t = boost::signals2::signal<void(Interfaces, Args...)>;
  signal_t<> game_fully_started;
  signal_t<> game_started;
  signal_t<> game_ended;
  signal_t<> stepped;
  signal_t<const sc2::Unit *> unit_created;
  signal_t<const sc2::Unit *> unit_destroyed;
  signal_t<const sc2::Unit *> unit_went_idle;
  signal_t<sc2::UpgradeID> upgrade_completed;
  signal_t<const sc2::Unit *> building_construction_completed;
  signal_t<> nydus_detected;
  signal_t<> nuclear_launch_detected;
  signal_t<const sc2::Unit *> unit_entered_vision;
  signal_t<const std::vector<sc2::ClientError> &,
           const std::vector<std::string> &>
      error_occurred;

 private:
  Interfaces interfaces(); // cannot be const because sc2api getters are not

  // **************************************************************************
  // sc2::Agent interface
  // **************************************************************************
  void OnGameFullStart() final override;
  void OnGameStart() final override;
  void OnGameEnd() final override;
  void OnStep() final override;
  void OnUnitCreated(const sc2::Unit *) final override;
  void OnUnitDestroyed(const sc2::Unit *) final override;
  void OnUnitIdle(const sc2::Unit *) final override;
  void OnUpgradeCompleted(sc2::UpgradeID) final override;
  void OnBuildingConstructionComplete(const sc2::Unit *) final override;
  void OnNydusDetected() final override;
  void OnNuclearLaunchDetected() final override;
  void OnUnitEnterVision(const sc2::Unit *) final override;
  void OnError(const std::vector<sc2::ClientError> &,
               const std::vector<std::string> &) final override;
  // **************************************************************************
};
} // namespace ares
