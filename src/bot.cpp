#include "bot.hpp"
#include <sc2api/sc2_interfaces.h>
#include <chrono>
#include <iomanip>
#include <iostream>
#include "decision.hpp"
#include "functional.hpp"
#include "geometry.hpp"

using namespace sc2;

namespace ares {

namespace {

// TODO: automatically get builder_unit_type
void decide_to_build_supply_depot(Agent &agent) {
  const auto *obs = agent.Observation();

  // If we are not supply capped, don't build a supply depot.
  if (obs->GetFoodUsed() > obs->GetFoodCap() - 2) {
    build_structure(*obs, *agent.Actions(), UNIT_TYPEID::TERRAN_SUPPLYDEPOT);
  }
}

void decide_to_build_refinery(Agent &agent, const Unit &cc) {
  // TODO: find both refineries positions

  // build_structure(agent, UNIT_TYPEID::TERRAN_REFINERY,
  // UNIT_TYPEID::TERRAN_SCV, );
}

using namespace std::chrono;

struct Print_state {
  using clock = steady_clock;

  Print_state(std::ostream &out, milliseconds period = seconds{1})
      : out{&out}, period{period} {}

  void operator()(Agent::Interfaces intf) {
    const auto now = clock::now();
    const auto obs = intf.observation;
    if (now < last_print + period) {
      return;
    }
    *out << "Loop count: " << std::setw(7) << obs->GetGameLoop() << std::setw(0)
         << " | Minerals: " << std::setw(5) << obs->GetMinerals()
         << std::setw(0) << " | Vespene: " << std::setw(5) << obs->GetVespene()
         << std::setw(0) << " | Food: " << std::setw(3) << obs->GetFoodUsed()
         << std::setw(0) << "/" << std::setw(3) << obs->GetFoodCap()
         << std::setw(0) << " (W: " << std::setw(3) << obs->GetFoodWorkers()
         << std::setw(0) << ", A: " << std::setw(3) << obs->GetFoodArmy()
         << std::setw(0) << ")" << std::endl;
    last_print = now;
  }

  std::ostream *out;
  milliseconds period;
  clock::time_point last_print = clock::now();
};

}  // namespace

// void Agent::OnStep() {
//  auto* const obs = Observation();
//  decide_to_build_supply_depot(*this);
//
//  const auto ccs = obs->GetUnits(IsUnit(UNIT_TYPEID::TERRAN_COMMANDCENTER));
//  for (auto* cc : ccs) {
//    decide_to_build_refinery(*this, *cc);
//  }
//}

// void Agent::OnUnitIdle(const Unit* unit) {
//  if (!unit) return;
//  auto* const obs = Observation();
//  switch (unit->unit_type.ToType()) {
//    case UNIT_TYPEID::TERRAN_COMMANDCENTER:
//      std::cout << "Training SCV" << std::endl;
//      Actions()->UnitCommand(unit, ABILITY_ID::TRAIN_SCV);
//      break;
//    case UNIT_TYPEID::TERRAN_SCV: {
//      std::cout << "Sending SCV to minerals" << std::endl;
//      const auto minerals =
//          obs->GetUnits(IsUnit(UNIT_TYPEID::NEUTRAL_MINERALFIELD));
//      const auto minerals_end = end(minerals);
//      const auto closest_mineral_it =
//          nearest_unit(unit->pos, begin(minerals), minerals_end);
//      if (closest_mineral_it != minerals_end) {
//        Actions()->UnitCommand(unit, ABILITY_ID::SMART, *closest_mineral_it);
//      }
//    } break;
//    default:
//      break;
//  }
//}

Agent::Interfaces Agent::interfaces() {
  return {
    Observation(),
    Query(),
    Debug(),
    Actions(),
  };
}

void Agent::OnGameFullStart() { game_fully_started(interfaces()); }

void Agent::OnGameStart() { game_started(interfaces()); }

void Agent::OnGameEnd() { game_ended(interfaces()); }

void Agent::OnStep() { stepped(interfaces()); }

void Agent::OnUnitCreated(const sc2::Unit *unit) { unit_created(interfaces(), unit); }

void Agent::OnUnitDestroyed(const sc2::Unit *unit) { unit_destroyed(interfaces(), unit); }

void Agent::OnUnitIdle(const sc2::Unit *unit) { unit_went_idle(interfaces(), unit); }

void Agent::OnUpgradeCompleted(sc2::UpgradeID id) { upgrade_completed(interfaces(), id); }

void Agent::OnBuildingConstructionComplete(const sc2::Unit *unit) {
  building_construction_completed(interfaces(), unit);
}

void Agent::OnNydusDetected() { nydus_detected(interfaces()); }

void Agent::OnNuclearLaunchDetected() { nuclear_launch_detected(interfaces()); }

void Agent::OnUnitEnterVision(const sc2::Unit *unit) {
  unit_entered_vision(interfaces(), unit);
}

void Agent::OnError(const std::vector<sc2::ClientError> &client_errors,
                    const std::vector<std::string> &protocol_errors) {
  error_occurred(interfaces(), client_errors, protocol_errors);
}

}  // namespace ares
