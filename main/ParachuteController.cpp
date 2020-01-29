#include "ParachuteController.h"

void ParachuteController::init() {
  float storage_array[10];
  altitudes.setStorage(storage_array);
  altitudes.clear();
  Serial.println("Parachute controller fully initalized");
}

bool ParachuteController::deploymentCheck(float currentAltitude) {
  // length of array
  int sampled = altitudes.size();
  if (sampled == samples) {
    Serial.println("Reached 10!");
    // check how many altitudes decreased
    int decreased = 0;
    for ( int i = 1; i < samples; i++ ) {
      Serial.println("Altitude: " + String(altitudes[i]) + ", previous one: " + String(altitudes[i-1]));
      if (altitudes[i] - altitudes[i-1] < 0) {
        // altitude decreased
        decreased++;
      }
    }
    Serial.println(String(decreased) + "/" + String(samples) + " of samples showed a decrease in altitude");
    altitudes.clear();
    // if over half of the samples show a decrease in altitude then deploy parachutes
    if (decreased > samples / 2) {
      return true;
    }
  } else {
    for ( int i = 0; i < altitudes.size(); i++ ) {
      Serial.print(String(altitudes[i]) + ",");
    }
    altitudes.push_back(currentAltitude);
    Serial.println("added: " + String(currentAltitude) + ", altitudes size: " + String(altitudes.size()) + "/" + String(altitudes.max_size()));
  }
  return false;
}
