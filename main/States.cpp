#include "States.h"
#include "StateMachine.h"

void StandbyState::onEntry() {
	//memset(array, 0, sizeof(array));
	LOG("Entering standby state");
}
void StandbyState::update(StateMachine* stateMachine) {
  static int counter = 0;
	LOG("Standby " + String(counter));
  stateMachine->changeState(STATE_POWERED_ASCENT);
  counter++;
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
  stateMachine->changeState(STATE_COASTING);
  counter++;
}
void PoweredAscentState::onExit() {
  LOG("Exiting powered ascent state");
}

void CoastingState::onEntry() {
  //memset(array, 0, sizeof(array));
  LOG("Entering coasting state");
}
void CoastingState::update(StateMachine* stateMachine) {
  static int counter = 0;
  LOG("Coasting " + String(counter));
  stateMachine->changeState(STATE_DROGUE_DESCENT);
  counter++;
}
void CoastingState::onExit() {
  LOG("Exiting coasting state");
}

void DrogueDescentState::onEntry() {
  //memset(array, 0, sizeof(array));
  LOG("Entering drogue descent state");
}
void DrogueDescentState::update(StateMachine* stateMachine) {
  static int counter = 0;
  LOG("Drogue descent " + String(counter));
  stateMachine->changeState(STATE_MAIN_DESCENT);
  counter++;
}
void DrogueDescentState::onExit() {
  LOG("Exiting drogue descent state");
}

void MainDescentState::onEntry() {
  //memset(array, 0, sizeof(array));
  LOG("Entering main descent state");
}
void MainDescentState::update(StateMachine* stateMachine) {
  static int counter = 0;
  LOG("Main descent " + String(counter));
  stateMachine->changeState(STATE_LANDED);
  counter++;
}
void MainDescentState::onExit() {
  LOG("Exiting main descent state");
}

void LandedState::onEntry() {
  //memset(array, 0, sizeof(array));
  LOG("Entering landed state");
}
void LandedState::update(StateMachine* stateMachine) {
  static int counter = 0;
  LOG("Landed " + String(counter));
  counter++;
}
void LandedState::onExit() {
  LOG("Exiting landed state");
}
