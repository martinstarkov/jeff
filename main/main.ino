#include "SensorController.h"
#include "ParachuteController.h"

SensorController* sController;
ParachuteController* pController;
float initialPressure = -9999999999;

void setup()
{
  sController = new SensorController();
  sController->init();
  pController = new ParachuteController();
  pController->init();
  initialPressure = sController->getPressure();
  delay(1000);
}

void loop()
{
  sController->recordData();
  Serial.println("Pressure: " + String(sController->getPressure()));
  Serial.println(String(sController->getAltitude(985)));
  pController->drogueDeploymentCheck(sController->getAltitude(985));
  pController->mainChuteDeploymentCheck(sController->getAltitude(985));
  
  delay(100);
}
