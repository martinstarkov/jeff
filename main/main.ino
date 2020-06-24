#include "FlightComputer.h"
#include "Serials.h"
#include "Defines.h"

FlightComputer* fc = nullptr;

void setup() {
  Serials::begin(SERIAL_BAUD);
  fc = FlightComputer::getInstance();
}

void loop() {
  fc->update();
  //AllocationMetrics::printMemoryUsage();
  delay(1000); // Comment for final use
}
