#pragma once
#include <Adafruit_BMP280.h>
        
class BMP280 {
    private:
      float standardPressure;
      float pressure;
      float temperature;
      float altitude;
    public:
      BMP280(TwoWire* theWire, uint8_t address, );
      void setStandardPressure(float pressure);
      float getPressure();
      float getTemperature();
      float getAltitude()
};
