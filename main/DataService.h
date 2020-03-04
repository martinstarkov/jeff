#pragma once
#include "Bluetooth.h"
        
class DataService {
    private:
      static DataService* instance;
      static float currentPressure;
      static float currentTemperature;
      static float currentAltitude;
    public:
      static void init();

      static void printData();
      
      static float getAltitude();
      static void setAltitude(float altitude);
      static float getTemperature();
      static void setTemperature(float temperature);
      static float getPressure();
      static void setPressure(float pressure);
      
};
