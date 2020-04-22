#pragma once
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <math.h>
#include <SPI.h>
#include "BMP280.h"
#include "BNO055.h"
#include "Defines.h"
#include "Vector3D.h"
#include "Data.h"

class SensorController {
    private:
      int bmpCount = 0;
      BMP280* bmps[BMPS];
      int bnoCount = 0;
      BNO055* bnos[BNOS];
      uint8_t BMPAddresses[2] = { BMP_I2C_1, BMP_I2C_2 };
      uint8_t BNOAddresses[1] = { BNO_I2C_1 };
      void logRawValues();
      template <typename Data, typename Sensor>
      Data average(int count, Sensor* sensors[], Data (Sensor::*functionPointer)());
//      template <typename Sensor> 
//      void initI2C(int count, Sensor* sensors[], uint8_t* addresses);
    public:
      SensorController();
      void init();
      void initBMPs();
      void initBNOs();
      void update();
};
