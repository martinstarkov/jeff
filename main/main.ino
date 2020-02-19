#include "SensorController.h"
#include "ParachuteController.h"

SensorController* sController;
ParachuteController* pController;

void setup()
{
  sController = new SensorController();
  sController->init();
  pController = new ParachuteController();
  pController->init();
  //delay(1000);
}

void loop()
{
  sController->recordData();
  sController->bluetoothListener();
  //Serial.println("Average Pressure: " + String(sController->getPressure()));
  //float currentAltitude = sController->getAltitude();
  //Serial.println("Average Altitude: " + String(currentAltitude));
  //pController->drogueDeploymentCheck(currentAltitude);
  //pController->mainChuteDeploymentCheck(currentAltitude);
  //delay(REFRESH_DELAY);
}
