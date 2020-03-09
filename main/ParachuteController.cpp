#include "ParachuteController.h"

void ParachuteController::init() {
  
  for (int i = 0; i < altitudeLoop; i++) {
    previousStates[i] = 0;
  }
  
  for (int i = 0; i < caching; i++) {
    altitudeCache[i] = 0;
  }
  
  Bluetooth::print(SUCCESS + "Parachute Controller initalized");
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
  
  //Bluetooth::print("Altitude Threshold Confidence: " + String(100 * belowThresholdAltitudes / caching) + "%");
  //printMainChuteStatus();
  mainCycle++;
  return mainChuteDeploymentStatus;
}

void ParachuteController::printMainChuteStatus() {
  
  for (int i = 0; i < caching; i++) {
    if (i == mainCycle % caching) {
      Bluetooth::print("#", false);
    } else {
      Bluetooth::print("_", false);
    }
  }
  
  Bluetooth::print("");
  
  for (int i = 0; i < caching; i++) {
    Bluetooth::print(String(altitudeCache[i]), false);
  }
  
  Bluetooth::print("");
}

void ParachuteController::printDrogueStatus() {
  
  for (int i = 0; i < altitudeLoop; i++) {
    if (i == drogueCycle % altitudeLoop) {
      Bluetooth::print("#", false);
    } else {
      Bluetooth::print("_", false);
    }
  }
  
  Bluetooth::print("");
  
  for (int i = 0; i < altitudeLoop; i++) {
    Bluetooth::print(String(previousStates[i]), false);
  }
  
  Bluetooth::print("");
}

bool ParachuteController::drogueDeploymentCheck(float currentAltitude) {
  
  if (previousStates[drogueCycle % altitudeLoop] == 1) {
    decreasedAltitudes--;
  }
  
  previousStates[drogueCycle % altitudeLoop] = 0; // update tile state each loop iteration
  
  if (decreasedAltitudes > altitudeConfidence) {
    Bluetooth::print("Parachute Deployed!");
    drogueDeploymentStatus = true;
    decreasedAltitudes = 0;
    while (1); // Stop printing
  }
  
  if (previousAltitude - currentAltitude > altitudeSafetyFactor) { // altitude decreased
    previousStates[drogueCycle % altitudeLoop] = 1; // update tile state
    decreasedAltitudes++;
  }
  //Bluetooth::print("Altitude Decrease Confidence: " + String(100 * decreasedAltitudes / altitudeConfidence) + "%");
  //printDrogueStatus();
  previousAltitude = currentAltitude;
  drogueCycle++;
  return drogueDeploymentStatus;
}
