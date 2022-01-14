#include "MockPayload.h"
#include <Arduino.h>

//
// PUBLIC METHODS
//

MockPayload::MockPayload() {};
MockPayload::~MockPayload() {};

void MockPayload::initialise() {
};

int MockPayload::doing(int mode, char argv[][10]) {
  Serial.print("Mock payload doing at mode: ");
  Serial.println(mode);

  if (mode == 0) {
    int i = 0;
    while ((*(argv + i)[0] != '\0') && i <= 10)
    {
      Serial.print("... instructions: ");
      Serial.println(*(argv + i));
      i++;
    }
    return i;
  } else {
    return mode;
  }
};

int MockPayload::done() {
  return 0;
};
