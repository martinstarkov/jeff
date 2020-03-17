#pragma once
#include "Defines.h"
#include "Bluetooth.h"
#include "Data.h"
        
class ParachuteController {
    private:
      // initalize
      float previousAltitude;
      // drogue chute variables
      int decreasedAltitudes = 0;
      int drogueCycle = 0;
      int altitudeDifferences[DROGUE_LOOP_LENGTH]; // must be same as altitudeLoop
      bool drogueDeploymentStatus = false;
      // main chute variables
      int mainCycle = 0;
      int belowThresholdAltitudes = 0;
      int altitudeCache[MAIN_LOOP_LENGTH];
      bool mainChuteDeploymentStatus = false;
    public:
      ParachuteController();
      void check(ProcessedData data);
      bool drogueDeploymentCheck(float currentAltitude);
      bool mainChuteDeploymentCheck(float currentAltitude);
      void printMainChuteStatus();
      void printDrogueStatus();
};
