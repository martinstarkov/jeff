#include "ParachuteController.h"

void ParachuteController::init() {
  Serial.println("Parachute controller fully initalized");
  for (int i = 0; i < altitudeLoop; i++) {
    previousStates[i] = 0;
  }
  for (int i = 0; i < caching; i++) {
    altitudeCache[i] = 0;
  }
}

bool ParachuteController::mainChuteDeploymentCheck(float currentAltitude) {
  belowThresholdAltitudes = 0;
  if (currentAltitude < mainDeployAltitude) {
    altitudeCache[mainCycle % caching] = 1;
  } else {
    altitudeCache[mainCycle % caching] = 0;
  }
  for (int i = 0; i < caching; i++) {
    if (altitudeCache[i % caching] == 1) {
      belowThresholdAltitudes++;
    }
  }
  if (belowThresholdAltitudes >= caching) {
    mainChuteDeploymentStatus = true;
  }
  printMainChuteStatus();
  mainCycle++;
  return mainChuteDeploymentStatus;
}

void ParachuteController::printMainChuteStatus() {
  Serial.println("Altitude Threshold Confidence: " + String(100 * belowThresholdAltitudes / caching) + "%");
  for (int i = 0; i < caching; i++) {
    if (i == mainCycle % caching) {
      Serial.print("#");
    } else {
      Serial.print("_");
    }
  }
  Serial.println();
  for (int i = 0; i < caching; i++) {
    Serial.print(String(altitudeCache[i]));
  }
  Serial.println();
}

void ParachuteController::printDrogueStatus() {
  Serial.println("Altitude Decrease Confidence: " + String(100 * decreasedAltitudes / altitudeConfidence) + "%");
  for (int i = 0; i < altitudeLoop; i++) {
    if (i == drogueCycle % altitudeLoop) {
      Serial.print("#");
    } else {
      Serial.print("_");
    }
  }
  Serial.println();
  for (int i = 0; i < altitudeLoop; i++) {
    Serial.print(String(previousStates[i]));
  }
  Serial.println();
}

bool ParachuteController::drogueDeploymentCheck(float currentAltitude) {
  if (previousStates[drogueCycle % altitudeLoop] == 1) {
    decreasedAltitudes--;
  }
  previousStates[drogueCycle % altitudeLoop] = 0; // update tile state each loop iteration
  if (decreasedAltitudes > altitudeConfidence) {
    //Serial.println("Parachute Deployed!");
    for (int i = 0; i < 10; i++) {
      Serial.println("1000");
    }
    drogueDeploymentStatus = true;
    decreasedAltitudes = 0;
    //while (1); // Stop printing
  }
  if (previousAltitude - currentAltitude > altitudeSafetyFactor) { // altitude decreased
    previousStates[drogueCycle % altitudeLoop] = 1; // update tile state
    decreasedAltitudes++;
  }
  printDrogueStatus();
  previousAltitude = currentAltitude;
  drogueCycle++;
  return drogueDeploymentStatus;
}
