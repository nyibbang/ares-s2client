#include "geometry.hpp"

using namespace sc2;

namespace ares {

bool Less_distance::operator()(const Point2D& a, const Point2D& b) const {
  return DistanceSquared2D(origin, a) < DistanceSquared2D(origin, b);
}
}  // namespace ares
