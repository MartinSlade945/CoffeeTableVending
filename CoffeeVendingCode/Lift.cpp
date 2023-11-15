#include "Lift.h"

void Lift::init(int Enable, int Direction, int Step, int Home) {
  enablePin = Enable;
  stepPin = Step;        
  directionPin = Direction;  
  homingPin = Home;

  pinMode(enablePin,OUTPUT);
  digitalWrite(enablePin,LOW);
  pinMode(homingPin,INPUT); //Set homing pin to a digital input
  liftMotor = new AccelStepper(1, stepPin, directionPin);
  liftMotor->setMaxSpeed(upSpeedSteps);
  liftMotor->setAcceleration(upAccelSteps);
  //liftMotor->setEnablePin(enablePin);
  liftMotor->setPinsInverted(false, false, true);
}

void Lift::up() {
  if (liftState == LIFT_AT_BOTTOM) {
    liftMotor->setMaxSpeed(upSpeedSteps);
    liftMotor->setAcceleration(upAccelSteps);  
    liftMotor->moveTo(upPositionMM * stepsPerMM); //Raise lift to up position
    liftState = LIFT_RISING;
    Serial.println("LIFT: moving up");
  }
}

void Lift::down() {
  if (liftState != LIFT_LOWERING) {
    liftMotor->setMaxSpeed(downSpeedSteps); //set speed
    liftMotor->setAcceleration(downAccelSteps); //Set acceleration
    liftMotor->move(-upPositionMM * stepsPerMM * 2); //Move motor down to find homing Switch
    liftState = LIFT_LOWERING;
    Serial.println("LIFT: moving down");
  }
}

void Lift::update() {
  liftMotor->run();
  if (liftState == LIFT_LOWERING) {
    bool readSwitchState = digitalRead(homingPin);
    if (readSwitchState && !homingPinState) {
      stopMotor();
      liftMotor->setCurrentPosition(0);
      liftState = LIFT_AT_BOTTOM;
      Serial.println("LIFT: LIFT HOMED");
    }
    homingPinState = readSwitchState;
  }
  if (liftState == LIFT_RISING) {
    if (!liftMotor->isRunning()) {
      liftState = LIFT_AT_TOP;
    }
  }
}

bool Lift::busy() {
  if (liftMotor->isRunning()) {
    return true;
  }
  return false;
}

void Lift::stopMotor() {
  liftMotor->setSpeed(0);
  long getCurrentPosition = liftMotor->currentPosition();
  liftMotor->moveTo(getCurrentPosition); //Instant Stop Motor
}
