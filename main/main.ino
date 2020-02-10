#include "SensorController.h"
#include "ParachuteController.h"

SensorController* sController;
ParachuteController* pController;
float testAltitude = 800;
float randNumber;

void setup(void)
{
  sController = new SensorController();
  sController->init();
  pController = new ParachuteController();
  pController->init();
  randomSeed(analogRead(0));
  delay(1000);
}

void loop(void)
{
  randNumber = random(-4, 5);
  testAltitude = testAltitude - 20;
  //sController->recordData();
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
  Serial.println(sController->getAltitude());
  //pController->deploymentCheck(sController->getAltitude());
  pController->deploymentCheck(sController->getAltitude());
  
  delay(1000);
}
