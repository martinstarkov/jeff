#include <SoftwareSerial.h>
#include "SensorController.h"
#include "ParachuteController.h"

SensorController* sController;
ParachuteController* pController;
float initialPressure = -9999999999;

SoftwareSerial bluetoothSerial(0,1);

void setup()
{
  Serial1.begin(9600);
  bluetoothSerial.begin(9600);
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
  //Serial.println("Pressure: " + String(sController->getPressure()));
//  float currentAltitude = sController->getAltitude(995);
//  Serial.println(String(currentAltitude));
//  pController->drogueDeploymentCheck(currentAltitude);
//  pController->mainChuteDeploymentCheck(currentAltitude);

    bluetoothSerial.println("whatever");
    bluetoothSerial.write("whatever");
    Serial1.println("test");
  
  delay(100);
}
