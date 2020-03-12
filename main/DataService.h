#pragma once
#include <Wire.h>
#include "Vector3D.h"

class DataService {
    private:
      static DataService* instance;
      // General
      static String rawData;
    public:
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

      static void init();
      static String getRawData();
      template <typename Type> static void addRawData(Type newData);
      static void resetRawData();
      static String processData();
};
