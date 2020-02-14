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
  Serial.println("Pressure: " + String(sController->getPressure()));
  Serial.println("Altitude: " + String(sController->getAltitude(980)));
  pController->deploymentCheck(sController->getAltitude(980));
  
  delay(1000);
}
