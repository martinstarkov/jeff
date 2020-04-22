#include "FlightComputer.h"
#include "Serials.h"

#define REFRESH_DELAY 0

FlightComputer* fc;

void setup() {
  Serials::begin();
  fc = FlightComputer::getInstance();
}

void loop() {
  fc->update();
  delay(REFRESH_DELAY);
}
