#include "SysControl.h"
SysControl::SysControl() {}

void SysControl::init() {
  Serial.begin(115200);
  Serial.println("Serial Connected");

  leftSodaDispenser.init(LEFT_SOLENOID_PIN);
  rightSodaDispenser.init(RIGHT_SOLENOID_PIN);

  lift.init(LIFT_ENABLE_PIN, LIFT_DIRECTION_PIN, LIFT_STEP_PIN, LIFT_HOMING_PIN);
  
  candyDispenser1.init(CANDY_1_ENABLE_PIN, CANDY_1_DIRECTION_PIN, CANDY_1_STEP_PIN);
  candyDispenser2.init(CANDY_2_ENABLE_PIN, CANDY_2_DIRECTION_PIN, CANDY_2_STEP_PIN);
  candyDispenser3.init(CANDY_3_ENABLE_PIN, CANDY_3_DIRECTION_PIN, CANDY_3_STEP_PIN);

  soda1Button.init(SODA_BUTTON_1_PIN);
  soda2Button.init(SODA_BUTTON_2_PIN);
  candy1Button.init(CANDY_BUTTON_1_PIN);
  candy2Button.init(CANDY_BUTTON_2_PIN);
  candy3Button.init(CANDY_BUTTON_3_PIN);
}

void SysControl::update() {
  lift.update();
  candyDispenser1.update();
  candyDispenser2.update();
  candyDispenser3.update();
  leftSodaDispenser.update();
  rightSodaDispenser.update();
  soda1Button.update();
  soda2Button.update();
  candy1Button.update();
  candy2Button.update();
  candy3Button.update();
}

void SysControl::runStateModel() {
  switch (actionState) {
    case WAITING_INPUT:
      readButtons();
      break;
    case START_LIFT_FALLING:
      Serial.println("DEBUG: Lowering Lift");
      lift.down();
      actionState = LIFT_FALLING;
      break;
    case LIFT_FALLING:
      if (!lift.busy()) {       
        actionState = START_DISPENSING;
      }
      break;
    case START_DISPENSING:
      Serial.println("DEBUG: Start Dispensing");
      actionState = DISPENSING;
      StartDispensing();
      break;
    case DISPENSING:
      HandleDispensing();
      break;
    case START_LIFT_RISING:
      Serial.println("DEBUG: Waiting for Soda");
      delay(sodaFallTime);
      Serial.println("DEBUG: Lift Rising");
      lift.up();
      actionState = LIFT_RISING;
      break;
    case LIFT_RISING:
      if (!lift.busy()) {
        Serial.println("DEBUG: Complete!");
        actionState = WAITING_INPUT;
        dispenseOption = NONE;
      }
      break;
  }
}

void SysControl::readButtons() {
  if (soda1Button.readButton()) {
    Serial.println("DEBUG: Button 1!");
    dispenseOption = SODA1;
    actionState = START_LIFT_FALLING;
  }
  else if (soda2Button.readButton()) {
    Serial.println("DEBUG: Button 2!");
    dispenseOption = SODA2;
    actionState = START_LIFT_FALLING;
  }
  else if (candy1Button.readButton()) {
    Serial.println("DEBUG: Button 3!");
    dispenseOption = CANDY1;
    actionState = START_LIFT_FALLING;
  }
  else if (candy2Button.readButton()) {
    Serial.println("DEBUG: Button 4!");
    dispenseOption = CANDY2;
    actionState = START_LIFT_FALLING;
  }
  else if (candy3Button.readButton()) {
    Serial.println("DEBUG: Button 5!");
    dispenseOption = CANDY3;
    actionState = START_LIFT_FALLING;
  }
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