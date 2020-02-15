#pragma once
#include <Wire.h>
        
class ParachuteController {
    private:
      int altitudeConfidence = 10;
      int altitudeLoop = 50;
      int previousStates[50];
      float previousAltitude = -99999999999999;
      float altitudeSafetyFactor = 1; // meters
    public:
      void init();
      bool deploymentCheck(float currentAltitude);
};
