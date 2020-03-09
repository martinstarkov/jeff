#pragma once
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include "Bluetooth.h"
#include "Vector3D.h"
        
class BNO055 {
    private:
      
      Adafruit_BNO055* instance;
      
      TwoWire* wire;
      uint8_t address;
      int id;
      bool status = false;
      
      sensors_event_t angVelocity, linearAccel, accelerometer, magnetometer, gravity;
      
    public:
    
      BNO055(TwoWire* wire, uint8_t address, int id);
      bool initialized();
      
      float getTemperature();
      Vector3D getOrientation();
};
