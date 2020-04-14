#pragma once
#include "SensorController.h"
#include "Defines.h"

class DataService {
  private:
    SensorController* sc;
  public:
    DataService();
    void update();
};
