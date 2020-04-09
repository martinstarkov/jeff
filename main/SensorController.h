#pragma once
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <math.h>
#include <SPI.h>
#include "BMP280.h"
#include "BNO055.h"
#include "Bluetooth.h"
#include "Vector3D.h"
#include "Defines.h"

class SensorInterface {
  public:
//    virtual float getPressure() = 0;
//    virtual float getAltitude() = 0;
//    virtual float getTemperature() = 0;
};

class SensorController : public SensorInterface {
    private:
      BMP280* bmps[BMPS];
      BNO055* bnos[BNOS];
      uint8_t bmpAddresses[2] = { BMP_I2C_1, BMP_I2C_2 };
      uint8_t bnoAddresses[1] = { BNO_I2C_1 };
      template <typename Sensor> 
      void initI2C(int count, Sensor* sensors[], uint8_t* addresses);
      template <typename Data, typename Sensor>
      Data average(int count, Sensor* sensors[], Data (Sensor::*functionPointer)());
    public:
      SensorController();
      void init();
      float getAltitude();
      Vector3D getOrientation();
};
