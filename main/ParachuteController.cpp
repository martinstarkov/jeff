#include "ParachuteController.h"

void ParachuteController::init() {
  Serial.println("Parachute controller fully initalized");
  for (int i = 0; i < 50; i++) {
    previousStates[i] = 0;
  }
}

bool ParachuteController::deploymentCheck(float currentAltitude) {
  bool deploymentStatus = false;
  static int cycle = 0;
  int count = 0;
  int firstOccurence = 0;
  for (int i = 0; i < 50; i++) {
    if (count == 0) firstOccurence = i;
    if (previousStates[i] == 1) count++;
  }
  previousStates[cycle % 50] = 0;
  if (count > altitudeConfidence) {
    previousStates[firstOccurence] = 0;
    Serial.println("altitudeConfidence reached! Parachute Deployed!");
    while (1);
  }
  if (previousAltitude - currentAltitude > altitudeSafetyFactor) {
    previousStates[cycle % 50] = 1;
    Serial.println("Altitude decreased! (" + String(cycle % 50) + ") set to 1");
  }
  Serial.println("Cycle: " + String(cycle % 50));
  Serial.println("Decreased Altitudes: " + String(count));
  for (int i = 0; i < 50; i++) {
    if (i == cycle % 50) {
      Serial.print("#");
    } else {
      Serial.print("_");
    }
  }
  Serial.println();
  for (int i = 0; i < 50; i++) {
    Serial.print(String(previousStates[i]));
  }
  Serial.println();
  previousAltitude = currentAltitude;
  cycle++;
  return deploymentStatus;
}
