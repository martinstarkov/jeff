#pragma once
#include "Bluetooth.h"
#include "Vector3D.h"
        
class DataService {
    private:
    
      static DataService* instance;

      // BMP
      static float currentPressure;
      static float currentTemperature;
      static float currentAltitude;

      // BNO
      static Vector3D currentOrientation;
      
    public:
    
      static void init();

      static String processData();
      static void printData();
      
      static float getAltitude();
      static void setAltitude(float altitude);
      
      static float getTemperature();
      static void setTemperature(float temperature);
      
      static float getPressure();
      static void setPressure(float pressure);
      
      static Vector3D getOrientation();
      static void setOrientation(Vector3D orientation);
      
};
