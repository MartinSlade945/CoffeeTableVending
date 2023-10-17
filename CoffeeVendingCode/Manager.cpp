#include "Manager.h"

Manager::Manager(){}

void Manager::init() {

  Serial.begin(115200);
  Serial.println("Serial Connected");

  //  lift.init();
    leftCanDispenser.init(LEFT_SOLENOID_PIN);
    rightCanDispenser.init(RIGHT_SOLENOID_PIN);
  //  candyVender1.init();
  //  candyVender2.init();
  //  candyVender3.init(); 
}

void Manager::update() {  
  unsigned long currentMillis = millis();  // Get the current millisecond count
  if (currentMillis - previousPollMillis >= pollingInterval) {

//    lift.Update();
    leftCanDispenser.update();
    rightCanDispenser.update();
/*
    candyVender1.Update();
    candyVender2.Update();
    candyVender3.Update();
*/
    previousPollMillis = currentMillis;  // Update the previousMillis variable to the current time
  }
}