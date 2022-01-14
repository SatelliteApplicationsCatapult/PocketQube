#include "Cube.h"   // Including the Cube library

Cube ubo;   // Declaring an instance we can use to access satellite functions

void setup() {

  // Initialising satellite
  ledInit(); // LEDs
  epsInit(); // Power system

  // Initialising serial communications
  Serial.begin(115200);
  while (!Serial) {}; // Waiting for monitor to be opened
  while (Serial.available()) {
    Serial.read(); // Clearing any existing data in the serial buffer
  }

  Serial.println("Ubo camera test");
}

void loop() {

  // Waiting for user to trigger image capture
  charToContinue();

  Serial.println("Enabling camera power...");
  ubo.eps.outputSet(OUTPUT_BAT_1, 1); // Turn on the camera power line
  delay(100); // Give it a moment to recover, camera is very high current draw

  // Printing some diagnostic information about the camera
  Serial.print("Configuring camera... ");
  Serial.print("Initialised... ");
  Serial.println(ubo.camera.init(115200));
  Serial.print("Reset...");
  Serial.println(ubo.camera.reset());
  Serial.print("Baud rate selection...");
  Serial.println(ubo.camera.baudTemp(115200));
  Serial.print("Taking picture... ");
  Serial.println(ubo.camera.takePic());
  Serial.print(ubo.camera.getLen());
  Serial.println(" bytes captured");

  uint32_t timer = millis(); // Counter to see how long it takes to transfer

  if (ubo.camera.jpglen < 4096) { // Check we actually took a picture
    Serial.print("Image capture failed, try power cycling the satellite");
  } else {
    uint32_t bytesRemain = ubo.camera.getPic(4096) + 4096; // Get the size of the image
    uint8_t imageBuffer[4096]; // Buffer to hold image data in heap while transferring
    while (bytesRemain > 0) { // Still image data left to be transferred?
      for ( int i = 0; i < min(4096, bytesRemain); i ++) {
        if ( ubo.camera.byteBuffer[i] < 16 ) { // To handle printing HEX data to serial
          Serial.print("0");
        }
        Serial.print(ubo.camera.byteBuffer[i], HEX); // Printing each element of the buffer array
      }
      bytesRemain -= min(4096, bytesRemain); // Update image size
      ubo.camera.getPic(min(4096, bytesRemain)); // Refresh buffer
    }
  }

  // Finished, let's turn off the camera
  ubo.eps.outputSet(OUTPUT_BAT_1, 0); // Turn off the camera power line

  Serial.println();
  Serial.print(millis() - timer);
  Serial.println(" milliseconds elapsed");
  Serial.println("Run demo again?");
}
void epsInit() {
  // Making sure all the switched supplies are turned off
  ubo.eps.outputSet(OUTPUT_3V3_1, 0);
  ubo.eps.outputSet(OUTPUT_3V3_2, 0);
  ubo.eps.outputSet(OUTPUT_3V3_3, 0);
  ubo.eps.outputSet(OUTPUT_BAT_1, 0);
  ubo.eps.outputSet(OUTPUT_BAT_2, 0);
}

void ledInit() {
  // Making sure all the LEDs are set as outputs
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_AMBER, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);

  // and turned off
  digitalWrite(GPIO_0, LOW);
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(LED_AMBER, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN, LOW);
}

void charToContinue() {
  Serial.flush();
  Serial.println("Enter any character to continue...");
  while (!Serial.available()) {};
  while (Serial.available()) {
    Serial.read();
  }
}