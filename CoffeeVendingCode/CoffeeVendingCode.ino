#include "SysControl.h"
SysControl sysControl;

void setup() {
  sysControl.init();
  Serial.println("DEBUG: Setup Complete");
}

void loop() {
  sysControl.update();
}
