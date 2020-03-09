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
  
  delay(500);
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
  
  delay(sController->refresh_delay);
}
