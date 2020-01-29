#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include "SensorController.h"
#include "ParachuteController.h"

SensorController* sController;
ParachuteController* pController;

void setup(void)
{
  sController = new SensorController();
  sController->init();
  pController = new ParachuteController();
  pController->init();
  
  delay(1000);
}

void loop(void)
{
  sController->recordData();
  sController->printData(sController->getData("orientation"));
  sController->printData(sController->getData("l_acceleration"));
  sController->printData(sController->getData("a_acceleration"));
  sController->printData(sController->getData("gyroscope"));
  sController->printData(sController->getData("magnetic"));
  sController->printData(sController->getData("temperature"));
  
  delay(sController->refresh_delay);
}
