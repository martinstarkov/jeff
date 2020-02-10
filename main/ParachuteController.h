#pragma once
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <Adafruit_BMP280.h>
#include <utility/imumaths.h>
#include <SPI.h>
#include "Vector.h"
        
class ParachuteController {
    private:
      int decreasedAltitudesThreshold = 10;
      float previousAltitude = -99999999999999;
      float altitudeSafetyFactor = 0.25;
    public:
      void init();
      bool deploymentCheck(float currentAltitude);
};
