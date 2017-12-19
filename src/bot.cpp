#include "bot.hpp"
#include <sc2api/sc2_interfaces.h>
#include <iomanip>
#include <iostream>
#include "decision.hpp"
#include "functional.hpp"
#include "geometry.hpp"

using namespace sc2;

namespace ares {

namespace {

// TODO: automatically get builder_unit_type
void decide_to_build_supply_depot(Agent& agent) {
  const auto* obs = agent.Observation();

  // If we are not supply capped, don't build a supply depot.
  if (obs->GetFoodUsed() > obs->GetFoodCap() - 2) {
    build_structure(*obs, *agent.Actions(), UNIT_TYPEID::TERRAN_SUPPLYDEPOT);
  }
}

void decide_to_build_refinery(Agent& agent, const Unit& cc) {
  // TODO: find both refineries positions

  // build_structure(agent, UNIT_TYPEID::TERRAN_REFINERY,
  // UNIT_TYPEID::TERRAN_SCV, );
}
}

Bot::Bot() : _lastStepPrint(std::chrono::system_clock::now()) {}

void Bot::OnGameStart() { std::cout << "Game started" << std::endl; }

void Bot::OnStep() {
  auto* const obs = Observation();
  const auto now = std::chrono::system_clock::now();
  if (now - std::chrono::seconds(1) > _lastStepPrint) {
    std::cout << "Loop count: " << std::setw(7) << obs->GetGameLoop()
              << std::setw(0) << " | Minerals: " << std::setw(5)
              << obs->GetMinerals() << std::setw(0)
              << " | Vespene: " << std::setw(5) << obs->GetVespene()
              << std::setw(0) << " | Food: " << std::setw(3)
              << obs->GetFoodUsed() << std::setw(0) << "/" << std::setw(3)
              << obs->GetFoodCap() << std::setw(0) << " (W: " << std::setw(3)
              << obs->GetFoodWorkers() << std::setw(0)
              << ", A: " << std::setw(3) << obs->GetFoodArmy() << std::setw(0)
              << ")" << std::endl;
    _lastStepPrint = now;
  }

  decide_to_build_supply_depot(*this);

  const auto ccs = obs->GetUnits(IsUnit(UNIT_TYPEID::TERRAN_COMMANDCENTER));
  for (auto* cc : ccs) {
    decide_to_build_refinery(*this, *cc);
  }
}

void Bot::OnUnitCreated(const Unit* unit) {
  if (!unit) return;
  std::cout << "Unit " << UnitTypeToName(unit->unit_type) << " created"
            << std::endl;
}

void Bot::OnUnitIdle(const Unit* unit) {
  if (!unit) return;
  auto* const obs = Observation();
  switch (unit->unit_type.ToType()) {
    case UNIT_TYPEID::TERRAN_COMMANDCENTER:
      std::cout << "Training SCV" << std::endl;
      Actions()->UnitCommand(unit, ABILITY_ID::TRAIN_SCV);
      break;
    case UNIT_TYPEID::TERRAN_SCV: {
      std::cout << "Sending SCV to minerals" << std::endl;
      const auto minerals =
          obs->GetUnits(IsUnit(UNIT_TYPEID::NEUTRAL_MINERALFIELD));
      const auto minerals_end = end(minerals);
      const auto closest_mineral_it =
          nearest_unit(unit->pos, begin(minerals), minerals_end);
      if (closest_mineral_it != minerals_end) {
        Actions()->UnitCommand(unit, ABILITY_ID::SMART, *closest_mineral_it);
      }
    } break;
    default:
      break;
  }
}
}
