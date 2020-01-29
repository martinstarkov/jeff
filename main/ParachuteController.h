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
      int samples = 10;
      Vector<float> altitudes;
    public:
      void init();
      bool deploymentCheck(float currentAltitude);
};
