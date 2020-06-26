#include "FlightComputer.h"
#include "Serials.h"
#include "Defines.h"
#include "DataInterface.h"
#include <limits.h>

FlightComputer* fc = nullptr;

uint64_t startTime = 0;
uint64_t endTime = 0;
uint64_t counter = 0;

constexpr uint64_t BENCHMARK = 100;//1000000000; // 10

char * uintToStr( const uint64_t num, char *str )
{
  uint8_t i = 0;
  uint64_t n = num;
 
  do
    i++;
  while ( n /= 10 );
 
  str[i] = '\0';
  n = num;
 
  do
    str[--i] = ( n % 10 ) + '0';
  while ( n /= 10 );

  return str;
}

char str[21];

void setup() {
  Serials::begin(SERIAL_BAUD);
  fc = FlightComputer::getInstance();
  DataInterface::getInstance()->getProcessedData().altitude = 30.0f;
  DataInterface::getInstance()->getProcessedData().orientation = Vector3D(1.0f, 1.0f, 1.0f);
  DataInterface::getInstance()->getProcessedData().angularVelocity = Vector3D(2.0f, 2.0f, 2.0f);
  DataInterface::getInstance()->getProcessedData().linearAcceleration = Vector3D(3.0f, 3.0f, 3.0f);
  DataInterface::getInstance()->getProcessedData().netAcceleration = Vector3D(4.0f, 4.0f, 4.0f);
  Serial.println(uintToStr((millis() - startTime), str));
}

void loop() {
  if (counter == 0) {
    startTime = millis();
  } else if (counter < BENCHMARK) {
    fc->update();
  } else if (counter == BENCHMARK) {
    Serial.println(uintToStr((millis() - startTime), str));
    AllocationMetrics::printMemoryUsage();
  }
  counter++;
}
