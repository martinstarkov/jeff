#include "States.h"
#include "StateMachine.h"

void StandbyState::onEntry() {
	//memset(array, 0, sizeof(array));
	LOG("Entering standby state");
}
void StandbyState::update(StateMachine* stateMachine) {
  static int counter = 0;
	LOG("Standby " + String(counter));
  if (counter >= 10) {
    stateMachine->changeState(STATE_POWERED_ASCENT);
    counter = 0;
  } else {
    counter++;
  }
}
void StandbyState::onExit() {
	LOG("Exiting standby state");
}

void PoweredAscentState::onEntry() {
  //memset(array, 0, sizeof(array));
  LOG("Entering powered ascent state");
}
void PoweredAscentState::update(StateMachine* stateMachine) {
  static int counter = 0;
  LOG("Powered ascent " + String(counter));
  if (counter >= 5 && true) {
    stateMachine->changeState(STATE_STANDBY);
    counter = 0;
  } else {
    counter++;
  }
}
void PoweredAscentState::onExit() {
  LOG("Exiting powered ascent state");
}
