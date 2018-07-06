#pragma once

#include "agent.hpp"

namespace ares {

// bool build_structure(
//     const sc2::ObservationInterface& obs, sc2::ActionInterface& act,
//     sc2::UNIT_TYPEID unit_type,
//     sc2::UNIT_TYPEID builder_unit_type = sc2::UNIT_TYPEID::TERRAN_SCV,
//     boost::optional<sc2::Point2D> position = {});
//
// struct Build_supply_depot {
//   bool condition(const sc2::ObservationInterface& obs) const;
//   void execute(const sc2::ObservationInterface& obs, sc2::ActionInterface&
//   act);
// };
//
// sc2::Point2D find_new_building_position(const sc2::Point2D& center);

void start_decision(ares::Agent& agent);

}  // namespace ares
