#pragma once
#include <Wire.h>

#define ALTITUDE_LOOP_LENGTH 50
        
class ParachuteController {
    private:
      // initalize
      float previousAltitude;

      // drogue chute variables
      int decreasedAltitudes = 0;
      int drogueCycle = 0;
      bool drogueDeploymentStatus = false;
      int altitudeConfidence = 10;
      int altitudeLoop = ALTITUDE_LOOP_LENGTH;
      int previousStates[ALTITUDE_LOOP_LENGTH]; // must be same as altitudeLoop
      float altitudeSafetyFactor = 0.2; // meters

      // main chute variables
      int caching = 10;
      int mainCycle = 0;
      int belowThresholdAltitudes = 0;
      int altitudeCache[10];
      bool mainChuteDeploymentStatus = false;
      float mainDeployAltitude = 179; // 457.2 according to competition rules
    public:
      void init();
      bool drogueDeploymentCheck(float currentAltitude);
      bool mainChuteDeploymentCheck(float currentAltitude);
      void printMainChuteStatus();
      void printDrogueStatus();
};
