#include "decision.hpp"
#include <sc2api/sc2_common.h>

using namespace sc2;

namespace ares {

Point2D find_new_building_position(const Point2D& center) {
  // TODO: decide of a position instead of picking a random one
  float rx = GetRandomScalar();
  float ry = GetRandomScalar();
  return Point2D(center.x + rx * 15.0f, center.y + ry * 15.0f);
}
}
