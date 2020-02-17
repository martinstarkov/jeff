#pragma once
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <Adafruit_BMP280.h>
#include <utility/imumaths.h>
#include <SPI.h>

#define SENSOR_TYPE_TEMPERATURE_BNO 69420
#define SENSOR_TYPE_TEMPERATURE_BMP 69422
#define SENSOR_TYPE_PRESSURE 69424
#define SENSOR_TYPE_ALTITUDE 69426
#define SENSOR_TYPE_SEA_PRESSURE 69428
#define BMP_AMOUNT 4
        
class SensorController {
    private:
        int32_t sensorID = 55;
        uint8_t BNOAddress = 0x29;
        uint8_t BMPAddress = 0x76;
        uint8_t addresses[2] = { 0x76, 0x77 };
        Adafruit_BNO055* bno;
        Adafruit_BMP280* bmps[BMP_AMOUNT];
        int initalizedBmps = 0;
        float getAverageAltitude(float standardPressure);
        
        sensors_event_t orientationData, angVelocityData, linearAccelData, accelerometerData, magnetometerData, gravityData, bnoTemperatureData, bmpTemperatureData, pressureData, altitudeData, seaPressureData;
    public:
        uint16_t refresh_delay = 1000; // milliseconds
        
        void init();
        void initBNO();
        void initBMP(TwoWire *theWire, uint8_t address);
        void recordData();
        sensors_event_t* getData(String type);
        void printData(sensors_event_t* event);
        void readData();
        float getAltitude(float standardPressure);
        float getPressure();
        //void initBMP();
};
