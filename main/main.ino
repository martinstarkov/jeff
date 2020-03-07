#include "SensorController.h"
#include "ParachuteController.h"
#include "Bluetooth.h"
#include "DataService.h"

SensorController* sController;
ParachuteController* pController;

#define BLUETOOTH_RX 0 // (TX on bluetooth module)
#define BLUETOOTH_TX 1 // (RX on bluetooth module)
#define BLUETOOTH_BAUD_RATE 9600 // data mode: 9600, command mode: 38400

void setup()
{
  Bluetooth::init(BLUETOOTH_RX, BLUETOOTH_TX, BLUETOOTH_BAUD_RATE);
  DataService::init();
  sController = new SensorController();
  sController->init();
  pController = new ParachuteController(sController);
  pController->init();
}

void loop()
{
  sController->recordData();
  sController->update();
  if (Bluetooth::available()) {
    Bluetooth::print(Bluetooth::read());
  }
  //Bluetooth::print("test123");
  
}
