#include "ParachuteController.h"

void ParachuteController::init() {
  Serial.println("Parachute controller fully initalized");
}

bool ParachuteController::deploymentCheck(float currentAltitude) {
  if (previousAltitude - currentAltitude > altitudeSafetyFactor) {
    decreasedAltitudesThreshold--;
    Serial.println("Decreased altitude!");
  }
  previousAltitude = currentAltitude;
  if (decreasedAltitudesThreshold <= 0) {
    Serial.println("Parachute deployed");
    return true;
  }
  return false;
}
