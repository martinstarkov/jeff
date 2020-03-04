#include "BNO055.h"

BNO055::BNO055(int id, uint8_t address) {
  id = id;
  address = address;
  instance = new Adafruit_BNO055(id, address);
  
  if (!instance->begin()) {
    // BNO sensor not detected. Check wiring.
    // while (1) {}
  }
}
