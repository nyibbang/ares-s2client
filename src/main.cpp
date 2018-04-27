#include <sc2api/sc2_api.h>
#include "bot.hpp"

using namespace sc2;

//
// Decision:
// Based on a condition verified in an environment/context,
// we take an action.
//
// Unit allocation:
// To be defined
//
// Learning:
// To be defined
//
//

int main(int argc, char* argv[]) {
  Coordinator coordinator;
  coordinator.LoadSettings(argc, argv);
  coordinator.SetWindowLocation(0, 0);

  ares::Agent agent;
  coordinator.SetParticipants(
      {CreateParticipant(Race::Terran, &agent), CreateComputer(Race::Random)});

  coordinator.LaunchStarcraft();
  coordinator.StartGame(std::string{ARES_ROOT} + "/contrib/s2client-api/maps/" +
                        sc2::kMapBelShirVestigeLE);
  while (coordinator.Update()) {
  }
  return 0;
}
