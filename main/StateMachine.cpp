#include "StateMachine.h"

StateMachine::StateMachine() {
  cc = new CommunicationController();
  pc = new ParachuteController();
  ac = new AirbrakeController();
  // initial state set to standby
  currentStage = STANDBY;
  //Data::stage = STAGE_STANDBY;
  // fill array caches for staging checks
  for (int i = 0; i < LIFTOFF_LOOP_LENGTH; i++) {
    liftoffCache[i] = 0;
  }
  for (int i = 0; i < BURNOUT_LOOP_LENGTH; i++) {
    burnoutCache[i] = 0;
  }
}

void StateMachine::update() {
  //pc->update(cycle);
  //determineStage();
  //cycle++;
  // clear debug messages after 5 full cycles
  //if (Data::cycle == 5) {
    //Data::clearDebug();
  //}
  Data::add(TRANSMISSION_TIME, String(millis() / 1000.000f));
  // Send everything via serials at the end of the cycle
  cc->update();
}

void StateMachine::determineStage() {
  switch (currentStage) { // switch statement because stage transition can only occur incrementally
    case STANDBY:
      // check if criteria for powered ascent are met
      if (poweredAscentCheck()) {
        currentStage = POWERED_ASCENT;
        //Data::stage = STAGE_POWERED_ASCENT;
      }
      break;
    case POWERED_ASCENT:
      // check if criteria for coasting are met
      if (coastingCheck()) {
        currentStage = COASTING;
        //Data::stage = STAGE_COASTING;
      }
      break;
    case COASTING:
      // check if criteria for drogue chute deploy are met
      if (pc->drogueDescentCheck()) {
        currentStage = DROGUE_DESCENT;
        //Data::stage = STAGE_DROGUE_DESCENT;
      }
      break;
    case DROGUE_DESCENT:
      // check if criteria for main chute deploy are met
      if (pc->mainDescentCheck()) {
        currentStage = MAIN_DESCENT;
        //Data::stage = STAGE_MAIN_DESCENT;
      }
      break;
    case MAIN_DESCENT:
      // check if criteria for sufficient still time (i.e. landing) are met
      if (landingCheck()) {
        currentStage = LANDED;
        //Data::stage = STAGE_LANDED;
      }
      break;
    case LANDED:
      // turn off data logging after X seconds
      break;
    default:
      // error
      break;
  }
}

bool StateMachine::poweredAscentCheck() {
  if (liftoffCache[cycle % LIFTOFF_LOOP_LENGTH] == 1) {
    liftoffCount--;
  }
  liftoffCache[cycle % LIFTOFF_LOOP_LENGTH] = 0; // reset tile state each loop iteration
  if (liftoffCount >= LIFTOFF_CONFIDENCE) { // enough accel values are above threshold to trigger liftoff event
    return true;
  }
  Vector3D netAcceleration = Vector3D();//Data::get(PROCESSED, BNO_NET_ACCELERATION));
  // negative sign due to BNO thinking downward is positive
  float minAcceleration = -netAcceleration.maxValue();
  if (minAcceleration > LIFTOFF_THRESHOLD) { // upwards acceleration on smallest axis, i.e. axis experiecing the largest gravitational acceleration begins accelerating above threshold
    liftoffCache[cycle % LIFTOFF_LOOP_LENGTH] = 1; // update tile state
    liftoffCount++;
  }
  return false;
}

bool StateMachine::coastingCheck() {
  if (burnoutCache[cycle % BURNOUT_LOOP_LENGTH] == 1) {
    burnoutCount--;
  }
  burnoutCache[cycle % BURNOUT_LOOP_LENGTH] = 0; // reset tile state each loop iteration
  if (burnoutCount >= BURNOUT_CONFIDENCE) { // enough accel values are below threshold to trigger coasting event
    return true;
  }
  Vector3D netAcceleration = Vector3D();//Data::get(PROCESSED, BNO_NET_ACCELERATION));
  // negative sign due to BNO thinking downward is positive
  float minAcceleration = -netAcceleration.maxValue();
  if (minAcceleration < BURNOUT_THRESHOLD) { // upwards acceleration on smallest axis, i.e. axis experiecing the largest gravitational acceleration begins accelerating above threshold
    burnoutCache[cycle % BURNOUT_LOOP_LENGTH] = 1; // update tile state
    burnoutCount++;
  }
  return false;
}

bool StateMachine::landingCheck() {
  return true;
}
