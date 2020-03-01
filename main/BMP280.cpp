#include "BMP280.h"

BMP280(TwoWire* theWire, uint8_t address) {
  
}

void BMP280::setStandardPressure(float pressure) {
  standardPressure = pressure;
}

float BMP280::getPressure() {
  return ->readPressure();
}
