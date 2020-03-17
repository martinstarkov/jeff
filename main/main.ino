#include "FlightController.h"
#include "Defines.h"

FlightController* fc;

void setup() {
  fc = new FlightController();
}

void loop() {
  fc->cycle();
  delay(READ_REFRESH_DELAY);
}
