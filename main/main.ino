#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include "SensorController.h"
#include <Adafruit_BMP280.h>

SensorController* controller;

void setup(void)
{
  controller = new SensorController();
  controller->init();
  
  delay(1000);
}

void loop(void)
{
  controller->recordData();
  controller->correctData();
  controller->printData(controller->getData("orientation"));
  controller->printData(controller->getData("l_acceleration"));
  controller->printData(controller->getData("a_acceleration"));
  controller->printData(controller->getData("gyroscope"));
  controller->printData(controller->getData("magnetic"));
  controller->printData(controller->getData("temperature"));
  controller->printBMPData();
  delay(controller->refresh_delay);
}
