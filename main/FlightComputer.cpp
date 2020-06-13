#include "FlightComputer.h"

FlightComputer* FlightComputer::_instance = nullptr;

FlightComputer* FlightComputer::getInstance() {
  if (!_instance) {
    _instance = new FlightComputer();
  }
  return _instance;
}

FlightComputer::FlightComputer() {
  // Sub system initialization
  _sm = new StateMachine();
  _ds = new DataService();
}

FlightComputer::~FlightComputer() {
  delete _sm;
  delete _ds;
  _sm = nullptr;
  _ds = nullptr;
}

void FlightComputer::update() { // update every flight component for each microcontroller cycle
  _ds->update();
  _sm->update();
}

/*
void FlightComputer::clean() {
  delete instance;
  instance = nullptr;
}
*/
