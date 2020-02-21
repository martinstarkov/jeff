#include "ParachuteController.h"

void ParachuteController::init() {
  sensorController->BTPrint("Parachute controller fully initalized");
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
  sensorController->BTPrint("Altitude Threshold Confidence: " + String(100 * belowThresholdAltitudes / caching) + "%");
  //printMainChuteStatus();
  mainCycle++;
  return mainChuteDeploymentStatus;
}

void ParachuteController::printMainChuteStatus() {
  for (int i = 0; i < caching; i++) {
    if (i == mainCycle % caching) {
      sensorController->BTPrint("#", false);
    } else {
      sensorController->BTPrint("_", false);
    }
  }
  sensorController->BTPrint("");
  for (int i = 0; i < caching; i++) {
    sensorController->BTPrint(String(altitudeCache[i]), false);
  }
  sensorController->BTPrint("");
}

void ParachuteController::printDrogueStatus() {
  for (int i = 0; i < altitudeLoop; i++) {
    if (i == drogueCycle % altitudeLoop) {
      sensorController->BTPrint("#", false);
    } else {
      sensorController->BTPrint("_", false);
    }
  }
  sensorController->BTPrint("");
  for (int i = 0; i < altitudeLoop; i++) {
    sensorController->BTPrint(String(previousStates[i]), false);
  }
  sensorController->BTPrint("");
}

bool ParachuteController::drogueDeploymentCheck(float currentAltitude) {
  if (previousStates[drogueCycle % altitudeLoop] == 1) {
    decreasedAltitudes--;
  }
  previousStates[drogueCycle % altitudeLoop] = 0; // update tile state each loop iteration
  if (decreasedAltitudes > altitudeConfidence) {
    sensorController->BTPrint("Parachute Deployed!");
    drogueDeploymentStatus = true;
    decreasedAltitudes = 0;
    while (1); // Stop printing
  }
  if (previousAltitude - currentAltitude > altitudeSafetyFactor) { // altitude decreased
    previousStates[drogueCycle % altitudeLoop] = 1; // update tile state
    decreasedAltitudes++;
  }
  sensorController->BTPrint("Altitude Decrease Confidence: " + String(100 * decreasedAltitudes / altitudeConfidence) + "%");
  //printDrogueStatus();
  previousAltitude = currentAltitude;
  drogueCycle++;
  return drogueDeploymentStatus;
}
