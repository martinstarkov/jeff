#include "SensorController.h"

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
  controller->printData(controller->getData("orientation"));
  controller->printData(controller->getData("l_acceleration"));
  controller->printData(controller->getData("a_acceleration"));
  controller->printData(controller->getData("gyroscope"));
  controller->printData(controller->getData("magnetic"));
  controller->printData(controller->getData("bnoTemperature"));
  controller->printData(controller->getData("bmpTemperature"));
  controller->printData(controller->getData("pressure"));
  controller->printData(controller->getData("altitude"));
  
  delay(controller->refresh_delay);
}
