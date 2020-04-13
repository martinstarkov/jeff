#include "FlightController.h"

FlightController* FlightController::instance = 0;

FlightController* FlightController::getInstance() {
  if (!instance) {
    instance = new FlightController();
  }
  return instance;
}

FlightController::FlightController() {
  // sub systems
  sm = new StateMachine();
  ds = new DataService();
}

void FlightController::restart() { // Restart teensy programmatically
  //Bluetooth::clear();
  SCB_AIRCR = 0x05FA0004; // write value for restart
}

void FlightController::cycle() { // update every flight component for each microcontroller cycle
  //ds->update();
  //sm->update();
}
