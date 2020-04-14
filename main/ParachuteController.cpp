#include "ParachuteController.h"

ParachuteController::ParachuteController() {
  for (int i = 0; i < DROGUE_LOOP_LENGTH; i++) {
    altitudeDifferences[i] = 0;
  }
  for (int i = 0; i < MAIN_LOOP_LENGTH; i++) {
    altitudeCache[i] = 0;
  }
  debug(SUCCESS + "Parachute controller initalized");
}

void ParachuteController::check(float altitude) {
  float currentAltitude = altitude;
  drogueDeploymentCheck(currentAltitude);
  mainChuteDeploymentCheck(currentAltitude);
  cycle++;
}

bool ParachuteController::mainChuteDeploymentCheck(float currentAltitude) {
  belowThresholdAltitudes = 0;
  if (abs(currentAltitude - MAIN_SAFETY_FACTOR) < MAIN_DEPLOY_ALTITUDE) {
    altitudeCache[cycle % MAIN_LOOP_LENGTH] = 1;
  } else {
    altitudeCache[cycle % MAIN_LOOP_LENGTH] = 0;
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
  //printChuteCheck(altitudeCache, MAIN_LOOP_LENGTH);
  return mainChuteDeploymentStatus;
}

void ParachuteController::printChuteCheck(int* array, int length) {
  // _______#____________ display state of cycle in the given caching array
  for (int i = 0; i < length; i++) {
    if (i == cycle % length) {
      //Bluetooth::print("#", false);
    } else {
      //Bluetooth::print("_", false);
    }
  }
  //Bluetooth::print(""); // newline
  // 0000100000010000001 display altitude behavior that is desired for specific deployment as 1s
  for (int i = 0; i < length; i++) {
    //Bluetooth::print(String(array[i]), false);
  }
  //Bluetooth::print(""); // newline
}

bool ParachuteController::drogueDeploymentCheck(float currentAltitude) {
  if (altitudeDifferences[cycle % DROGUE_LOOP_LENGTH] == 1) {
    decreasedAltitudes--;
  }
  altitudeDifferences[cycle % DROGUE_LOOP_LENGTH] = 0; // reset tile state each loop iteration
  if (decreasedAltitudes > DROGUE_CONFIDENCE) {
    //Bluetooth::print("Parachute Deployed!");
    drogueDeploymentStatus = true;
    decreasedAltitudes = 0;
    while (1); // Stop printing
  }
  if (previousAltitude - currentAltitude > DROGUE_SAFETY_FACTOR) { // altitude decreased
    altitudeDifferences[cycle % DROGUE_LOOP_LENGTH] = 1; // update tile state
    decreasedAltitudes++;
  }
  //Bluetooth::print("Altitude Decrease Confidence: " + String(100 * decreasedAltitudes / DROGUE_CONFIDENCE) + "%");
  //printChuteCheck(altitudeDifferences, DROGUE_LOOP_LENGTH);
  previousAltitude = currentAltitude;
  return drogueDeploymentStatus;
}
