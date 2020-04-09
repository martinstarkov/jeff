#pragma once
#include "Bluetooth.h"
#include "ParachuteController.h"
#include "AirbrakeController.h"
#include "SensorController.h"

#define SCB_AIRCR (*(volatile uint32_t *)0xE000ED0C) // Application Interrupt and Reset Control location

class FlightController {
    private:
      SensorController* sc;
      ParachuteController* pc;
      AirbrakeController* ac;
    public:
      FlightController();
      void init();
      void restart();
      void cycle();
};
