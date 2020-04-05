#pragma once
#include "Defines.h"
#include "Vector3D.h"

struct ProcessedData {
  // BMP
  float BMPTemperature;
  float pressure;
  float altitude;
  // BNO
  float BNOTemperature;
  Vector3D orientation;
  Vector3D angularVelocity;
  Vector3D linearAcceleration;
  Vector3D netAcceleration;
  Vector3D gravity;
  Vector3D magneticField;
};

struct RawData {
  // BMP
  float BMPTemperature1, BMPTemperature2, BMPTemperature3;
  float pressure1, pressure2, pressure3;
  float altitude1, altitude2, altitude3;
  // BNO
  float BNOTemperature;
  Vector3D orientation;
  Vector3D angularVelocity;
  Vector3D linearAcceleration;
  Vector3D netAcceleration;
  Vector3D gravity;
  Vector3D magneticField;
};
