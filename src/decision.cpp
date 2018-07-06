#include "decision.hpp"
#include "geometry.hpp"
//#include <sc2api/sc2_common.h>

// using namespace sc2;

namespace ares {

using namespace sc2;

// bool Build_supply_depot::condition(const ObservationInterface& obs) const {
//   return obs.GetFoodUsed() > obs.GetFoodCap() - 2;
// }
//
// void Build_supply_depot::execute(const ObservationInterface& obs,
//                                  ActionInterface& act) {
//   build_structure(obs, act, UNIT_TYPEID::TERRAN_SUPPLYDEPOT);
// }
//
// Point2D find_new_building_position(const Point2D& center) {
//   // TODO: decide of a position instead of picking a random one
//   float rx = GetRandomScalar();
//   float ry = GetRandomScalar();
//   return Point2D(center.x + rx * 15.0f, center.y + ry * 15.0f);
// }

bool unit_is_scv(const sc2::Unit& unit) {
  return unit.unit_type.ToType() == UNIT_TYPEID::TERRAN_SCV;
}

void send_scv_to_closest_minerals(const Interfaces& itf, const sc2::Unit& scv) {
  const auto minerals =
      itf.observation->GetUnits(IsUnit(UNIT_TYPEID::NEUTRAL_MINERALFIELD));
  const auto closest_mineral_it =
      nearest_unit(scv.pos, minerals);
  if (closest_mineral_it != end(minerals)) {
    itf.actions->UnitCommand(&scv, ABILITY_ID::SMART, *closest_mineral_it);
  }
}

void start_decision(ares::Agent& agent) {
  //agent.unit_went_idle.connect(Compose{ deref })
}

}  // namespace ares
