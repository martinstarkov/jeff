#pragma once
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <Adafruit_BMP280.h>

#define SENSOR_TYPE_TEMPERATURE 69420
        
class SensorController {
    private:
        int32_t sensorID = 55;
        uint8_t address = 0x29;
        Adafruit_BNO055* bno;

        sensors_event_t orientationData, angVelocityData, linearAccelData, accelerometerData, magnetometerData, gravityData, temperatureData;

        Adafruit_BMP280 bmp1;
        Adafruit_BMP280 bmp2;
        Adafruit_BMP280 bmp3;

        int bmp1Data[3] = {0};
        int bmp2Data[3] = {0};
        int bmp3Data[3] = {0};
        int bmpCorrectedData[3] = {0};

        //Thresholds for BMP error correction 
        //TODO: change threshold values to appropriate values
        const int bmpTemp_Threshold = 5;
        const int bmpPressure_Threshold = 5;
        const int bmpAltitude_Threshold = 5;
        
    public:
        uint16_t refresh_delay = 100; // milliseconds
        
        void init();
        void initBNO();
        Adafruit_BNO055* getBNO() {
          return bno;
        }
        
        void initBMPs();
        Adafruit_BMP280 getBMP1(){
          return bmp1;
        }
        Adafruit_BMP280 getBMP2(){
          return bmp2;
        }
        Adafruit_BMP280 getBMP3(){
          return bmp3;
        }
        
        void recordData();
        void correctData();
        sensors_event_t* getData(String type);
        void printData(sensors_event_t* event);
        void readData();
        void printBMPData();
        
        //void initBMP();
};
