#include "StateMachine.h"

StateMachine::StateMachine() {
  cc = new CommunicationController();
  pc = new ParachuteController();
  ac = new AirbrakeController();
  // initial state set to standby and cycle to 1
  Data::setStage(STANDBY);
  Data::add(CYCLE, String(1));
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
  cycle = Data::getCycle();
  pc->update();
  // determine which axis has gravity acceleration
  if (cycle < 100) {
    Vector3D gravity = Vector3D(Data::get(GRAVITY));
    axisOfAcceleration = gravity.maxis();
  }
  acceleration = Vector3D(Data::get(LINEAR_ACCELERATION));
  determineStage();
  Data::add(CYCLE, String(cycle));
  Data::add(TRANSMISSION_TIME, String(millis() / 1000.000f));
  Data::add(STAGE, String(Data::getStage()));
  // Send everything via serials at the end of the cycle
  cc->update();
  Data::clearData();
  Data::incrementCycle();
}

void StateMachine::determineStage() {
  switch (Data::getStage()) { // switch statement because stage transition can only occur incrementally
    case STANDBY:
      // check if criteria for powered ascent are met
      if (poweredAscentCheck()) {
        Data::setStage(POWERED_ASCENT);
      }
      break;
    case POWERED_ASCENT:
      // check if criteria for coasting are met
      if (coastingCheck()) {
        Data::setStage(COASTING);
      }
      break;
    case COASTING:
      // check if criteria for drogue chute deploy are met
      if (pc->drogueDescentCheck()) {
        Data::setStage(DROGUE_DESCENT);
      }
      break;
    case DROGUE_DESCENT:
      // check if criteria for main chute deploy are met
      if (pc->mainDescentCheck()) {
        Data::setStage(MAIN_DESCENT);
      }
      break;
    case MAIN_DESCENT:
      // check if criteria for sufficient still time (i.e. landing) are met
      if (landingCheck()) {
        Data::setStage(LANDED);
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
  if (acceleration.getAxis(axisOfAcceleration) > LIFTOFF_THRESHOLD) { // upwards acceleration on smallest axis, i.e. axis experiecing the largest gravitational acceleration begins accelerating above threshold
    liftoffCache[cycle % LIFTOFF_LOOP_LENGTH] = 1; // update tile state
    liftoffCount++;
  }
  Serials::print("------------- netAccel: " + String(acceleration) + ", minAccel: " + String(acceleration.getAxis(axisOfAcceleration)) + ", Liftoff count: " + String(liftoffCount));
  if (liftoffCount >= LIFTOFF_CONFIDENCE) { // enough accel values are above threshold to trigger liftoff event
    return true;
  }
  return false;
}

bool StateMachine::coastingCheck() {
  if (burnoutCache[cycle % BURNOUT_LOOP_LENGTH] == 1) {
    burnoutCount--;
  }
  burnoutCache[cycle % BURNOUT_LOOP_LENGTH] = 0; // reset tile state each loop iteration
  if (acceleration.getAxis(axisOfAcceleration) < BURNOUT_THRESHOLD) { // upwards acceleration on smallest axis, i.e. axis experiecing the largest gravitational acceleration begins accelerating above threshold
    burnoutCache[cycle % BURNOUT_LOOP_LENGTH] = 1; // update tile state
    burnoutCount++;
  }
  Serials::print("------------- netAccel: " + String(acceleration) + ", minAccel: " + String(acceleration.getAxis(axisOfAcceleration)) + ", burnout count: " + String(burnoutCount));
  if (burnoutCount >= BURNOUT_CONFIDENCE) { // enough accel values are below threshold to trigger coasting event
    return true;
  }
  return false;
}

bool StateMachine::landingCheck() {
  return true;
}
