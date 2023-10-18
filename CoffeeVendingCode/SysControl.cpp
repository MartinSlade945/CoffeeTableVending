#include "SysControl.h"
SysControl::SysControl() {}

void SysControl::init() {
  Serial.begin(115200);
  Serial.println("Serial Connected");

  lift.init(LIFT_ENABLE_PIN, LIFT_DIRECTION_PIN, LIFT_STEP_PIN, LIFT_HOMING_PIN);
  leftSodaDispenser.init(LEFT_SOLENOID_PIN);
  rightSodaDispenser.init(RIGHT_SOLENOID_PIN);
  candyDispenser1.init(CANDY_1_ENABLE_PIN, CANDY_1_DIRECTION_PIN, CANDY_1_STEP_PIN);
  candyDispenser2.init(CANDY_2_ENABLE_PIN, CANDY_2_DIRECTION_PIN, CANDY_2_STEP_PIN);
  candyDispenser3.init(CANDY_3_ENABLE_PIN, CANDY_3_DIRECTION_PIN, CANDY_3_STEP_PIN);
}

void SysControl::update() {
  lift.update();
  candyDispenser1.update();
  candyDispenser2.update();
  candyDispenser3.update();
  leftSodaDispenser.update();
  rightSodaDispenser.update();

  switch (actionState) {
    case WAITING_INPUT:
      readButtons();
      break;
    case START_LIFT_FALLING:
      lift.down();
      actionState = LIFT_FALLING;
      break;
    case LIFT_FALLING:
      if (!lift.busy()) {
        actionState = START_DISPENSING;
      }
      break;
    case START_DISPENSING:
      actionState = DISPENSING;
      StartDispensing();
      break;
    case DISPENSING:
      HandleDispensing();
      break;
    case START_LIFT_RISING:
      lift.up();
      actionState = LIFT_RISING;
      break;
    case LIFT_RISING:
      if (!lift.busy()) {
        actionState = WAITING_INPUT;
        dispenseOption = NONE;
      }
      break;
  }
}
void SysControl::readButtons() {
  bool readSodaButton1 = digitalRead(SODA_BUTTON_1_PIN);
  bool readSodaButton2 = digitalRead(SODA_BUTTON_2_PIN);
  bool readCandyButton1 = digitalRead(CANDY_BUTTON_1_PIN);
  bool readCandyButton2 = digitalRead(CANDY_BUTTON_2_PIN);
  bool readCandyButton3 = digitalRead(CANDY_BUTTON_3_PIN);

  if (readSodaButton1 && !sodaButton1State) {
    dispenseOption = SODA1;
    actionState = START_LIFT_FALLING;
  }
  if (readSodaButton2 && !sodaButton2State) {
    dispenseOption = SODA2;
    actionState = START_LIFT_FALLING;
  }
  if (readCandyButton1 && !candyButton1State) {
    dispenseOption = CANDY1;
    actionState = START_LIFT_FALLING;
  }
  if (readCandyButton2 && !candyButton2State) {
    dispenseOption = CANDY2;
    actionState = START_LIFT_FALLING;
  }
  if (readCandyButton3 && !candyButton3State) {
    dispenseOption = CANDY3;
    actionState = START_LIFT_FALLING;
  }

  sodaButton1State = readSodaButton1;
  sodaButton2State = readSodaButton2;
  candyButton1State = readCandyButton1;
  candyButton2State = readCandyButton2;
  candyButton3State = readCandyButton3;
}

void SysControl::StartDispensing() {
  switch (dispenseOption) {
    case SODA1:
      leftSodaDispenser.dispense();
      break;
    case SODA2:
      rightSodaDispenser.dispense();
      break;
    case CANDY1:
      candyDispenser1.dispense();
      break;
    case CANDY2:
      candyDispenser2.dispense();
      break;
    case CANDY3:
      candyDispenser3.dispense();
      break;
    case NONE:
      break;
  }
}

void SysControl::HandleDispensing() {
  switch (dispenseOption) {
    case SODA1:
      if (!leftSodaDispenser.busy()) {
        actionState = START_LIFT_RISING;
      }
      break;
    case SODA2:
      if (!rightSodaDispenser.busy()) {
        actionState = START_LIFT_RISING;
      }
      break;
    case CANDY1:
      if (!candyDispenser1.busy()) {
        actionState = START_LIFT_RISING;
      }
      break;
    case CANDY2:
      if (!candyDispenser2.busy()) {
        actionState = START_LIFT_RISING;
      }
      break;
    case CANDY3:
      if (!candyDispenser3.busy()) {
        actionState = START_LIFT_RISING;
      }
      break;
    case NONE:
      break;
  }
}