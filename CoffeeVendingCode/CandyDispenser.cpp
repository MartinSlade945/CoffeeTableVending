#include "CandyDispenser.h"

void CandyDispenser::init(int Enable, int Direction, int Step) {
  pinMode(Enable,OUTPUT);
  digitalWrite(Enable,LOW);

  coilMotor = new AccelStepper(1, Step, Direction);
  coilMotor->setMaxSpeed(motorSpeed);
  coilMotor->setAcceleration(motorAccel);
  coilMotor->setPinsInverted(false, false, true);
}

void CandyDispenser::dispense() {
  coilMotor->move(stepsPerRotation); //rotate one rev
}

void CandyDispenser::update() {
  coilMotor->run();
}

bool CandyDispenser::busy() {
  if (coilMotor->isRunning()) {
    return true;
  }
  return false;
}
