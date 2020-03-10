#pragma once
#include <Adafruit_BMP280.h>
#include "Bluetooth.h"
        
class BMP280 {
    private:
    
      Adafruit_BMP280* instance;
      
      TwoWire* wire;
      uint8_t address;
      float standardPressure;
      bool status = false;
      
    public:
    
      BMP280(TwoWire* wire, uint8_t address, float standardPressure);
      bool initialized();
      
      float getPressure();
      float getTemperature();
      float getAltitude();
};
