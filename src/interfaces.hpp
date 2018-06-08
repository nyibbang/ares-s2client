#include <sc2api/sc2_interfaces.h>

namespace ares {

struct Interfaces {
  const sc2::ObservationInterface *observation;
  sc2::QueryInterface *query;
  sc2::DebugInterface *debug;
  sc2::ActionInterface *actions;
};

}  // namespace ares
