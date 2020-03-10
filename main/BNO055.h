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
      
    public:
    
      BNO055(TwoWire* wire, uint8_t address, int id);
      bool initialized();
      
      float getTemperature();
      Vector3D getOrientation();
      Vector3D getAngularVelocity();
      Vector3D getLinearAcceleration();
      Vector3D getNetAcceleration();
      Vector3D getGravity();
      Vector3D getMagneticField();
};
