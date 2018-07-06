#pragma once

#include <sc2api/sc2_common.h>
#include <sc2api/sc2_unit.h>
#include <boost/iterator/transform_iterator.hpp>
#include "functional.hpp"
#include "utility.hpp"

namespace ares {

inline sc2::Point2D unit_position(const sc2::Unit* unit) { return unit->pos; }

struct Less_distance {
  sc2::Point2D origin;
  bool operator()(const sc2::Point2D& a, const sc2::Point2D& b) const;
};

/// Range<Unit*>
template <typename FwdIter>
FwdIter nearest_unit(const sc2::Point2D& origin, FwdIter begin, FwdIter end) {
  return std::min_element(boost::make_transform_iterator(begin, &unit_position),
                          boost::make_transform_iterator(end, &unit_position),
                          Less_distance{origin})
      .base();
}

/// Range<Unit*>
template <typename Range>
auto nearest_unit(const sc2::Point2D& origin, Range&& range) {
  return nearest_unit(origin, begin(range), end(range));
}
}  // namespace ares
