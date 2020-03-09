#include "DataService.h"

DataService* DataService::instance = nullptr;
float DataService::currentPressure = 0;
float DataService::currentTemperature = 0;
float DataService::currentAltitude = 0;
Vector3D DataService::currentOrientation = Vector3D(0, 0, 0);

void DataService::init() { // make sure DataService is only able to initialize once
  if (instance == 0) {
    
    instance = new DataService();
    // other init functions (setting default values for temp, pressure, etc)
  }
}

String DataService::processData() {
  
  String data = "";
  // Gregor said: Pressure1;Pressure2;Pressure3;Temp1;Temp2;Temp3;Altitude1;Altitude2;Altitude3;X-Magnetic;Y-Magnetic;Z-Magnetic;X-Orient;Y-Orient;Z-Orient;X-LinAccel;Y-LinAccel;Z-LinAccel;X-Angul;Y-Angul;Z-Angul;X-GravLin;Y-GravLin;Z-GravLin;BNOTemp;Latitude;Longitude;GPSAltitude;StatusBools;
  // Currently: avg-pressure;avg-bmp-temp;avg-altitude;(x-orient,y-orient,z-orient);
  data += String(getPressure()) + ";";
  data += String(getTemperature()) + ";";
  data += String(getAltitude()) + ";";
  data += getOrientation().toString() + ";";
  
  return data;
}

void DataService::printData() {
  Bluetooth::print("Pressure: " + String(getPressure()));
  Bluetooth::print("Temperature: " + String(getTemperature()));
  Bluetooth::print("Altitude: " + String(getAltitude()));
  Bluetooth::print("Orientation: " + getOrientation().toString()); // Vector3D objects require toString() method
}

float DataService::getAltitude() {
  return currentAltitude;
}

void DataService::setAltitude(float altitude) {
  currentAltitude = altitude;
}

float DataService::getTemperature() {
  return currentTemperature;
}

void DataService::setTemperature(float temperature) {
  currentTemperature = temperature;
}


float DataService::getPressure() {
  return currentPressure;
}

void DataService::setPressure(float pressure) {
  currentPressure = pressure;
}

Vector3D DataService::getOrientation() {
  return currentOrientation;
}

void DataService::setOrientation(Vector3D orientation) {
  currentOrientation = orientation;
}
