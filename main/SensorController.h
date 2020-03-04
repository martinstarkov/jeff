#pragma once
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <SPI.h>
#include "BMP280.h"
#include "Bluetooth.h"
#include "DataService.h"

#define SENSOR_TYPE_TEMPERATURE_BNO 69420
#define SENSOR_TYPE_TEMPERATURE_BMP 69422
#define SENSOR_TYPE_PRESSURE 69424
#define SENSOR_TYPE_ALTITUDE 69426
#define SENSOR_TYPE_SEA_PRESSURE 69428
  
#define BMP_AMOUNT 4 // amount of BMPs attached to teensy ports

#define SERIAL_BAUD_RATE 9600 // 115200 / 9600

#define BNO_ID 55
#define BNO_ADDRESS 0x29

#define REFRESH_DELAY 100 // milliseconds

#define STANDARD_PRESSURE 1005 // hPa (obtained from local weather forecast: https://www.worldweatheronline.com/edinburgh-weather/city-of-edinburgh/gb.aspx)
        
class SensorController {
    private:
        uint8_t BMPAddresses[2] = { 0x76, 0x77 };
        Adafruit_BNO055* bno;
        BMP280* bmps[BMP_AMOUNT];
        int initalizedBmps = 0;
        float getAverageAltitude();
        float getAveragePressure();
        float getAverageTemperature();
        void debugPrints();
        bool bmpDebugTemperature = false;
        bool bmpDebugPressure = false;
        bool bmpDebugAltitude = false;
        SoftwareSerial* BT;
        SoftwareSerial* GPS;
        void initBMPs();

        sensors_event_t orientationData, angVelocityData, linearAccelData, accelerometerData, magnetometerData, gravityData; 
    public:
        void init();
        void update();
        void initBNO();
        void recordData();
        float getAltitude();
        float getPressure();
        float getTemperature();
};
