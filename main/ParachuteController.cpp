#include "ParachuteController.h"

ParachuteController::ParachuteController() {
  for (int i = 0; i < DROGUE_LOOP_LENGTH; i++) {
    altitudeDifferences[i] = 0;
  }
  for (int i = 0; i < MAIN_LOOP_LENGTH; i++) {
    altitudeCache[i] = 0;
  }
}

void ParachuteController::update() {
  cycle = Data::getCycle();
  altitude = Data::get(ALTITUDE).toFloat();
}

bool ParachuteController::mainDescentCheck() {
  belowThresholdAltitudes = 0;
  if (abs(altitude - MAIN_SAFETY_FACTOR) < MAIN_DEPLOY_ALTITUDE) {
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
    return true;
  }
  return false;
}

bool ParachuteController::drogueDescentCheck() {
  if (altitudeDifferences[cycle % DROGUE_LOOP_LENGTH] == 1) {
    decreasedAltitudes--;
  }
  altitudeDifferences[cycle % DROGUE_LOOP_LENGTH] = 0; // reset tile state each loop iteration
  if (decreasedAltitudes > DROGUE_CONFIDENCE) {
    return true;
  }
  if (previousAltitude - altitude > DROGUE_SAFETY_FACTOR) { // altitude decreased
    altitudeDifferences[cycle % DROGUE_LOOP_LENGTH] = 1; // update tile state
    decreasedAltitudes++;
  }
  previousAltitude = altitude;
  return false;
}

void ParachuteController::printChuteCheck(int* array, int length) {
  // _______#____________ display state of cycle in the given caching array
  for (int i = 0; i < length; i++) {
    if (i == cycle % length) {
      //Serial.print("#", false);
    } else {
      //Serial.print("_", false);
    }
  }
  //Serial.print(""); // newline
  // 0000100000010000001 display altitude behavior that is desired for specific deployment as 1s
  for (int i = 0; i < length; i++) {
    //Serial.print(String(array[i]), false);
  }
  //Serial.print(""); // newline
}
