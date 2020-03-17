#include "DataService.h"

void DataService::update() {
  rawData = sensorController->getRawData();
  data = sensorController->getProcessedData();
}

RawData DataService::getRawData() {
  return rawData;
}

ProcessedData DataService::getProcessedData() {
  return data;
}

void DataService::printRawData() {
  String line;
  line += String(rawData.BMPTemperature1) + ";" + String(rawData.BMPTemperature2) + ";" + String(rawData.BMPTemperature3) + ";";
  line += String(rawData.pressure1) + ";" + String(rawData.pressure2) + ";" + String(rawData.pressure3) + ";";
  line += String(rawData.altitude1) + ";" + String(rawData.altitude2) + ";" + String(rawData.altitude3) + ";";
  line += String(rawData.BNOTemperature) + ";";
  line += String(rawData.orientation) + ";";
  line += String(rawData.angularVelocity) + ";";
  line += String(rawData.linearAcceleration) + ";";
  line += String(rawData.netAcceleration) + ";";
  line += String(rawData.gravity) + ";";
  line += String(rawData.magneticField) + ";";
  Bluetooth::print(line);
}

void DataService::printProcessedData() {
  String line;
  line += String(data.BMPTemperature) + ";";
  line += String(data.pressure) + ";";
  line += String(data.altitude) + ";";
  line += String(data.BNOTemperature) + ";";
  line += String(data.orientation) + ";";
  line += String(data.angularVelocity) + ";";
  line += String(data.linearAcceleration) + ";";
  line += String(data.netAcceleration) + ";";
  line += String(data.gravity) + ";";
  line += String(data.magneticField) + ";";
  Bluetooth::print(line);
}
