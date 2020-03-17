#pragma once
#include <Wire.h>
#include "Vector3D.h"
#include "SensorController.h"
#include "Data.h"
#include "Bluetooth.h"

class DataService {
    private:
      SensorController* sensorController;
      RawData rawData;
      ProcessedData data;
    public:
      DataService() {
        sensorController = new SensorController();
      }
      void update();
      RawData getRawData();
      ProcessedData getProcessedData();
      void printRawData();
      void printProcessedData();
};
