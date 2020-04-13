#pragma once
#include "DataService.h"
#include "StateMachine.h"

#define SCB_AIRCR (*(volatile uint32_t *)0xE000ED0C) // Teensy interruption and reset control location

class FlightController {
    private:
      static FlightController* instance;
      FlightController();
      DataService* ds;
      StateMachine* sm;
    public:
      static FlightController* getInstance();
      void cycle();
      void restart();
};
