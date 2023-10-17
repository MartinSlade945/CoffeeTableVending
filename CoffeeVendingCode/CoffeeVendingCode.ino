#include "SysControl.h"
SysControl sysControl;

void setup() {
  sysControl.init();
}

void loop() {
  sysControl.update();
}
