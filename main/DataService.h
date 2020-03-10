#pragma once
#include "Bluetooth.h"
#include "Vector3D.h"
        
class DataService {
    private:
    
      static DataService* instance;
      
    public:
    
      static void init();

      // BMP
      static float BMPTemperature;
      static float pressure;
      static float altitude;

      // BNO
      static float BNOTemperature;
      static Vector3D orientation;
      static Vector3D angularVelocity;
      static Vector3D linearAcceleration;
      static Vector3D netAcceleration;
      static Vector3D gravity;
      static Vector3D magneticField;

      static String processData();
      static void printData();
      
      
};
