#include "bot.hpp"
#include "functional.hpp"
#include <boost/optional.hpp>
#include <iomanip>
#include <iostream>

using namespace sc2;

namespace ares {

namespace {

struct Less_distance {
  Point2D origin;
  bool operator()(Point2D a, Point2D b) const {
    return DistanceSquared2D(origin, a) < DistanceSquared2D(origin, b);
  }
};

/// Range<Unit*>
template <typename FwdIter>
auto nearest_unit(Point2D origin, FwdIter begin, FwdIter end) {
  return std::min_element(
      begin, end,
      make_domain_projection_function(Less_distance{origin},
                                      [](auto* unit) { return unit->pos; }));
}

/// Range<Unit*>
template <typename R>
auto nearest_unit(Point2D origin, R range) {
  return nearest_unit(origin, begin(range), end(range));
}

// TODO: automatically get builder_unit_type
bool build_structure(Agent& agent, UNIT_TYPEID unit_type,
                     UNIT_TYPEID builder_unit_type = UNIT_TYPEID::TERRAN_SCV,
                     boost::optional<Point2D> position = {}) {
  const auto* obs = agent.Observation();

  const auto unit_typedata = obs->GetUnitTypeData()[UnitTypeID(unit_type)];
  const auto ability_id =
      GetGeneralizedAbilityID(unit_typedata.ability_id, *obs);

  if (obs->GetMinerals() < unit_typedata.mineral_cost ||
      obs->GetVespene() < unit_typedata.vespene_cost) {
    return false;
  }

  // If a unit already is building a supply structure of this type, do nothing.
  // Also get an scv to build the structure.
  const auto units =
      obs->GetUnits(Unit::Alliance::Self, IsUnit(builder_unit_type));
  for (const auto* unit : units) {
    for (const auto& order : unit->orders) {
      if (order.ability_id == ability_id) {
        return false;
      }
    }
  }

  if (units.empty()) {
    return false;
  }

  const auto* builder = units.front();

  if (!position) {
    float rx = GetRandomScalar();
    float ry = GetRandomScalar();
    position =
        Point2D(builder->pos.x + rx * 15.0f, builder->pos.y + ry * 15.0f);
  }
  std::cout << "Building structure " << UnitTypeToName(unit_type) << std::endl;
  agent.Actions()->UnitCommand(builder, ability_id, *position);
  return true;
}

void decide_to_build_supply_depot(Agent& agent) {
  const auto* obs = agent.Observation();

  // If we are not supply capped, don't build a supply depot.
  if (obs->GetFoodUsed() > obs->GetFoodCap() - 2) {
    build_structure(agent, UNIT_TYPEID::TERRAN_SUPPLYDEPOT);
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
