#pragma once
#include <Wire.h>
#include "Defines.h"
#include "Data.h"

class ParachuteInterface {
  public:
    virtual bool drogueDescentCheck() = 0;
    virtual bool mainDescentCheck() = 0;
};

class ParachuteController : public ParachuteInterface {
    private:
      // initalize
      float previousAltitude;
      int cycle = 0;
      // drogue chute variables
      int decreasedAltitudes = 0;
      int altitudeDifferences[DROGUE_LOOP_LENGTH];
      bool drogueDeploymentStatus = false;
      // main chute variables
      int belowThresholdAltitudes = 0;
      int altitudeCache[MAIN_LOOP_LENGTH];
      bool mainChuteDeploymentStatus = false;
    public:
      ParachuteController();
      bool drogueDescentCheck();
      bool mainDescentCheck();
      void printChuteCheck(int* array, int length); // array refers to altitudeDifferences / altitudeCache and length is that of those arrays
};
