#pragma once
#include <Wire.h>
        
class ParachuteController {
    private:
      int altitudeConfidence = 10;
      int altitudeLoop = 50;
      float previousAltitude = -99999999999999;
      float altitudeSafetyFactor = 0.25;
    public:
      void init();
      bool deploymentCheck(float currentAltitude);
};
