#pragma once
#include "Bluetooth.h"
#include "ParachuteController.h"
#include "AirbrakeController.h"
#include "DataService.h"

class FlightController {
    private:
      ParachuteController* parachuteController;
      AirbrakeController* airbrakeController;
      DataService* dataService;
    public:
      FlightController();
      void cycle();
};
