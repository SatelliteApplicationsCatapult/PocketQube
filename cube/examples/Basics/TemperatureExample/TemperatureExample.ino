// Including the cube library
// Provides code for all of the satellite functions
#include "Cube.h" 

// Declaring an instance of the cube class, ubo.
// We access the class functions through this instance.
Cube ubo;

void setup() {
  // Initialising the satellite with default settings
  // This will start the serial monitor and wait for us to open it
  // Default buad rate: 115200
  ubo.initialise();
}

void loop() {
  
  // Creating a floating point variable to hold the temperature reading
  float temperature;

  // Setting our variable equal to the returned value of the function
  // ubo.telemetry.getTemperature()
  temperature = ubo.telemetry.getTemperature();

  // Printing the temperature to the serial monitor
  Serial.print("The external temperature is ");
  Serial.print(temperature, 2); // To two decimal places
  Serial.print(" degrees celcius");
  Serial.print("\n"); // New line

  // Waiting one second before repeating
  delay(1000);
}
