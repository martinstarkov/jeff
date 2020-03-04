#pragma once
#include <Adafruit_BMP280.h>
        
class BMP280 {
    private:
      float sPressure;
      float pressure;
      float temperature;
      float altitude;
      Adafruit_BMP280* instance;
    public:
      BMP280(TwoWire* theWire, uint8_t address, float standardPressure);
      float getPressure();
      float getTemperature();
      float getAltitude();
};
