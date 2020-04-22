#include "FlightComputer.h"

FlightComputer* FlightComputer::instance = 0;

FlightComputer* FlightComputer::getInstance() {
  if (!instance) {
    instance = new FlightComputer();
  }
  return instance;
}

FlightComputer::FlightComputer() {
  // sub systems
  sm = new StateMachine();
  ds = new DataService();
}

void FlightComputer::update() { // update every flight component for each microcontroller cycle
  ds->update();
  sm->update();
}

//void CommunicationController::restartTeensy() { // Restart teensy programmatically
//  // Make sure (at least how it was implemented online, need to test this) to end serials before this call
//  end();
//  SCB_AIRCR = 0x05FA0004; // write value for restart
//}
