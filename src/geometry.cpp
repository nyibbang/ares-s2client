#include "geometry.hpp"

using namespace sc2;

namespace ares {

bool Less_distance::operator()(Point2D a, Point2D b) const {
  return DistanceSquared2D(origin, a) < DistanceSquared2D(origin, b);
}
}
