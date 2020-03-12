#pragma once
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <SPI.h>
#include "BMP280.h"
#include "BNO055.h"
#include "Bluetooth.h"
#include "DataService.h"

#define SENSOR_TYPE_TEMPERATURE_BNO 69420
#define SENSOR_TYPE_TEMPERATURE_BMP 69422
#define SENSOR_TYPE_PRESSURE 69424
#define SENSOR_TYPE_ALTITUDE 69426
#define SENSOR_TYPE_SEA_PRESSURE 69428
  
#define BMP_AMOUNT 4 // amount of BMPs attached to teensy
#define BNO_AMOUNT 1 // amount of BNOs attached to teensy

#define STANDARD_PRESSURE 1005 // hPa (obtained from local weather forecast: https://www.worldweatheronline.com/edinburgh-weather/city-of-edinburgh/gb.aspx)
        
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
        void init();
        void update();
};
