#include "FlightComputer.h"

FlightComputer* FlightComputer::instance = 0;

FlightComputer* FlightComputer::getInstance() {
  if (!instance) {
    instance = new FlightComputer();
  }
  return instance;
}

FlightComputer::FlightComputer() {
  // Sub system initialization
  sm = new StateMachine();
  ds = new DataService();
}

void FlightComputer::update() { // update every flight component for each microcontroller cycle
  ds->update();
  sm->update();
}
