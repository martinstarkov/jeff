#include "DataService.h"

DataService* DataService::instance;
float DataService::pressure;
float DataService::BMPTemperature;
float DataService::altitude;
float DataService::BNOTemperature;
Vector3D DataService::orientation;
Vector3D DataService::angularVelocity;
Vector3D DataService::linearAcceleration;
Vector3D DataService::netAcceleration;
Vector3D DataService::gravity;
Vector3D DataService::magneticField;
String DataService::rawData;
    
void DataService::init() { // make sure DataService is only able to initialize once
  if (instance == 0) {
    instance = new DataService();
  }
}

String DataService::getRawData() {
  return rawData;
}

template <typename Type> void DataService::addRawData(Type newData) {
  rawData += String(newData);
}

void DataService::resetRawData() {
  rawData = "";
}

String DataService::processData() {
  String data;
  // Format (averages): pressure;bmp-temp;altitude;bno-temp;(x-orient,y-orient,z-orient);(x-angVel,y-angVel,z-angVel);(x-linAccel,y-linAccel,z-linAccel);(x-netAccel,y-netAccel,z-netAccel);(x-grav,y-grav,z-grav);(x-magn,y-magn,z-magn);
  data += String(pressure) + ";";
  data += String(BMPTemperature) + ";";
  data += String(altitude) + ";";
  data += String(BNOTemperature) + ";";
  data += String(orientation) + ";";
  data += String(angularVelocity) + ";";
  data += String(linearAcceleration) + ";";
  data += String(netAcceleration) + ";";
  data += String(gravity) + ";";
  data += String(magneticField) + ";";
  
  return data;
}
