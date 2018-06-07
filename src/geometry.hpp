#pragma once

#include <sc2api/sc2_common.h>

namespace ares {

struct Less_distance {
  sc2::Point2D origin;
  bool operator()(const sc2::Point2D& a, const sc2::Point2D& b) const;
};

/// Range<Unit*>
template <typename FwdIter>
auto nearest_unit(sc2::Point2D origin, FwdIter begin, FwdIter end) {
  return std::min_element(
      begin, end,
      make_domain_projection_function(Less_distance{origin},
                                      [](auto* unit) { return unit->pos; }));
}

/// Range<Unit*>
template <typename Range>
auto nearest_unit(sc2::Point2D origin, Range range) {
  return nearest_unit(origin, begin(range), end(range));
}
}  // namespace ares
