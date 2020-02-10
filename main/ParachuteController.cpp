#include "ParachuteController.h"

void ParachuteController::init() {
  Serial.println("Parachute controller fully initalized");
}

bool ParachuteController::deploymentCheck(float currentAltitude) {
  bool deploymentStatus = false;
  static int decreasedAltitudes = 0;
  static int loopIteration = altitudeLoop;
  if (loopIteration > 0) {
    if (previousAltitude - currentAltitude > altitudeSafetyFactor) {
      decreasedAltitudes++;
      Serial.println("Altitude decreased!");
    }
    if (decreasedAltitudes >= altitudeConfidence) {
      Serial.println("Parachute deployed");
      deploymentStatus = true;
    }
    loopIteration--;
  } else {
    Serial.println("Reset confidence");
    decreasedAltitudes = 0;
    loopIteration = altitudeLoop;
  }
  previousAltitude = currentAltitude;
  return deploymentStatus;
  
}
