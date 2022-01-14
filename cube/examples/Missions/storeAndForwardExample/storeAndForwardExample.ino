// Including the cube library
// Provides code for all of the satellite functions
#include "Cube.h" 

#define SATELLITE_ID 55 // Giving our satellite a unique ID between 0 and 120

// Declaring an instance of the cube class, ubo.
// We access the class functions through this instance.
Cube ubo;

char messageBuffer[61]; // Extra byte to hold string terminator
char messageTransmit[61] = "default message";
long timer = 0; // transmit frequency counter

void setup() {

  // Initialising the satellite with a 5 second timeout
  // Code will continue to execute after 5 seconds even if a serial monitor is not connected
  ubo.initialise(115200, 30);

  // Enabling the 1st switched voltage line 
  // This powers on the radio
  ubo.eps.outputSet(OUTPUT_3V3_1, 1);

  // Wait a few milliseconds to allow the voltage to stabilise
  delay(100);

  // Initialising the radio with our unique ID
  if (ubo.radio.initialise(SATELLITE_ID)) {
    Serial.println("Radio initialisation successful");
  } else {
    Serial.println("Radio initialisation failed");
  }

  // Increasing the power level for more reliable communications
  ubo.radio.setPower(15);
}

void loop() {
  
  // Check for a new message
  if (ubo.radio.messageAvailable()) { // There's a message for us
    ubo.radio.receiveMessage(messageBuffer); // Updates contents of messageBuffer
    strncpy(messageTransmit, messageBuffer, sizeof(messageTransmit)); // Coppy buffer to transmit message variable
  }

  if ((millis() - timer) > 10000) { // Transmit our current message every 10 seconds
    timer = millis(); // reset timer
    ubo.radio.sendMessage(messageTransmit); // Transmitting message
  }
}
