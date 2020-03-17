#include "ParachuteController.h"

ParachuteController::ParachuteController() {
  for (int i = 0; i < DROGUE_LOOP_LENGTH; i++) {
    altitudeDifferences[i] = 0;
  }
  for (int i = 0; i < MAIN_LOOP_LENGTH; i++) {
    altitudeCache[i] = 0;
  }
  Bluetooth::print(SUCCESS + "Parachute Controller initalized");
}

void ParachuteController::check(ProcessedData data) {
  float currentAltitude = data.altitude;
  drogueDeploymentCheck(currentAltitude);
  mainChuteDeploymentCheck(currentAltitude);
}

bool ParachuteController::mainChuteDeploymentCheck(float currentAltitude) {
  belowThresholdAltitudes = 0;
  if (abs(currentAltitude - MAIN_SAFETY_FACTOR) < MAIN_DEPLOY_ALTITUDE) {
    altitudeCache[mainCycle % MAIN_LOOP_LENGTH] = 1;
  } else {
    altitudeCache[mainCycle % MAIN_LOOP_LENGTH] = 0;
  }
  for (int i = 0; i < MAIN_LOOP_LENGTH; i++) {
    if (altitudeCache[i % MAIN_LOOP_LENGTH] == 1) {
      belowThresholdAltitudes++;
    }
  }
  if (belowThresholdAltitudes >= MAIN_LOOP_LENGTH) {
    mainChuteDeploymentStatus = true;
  }
  //Bluetooth::print("Altitude Threshold Confidence: " + String(100 * belowThresholdAltitudes / MAIN_LOOP_LENGTH) + "%");
  //printMainChuteStatus();
  mainCycle++;
  return mainChuteDeploymentStatus;
}

void ParachuteController::printMainChuteStatus() {
  for (int i = 0; i < MAIN_LOOP_LENGTH; i++) {
    if (i == mainCycle % MAIN_LOOP_LENGTH) {
      Bluetooth::print("#", false);
    } else {
      Bluetooth::print("_", false);
    }
  }
  Bluetooth::print("");
  for (int i = 0; i < MAIN_LOOP_LENGTH; i++) {
    Bluetooth::print(String(altitudeCache[i]), false);
  }
  Bluetooth::print("");
}

void ParachuteController::printDrogueStatus() {
  for (int i = 0; i < DROGUE_LOOP_LENGTH; i++) {
    if (i == drogueCycle % DROGUE_LOOP_LENGTH) {
      Bluetooth::print("#", false);
    } else {
      Bluetooth::print("_", false);
    }
  }
  Bluetooth::print("");
  for (int i = 0; i < DROGUE_LOOP_LENGTH; i++) {
    Bluetooth::print(String(altitudeDifferences[i]), false);
  }
  Bluetooth::print("");
}

bool ParachuteController::drogueDeploymentCheck(float currentAltitude) {
  if (altitudeDifferences[drogueCycle % DROGUE_LOOP_LENGTH] == 1) {
    decreasedAltitudes--;
  }
  altitudeDifferences[drogueCycle % DROGUE_LOOP_LENGTH] = 0; // reset tile state each loop iteration
  if (decreasedAltitudes > DROGUE_CONFIDENCE) {
    Bluetooth::print("Parachute Deployed!");
    drogueDeploymentStatus = true;
    decreasedAltitudes = 0;
    while (1); // Stop printing
  }
  if (previousAltitude - currentAltitude > DROGUE_SAFETY_FACTOR) { // altitude decreased
    altitudeDifferences[drogueCycle % DROGUE_LOOP_LENGTH] = 1; // update tile state
    decreasedAltitudes++;
  }
  //Bluetooth::print("Altitude Decrease Confidence: " + String(100 * decreasedAltitudes / DROGUE_CONFIDENCE) + "%");
  //printDrogueStatus();
  previousAltitude = currentAltitude;
  drogueCycle++;
  return drogueDeploymentStatus;
}
