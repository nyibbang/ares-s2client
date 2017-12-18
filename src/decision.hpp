#pragma once

//#include <deque>
//#include <queue>
#include <sc2api/sc2_common.h>

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

sc2::Point2D find_new_building_position(const sc2::Point2D& center);
}
