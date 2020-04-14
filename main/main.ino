#include "FlightController.h"
#include "Defines.h"

FlightController* fc;

void setup() {
  fc = FlightController::getInstance();
}

void loop() {
  fc->update();
  delay(READ_REFRESH_DELAY);
}
