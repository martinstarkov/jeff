#include "AirbrakeController.h"

AirbrakeController::AirbrakeController() {
  // initialize PID related things
  // double* Input, double* Output, double* Setpoint, double Kp, double Ki, double Kd, int ControllerDirection
  // Pulse width modulation
  //servo = new PWMServo();
  //servo->attach(AIRBRAKE_SERVO_PIN);
  //Bluetooth::log(SUCCESS + "Airbrake servo initialized");
  //referenceAltitude = new double(PID_REFERENCE_ALTITUDE);
  //pid = new PID(inputData, servoData, referenceAltitude, PID_PROPORTIONAL_GAIN, PID_INTEGRAL_GAIN, PID_DERIVATIVE_GAIN, PID_CONTROLLER_DIRECTION);
  //pid->SetSampleTime(PID_SAMPLE_TIME);
  //pid->SetOutputLimits(PID_MIN_OUTPUT, PID_MAX_OUTPUT);
  //pid->SetMode(PID_MODE);
  //Bluetooth::log(SUCCESS + "PID controller initialized");
}

float AirbrakeController::getServoOutput() {
  return 0;//*servoData;
}

void AirbrakeController::controlLoop(float altitude) {
  //inputData = new float(altitude);
  //pid->Compute();
}

void AirbrakeController::deployFlaps() {
  // take getServoOutput() distance value and turn it into angle the servo needs to rotate
  //rotateAngle = 0; // replace later with calculated value from above ^
  //servo->write(rotateAngle);
}
