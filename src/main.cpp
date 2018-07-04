#include "agent.hpp"
#include "config.hpp"
#ifdef ARES_DEBUG
#include "debug.hpp"
#endif
#include <sc2api/sc2_api.h>

using namespace sc2;

int main(int argc, char* argv[]) {
  Coordinator coordinator;
  coordinator.LoadSettings(argc, argv);
  coordinator.SetWindowLocation(0, 0);

  ares::Agent agent;

#ifdef ARES_DEBUG
  agent.stepped.connect(ares::Print_state{std::cout});
#endif

  coordinator.SetParticipants(
      {CreateParticipant(Race::Terran, &agent), CreateComputer(Race::Random)});

  coordinator.LaunchStarcraft();
  coordinator.StartGame(std::string{ARES_ROOT} + "/contrib/s2client-api/maps/" +
                        sc2::kMapBelShirVestigeLE);
  while (coordinator.Update()) {
  }
  return 0;
}
