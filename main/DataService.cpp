#include "DataService.h"

DataService* DataService::instance = nullptr;
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

void DataService::init() { // make sure DataService is only able to initialize once
  if (instance == 0) {
    instance = new DataService();
    // other init functions (setting default values for temp, pressure, etc)
  }
}

String DataService::processData() {
  
  String data = "";
  // Gregor said: Pressure1;Pressure2;Pressure3;Temp1;Temp2;Temp3;Altitude1;Altitude2;Altitude3;X-Magnetic;Y-Magnetic;Z-Magnetic;X-Orient;Y-Orient;Z-Orient;X-LinAccel;Y-LinAccel;Z-LinAccel;X-Angul;Y-Angul;Z-Angul;X-GravLin;Y-GravLin;Z-GravLin;BNOTemp;Latitude;Longitude;GPSAltitude;StatusBools;
  // Currently: averages: pressure;bmp-temp;altitude;bno-temp;(x-orient,y-orient,z-orient);(x-angVel,y-angVel,z-angVel);(x-,y-,z-);(x-linAccel,y-linAccel,z-linAccel);(x-netAccel,y-netAccel,z-netAccel);(x-grav,y-grav,z-grav);(x-magn,y-magn,z-magn);
  data += String(pressure) + ";";
  data += String(BMPTemperature) + ";";
  data += String(altitude) + ";";
  data += String(BNOTemperature) + ";";
  data += orientation.toString() + ";";
  data += angularVelocity.toString() + ";";
  data += linearAcceleration.toString() + ";";
  data += netAcceleration.toString() + ";";
  data += gravity.toString() + ";";
  data += magneticField.toString() + ";";
  
  return data;
}

void DataService::printData() {
  Bluetooth::print("Pressure: " + String(pressure));
  Bluetooth::print("BMPTemperature: " + String(BMPTemperature));
  Bluetooth::print("BNOTemperature: " + String(BNOTemperature));
  Bluetooth::print("Altitude: " + String(altitude));
  // Vector3D objects require toString() method
  Bluetooth::print("Orientation: " + orientation.toString());
  Bluetooth::print("Angular Velocity: " + angularVelocity.toString());
  Bluetooth::print("Linear Acceleration: " + linearAcceleration.toString());
  Bluetooth::print("Net Acceleration: " + netAcceleration.toString());
  Bluetooth::print("Gravity: " + gravity.toString());
  Bluetooth::print("Magnetic Field: " + magneticField.toString());
}
