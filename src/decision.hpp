#pragma once

//#include <deque>
//#include <sc2api/sc2_common.h>
//#include <sc2api/sc2_interfaces.h>

namespace ares {

// struct EffectCostRatio {
//  int effect_estimation;
//  int cost_estimation;
//
//  bool operator<(const EffectCostRatio& o) {
//    const auto l = static_cast<long long>(effect_estimation)   *
//    o.cost_estimation;
//    const auto r = static_cast<long long>(o.effect_estimation) *
//    cost_estimation;
//    return l < r;
//  }
//};
//
// struct Action {
//  virtual EffectCostRatio effectCostRatio() const = 0;
//  virtual void execute() = 0;
//};
//
// struct Less_useful_action {
//  bool operator()(const Action& a, const Action& b) {
//    return a.effectCostRatio() < b.effectCostRatio();
//  }
//};
//
// using Action_queue = std::deque<Action>;

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
}  // namespace ares
