// Including the cube library
// Provides code for all of the satellite functions
#include "Cube.h"

void setup() {
  // Setting the blue LED pin as a digital output
  // LED_BLUE is defined in the cube library
  pinMode(LED_BLUE, OUTPUT);
}

void loop() {
  // The code in this loop() will be continually repeated
  digitalWrite(LED_BLUE, HIGH); // Turning on the blue LED
  delay(1000); // Waiting one second
  digitalWrite(LED_BLUE, LOW); // Turning off the blue LED
  delay(1000); // Waiting one second
}