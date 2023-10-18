#include "CandyDispenser.h"

void CandyDispenser::init(int Enable, int Direction, int Step) {
  enablePin = Enable;
  stepPin = Step;
  directionPin = Direction;

  coilMotor = new AccelStepper(1, stepPin, directionPin);
  coilMotor->setMaxSpeed(motorSpeed);
  coilMotor->setAcceleration(motorAccel);
  coilMotor->setEnablePin(enablePin);
  coilMotor->setPinsInverted(false, false, true);
}

void CandyDispenser::dispense() {
  coilMotor->move(stepsPerRotation); //rotate one rev
}

void CandyDispenser::update() {
  coilMotor->run();
}

bool CandyDispenser::busy() {
  if (!coilMotor->isRunning()) {
    return true;
  }
  return false;
}
