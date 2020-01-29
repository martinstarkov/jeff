#pragma once
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#define SENSOR_TYPE_TEMPERATURE 69420
        
class SensorController {
    private:
        int32_t sensorID = 55;
        uint8_t address = 0x29;
        Adafruit_BNO055* bno;
        
        sensors_event_t orientationData, angVelocityData, linearAccelData, accelerometerData, magnetometerData, gravityData, temperatureData;
    public:
        uint16_t refresh_delay = 100; // milliseconds
        
        void init();
        void initBNO();
        Adafruit_BNO055* getBNO() {
          return bno;
        }
        void recordData();
        sensors_event_t* getData(String type);
        void printData(sensors_event_t* event);
        void readData();
        float getAltitude();
        
        //void initBMP();
};
