#include "SensorController.h"
#include "ParachuteController.h"

SensorController* sController;
ParachuteController* pController;
float initialPressure = -9999999999;

void setup(void)
{
  sController = new SensorController();
  sController->init();
  pController = new ParachuteController();
  pController->init();
  initialPressure = sController->getPressure();
  delay(1000);
}

void loop(void)
{
  sController->recordData();
  /*
  sController->printData(sController->getData("orientation"));
  sController->printData(sController->getData("l_acceleration"));
  sController->printData(sController->getData("a_acceleration"));
  sController->printData(sController->getData("gyroscope"));
  sController->printData(sController->getData("magnetic"));
  sController->printData(sController->getData("bnoTemperature"));
  sController->printData(sController->getData("bmpTemperature"));
  sController->printData(sController->getData("pressure"));
  */
  Serial.println("Pressure: " + String(sController->getPressure()));
  Serial.println("Altitude: " + String(sController->getAltitude(980)));
  pController->deploymentCheck(sController->getAltitude(980));
  
  delay(1000);
}
