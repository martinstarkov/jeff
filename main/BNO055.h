#pragma once
#include <Adafruit_BNO055.h>
        
class BNO055 {
    private:
      int id;
      uint8_t address;
      Adafruit_BNO055* instance;
    public:
      BNO055(int id, uint8_t address);
};
