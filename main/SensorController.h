#pragma once
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <SPI.h>
#include "BMP280.h"
#include "BNO055.h"
#include "Bluetooth.h"
#include "Data.h"
#include "Defines.h"
  
class SensorController {
    private:
      // BMP
      int bmpCount;
      void initBMPs();
      uint8_t BMPAddresses[2] = { 0x76, 0x77 };
      BMP280* bmps[BMP_AMOUNT];
      // BNO
      int bnoCount;
      void initBNOs();
      uint8_t BNOAddresses[1] = { 0x29 };
      int BNOIds[1] = { 55 };
      BNO055* bnos[BNO_AMOUNT];

      template <typename Array, typename Data, typename Sensor> Data average(Array sensorArray, int count, Data (Sensor::*functionPointer)());
    public:
      SensorController();
      ProcessedData getProcessedData();
      RawData getRawData();
};
