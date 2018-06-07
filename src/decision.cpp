#include "decision.hpp"
//#include <sc2api/sc2_common.h>

//using namespace sc2;

namespace ares {

// bool build_structure(const ObservationInterface& obs,
//                      ActionInterface& act, UNIT_TYPEID unit_type,
//                      UNIT_TYPEID builder_unit_type,
//                      boost::optional<Point2D> position) {
//   const auto unit_typedata = obs.GetUnitTypeData()[UnitTypeID(unit_type)];
//   const auto ability_id =
//       GetGeneralizedAbilityID(unit_typedata.ability_id, obs);
//
//   if (obs.GetMinerals() < unit_typedata.mineral_cost ||
//       obs.GetVespene() < unit_typedata.vespene_cost) {
//     return false;
//   }
//
//   // If a unit already is building a supply structure of this type, do
//   nothing.
//   // Also get an scv to build the structure.
//   // TODO: choosing a unit to build the structure should be part of decision
//   const auto units =
//       obs.GetUnits(Unit::Alliance::Self, IsUnit(builder_unit_type));
//   for (const auto* unit : units) {
//     for (const auto& order : unit->orders) {
//       if (order.ability_id == ability_id) {
//         return false;
//       }
//     }
//   }
//
//   if (units.empty()) {
//     return false;
//   }
//
//   const auto* builder = units.front();
//
//   if (!position) {
//     position = find_new_building_position(builder->pos);
//   }
//
//   std::cout << "Building structure " << UnitTypeToName(unit_type) <<
//   std::endl; act.UnitCommand(builder, ability_id, *position); return true;
// }
//
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
}
