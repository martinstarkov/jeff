#pragma once
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <Adafruit_BMP280.h>
#include <utility/imumaths.h>
#include <SoftwareSerial.h>
#include <SPI.h>

#define SENSOR_TYPE_TEMPERATURE_BNO 69420
#define SENSOR_TYPE_TEMPERATURE_BMP 69422
#define SENSOR_TYPE_PRESSURE 69424
#define SENSOR_TYPE_ALTITUDE 69426
#define SENSOR_TYPE_SEA_PRESSURE 69428
  
#define BMP_AMOUNT 4 // amount of BMPs attached to teensy ports

#define BLUETOOTH_RX 0 // (TX on bluetooth module)
#define BLUETOOTH_TX 1 // (RX on bluetooth module)
#define BLUETOOTH_BAUD_RATE 9600 // data mode: 9600, command mode: 38400

#define SERIAL_BAUD_RATE 9600 // 115200 / 9600

#define BNO_ID 55
#define BNO_ADDRESS 0x29

#define REFRESH_DELAY 100 // milliseconds

#define STANDARD_PRESSURE 1005 // hPa (obtained from local weather forecast: https://www.worldweatheronline.com/edinburgh-weather/city-of-edinburgh/gb.aspx)
        
class SensorController {
    private:
        uint8_t BMPAddresses[2] = { 0x76, 0x77 };
        Adafruit_BNO055* bno;
        Adafruit_BMP280* bmps[BMP_AMOUNT];
        int initalizedBmps = 0;
        float getAverageAltitude();
        float getAveragePressure();
        float getAverageTemperature();
        String debugPrints();
        char lastUserInput;
        SoftwareSerial* BT;

        sensors_event_t orientationData, angVelocityData, linearAccelData, accelerometerData, magnetometerData, gravityData; 
    public:
        void BTPrint(String text);
        void init();
        void initBNO();
        void initBMP(TwoWire *theWire, uint8_t address);
        void recordData();
        void bluetoothListener();
        float getAltitude();
        float getPressure();
        float getTemperature();

        bool bmpDebugTemperature = false;
        bool bmpDebugPressure = false;
        bool bmpDebugAltitude = false;
};
