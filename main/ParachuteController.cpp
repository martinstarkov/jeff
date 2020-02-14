#include "ParachuteController.h"

void ParachuteController::init() {
  Serial.println("Parachute controller fully initalized");
}

bool ParachuteController::deploymentCheck(float currentAltitude) {
  bool deploymentStatus = false;
  static int decreasedAltitudes = 0;
  static int deadValues = 0;
  static int loopIteration = altitudeLoop;
  if (true) {//(loopIteration > 0) {
    if (previousAltitude - currentAltitude > altitudeSafetyFactor) {
      decreasedAltitudes++;
      if (deadValues < 50) {  
        if (decreasedAltitudes >= altitudeConfidence) {
          Serial.println("Parachute deployed");
          deploymentStatus = true;
          
        }
      } else {
        decreasedAltitudes = 0;
        deadValues = 0;
      }
      Serial.println("Altitude decreased!");
    } else {
      deadValues++;
    }
    //loopIteration--;
  } else {
    Serial.println("Reset confidence");
    decreasedAltitudes = 0;
    loopIteration = altitudeLoop;
  }
  previousAltitude = currentAltitude;
  return deploymentStatus;
  
}
