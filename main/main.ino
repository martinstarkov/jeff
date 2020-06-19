#include "FlightComputer.h"

#define REFRESH_DELAY 0

FlightComputer* fc = nullptr;

void setup() {
  fc = FlightComputer::getInstance();
}

void loop() {
  fc->update();
  delay(REFRESH_DELAY);
}
