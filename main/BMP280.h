#pragma once
#include <Adafruit_BMP280.h>
        
class BMP280 {
    private:
      Adafruit_BMP280* instance;
      
      float address;
      float standardPressure;
      TwoWire* wire;
      
      float pressure;
      float temperature;
      float altitude;
    public:
      BMP280(TwoWire* wire, uint8_t address, float standardPressure);
      float getPressure();
      float getTemperature();
      float getAltitude();
};
