// Including the cube library
// Provides code for all of the satellite functions
#include "Cube.h" 

#define SATELLITE_ID 55 // Giving our satellite a unique ID between 0 and 120

// Declaring an instance of the cube class, ubo.
// We access the class functions through this instance.
Cube ubo;

void setup() {

  // Initialising the satellite with a 5 second timeout
  // Code will continue to execute after 5 seconds even if a serial monitor is not connected
  ubo.initialise(1, 115200, 5);

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
}

void loop() {

  // Defining our beacon message
  // We can only transmit 60 bytes in a single packet, so our message must be shorter than that.
  // This message is 30 bytes long
  char beaconMessage[] = "UBO_55 alive and transmitting!";

  // Now we will transmit our message
//  Serial.println("Sending message...");
  ubo.radio.sendPacket(beaconMessage);

  // Transmitting takes power, we want to wait between transmissions to avoid using too much power
  delay(10000);  
}
