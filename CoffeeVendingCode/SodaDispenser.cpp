#include "SodaDispenser.h"

void SodaDispenser::init(int digitalOutputPin) {
  solenoidPin = digitalOutputPin; //Save digital output for solenoid
  pinMode(solenoidPin,OUTPUT); //Setup solenoid pin as a Digital Output
  digitalWrite(solenoidPin,HIGH); //Turn solenoid off
  Serial.println("SodaDispenser init complete");
}

void SodaDispenser::dispense() {
  Serial.println("Soda Dispensing");
  digitalWrite(solenoidPin,LOW); //Turn solenoid on
  unsigned long nowTime = millis(); //get current time in milliSeconds
  endTimeMillis = nowTime + solenoidTimeout; //store time to turn off solenoid
}

void SodaDispenser::update() {
  unsigned long nowTime = millis(); //get current time in milliseconds
  if (nowTime > endTimeMillis) { 
    digitalWrite(solenoidPin,HIGH); //Turn off solenoid
  }
}

bool SodaDispenser::busy() {
  unsigned long nowTime = millis(); //get current time in milliseconds
  if (nowTime > endTimeMillis) { 
    return false;
  }
  return true;
}