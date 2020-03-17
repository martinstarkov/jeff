#pragma once
#include "Bluetooth.h"
#include "ParachuteController.h"
#include "DataService.h"

class FlightController {
    private:
      ParachuteController* parachuteController;
      DataService* dataService;
    public:
      FlightController();
      void cycle();
};
