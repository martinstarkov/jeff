#pragma once
#include "Bluetooth.h"
#include "SensorController.h"
#include "ParachuteController.h"
#include "AirbrakeController.h"
#include "DataProcessor.h"

#define SCB_AIRCR (*(volatile uint32_t *)0xE000ED0C) // Application interruption and reset control location

class FlightController {
    private:
      SensorController* sc;
      ParachuteController* pc;
      AirbrakeController* ac;
      DataProcessor* dp;
    public:
      FlightController();
      void init();
      void restart();
      void cycle();
};
