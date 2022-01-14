// Including the cube library, which will include all other dependencies
#include "Cube.h"

// Declaring instance of the cube object to work with
Cube ubo;

// Giving our satellite an ID between 2 and 99
#define SATELLITE_ID 55

// Setting the sensitivity of the image trigger
float angleHysteresis = 10.0;

// Other global variables for working with
uint32_t timer, idleTimer;
uint32_t bytesRemain;

// fault handler forward declaration
void fault(uint8_t id, bool radio = false,  const void* description = null, uint8_t descriptionSize = 0);

void setup() {

  ledInit(); // Initialise LEDs and EPS

  ubo.eps.outputSet(OUTPUT_3V3_1, 1); // Power on radio

  delay(500);

  if (!ubo.radio.initialise(SATELLITE_ID)) {
    fault(1); // Grr... No radio so will just flash an LED angrily.
  }

  // Transmit message to groundstation
  uint8_t msgInit[] = "Satellite status: Initialising...";
  if (!ubo.radio.sendMessage(msgInit, sizeof(msgInit), 1, true, 15)) {
    fault(2, true, "No response from groundstation", 31);
  }
  delay(3000);

  // see if the card is present and can be initialized:
  if (!SD.begin(CS_SD)) {
    fault(3, true, "SD card could not be initialised", 33);
  }
  idleTimer = millis();
}

void loop() {

  Serial.begin(115200); // In case we plug it in while running

  uint32_t latchTime = millis();

  bool led = false;

  while (1) { // Image trigger routine
    if ((millis() - idleTimer) > 5000) { // Transmit idle status every 5 seconds
      uint8_t msgIdle[] = "Satellite status: idle";
      // Transmit to groundstation, request ACK, repeat 15 times
      if (!ubo.radio.sendMessage(msgIdle, sizeof(msgIdle), 1, true, 15)) {
        fault(2, true, "No response from groundstation", 31);
      }
      idleTimer = millis();
    }
    if (Serial) { // If radio or SD card not working, can take image directly over a USB connection instead
      Serial.println("Operating over debug serial interface");
      charToContinue();
      cameraSerial();
      while (1) {};
    }
    if ((ubo.telemetry.getRoll() > (-100 - angleHysteresis / 2.0)) & (ubo.telemetry.getRoll() < (-100 + (angleHysteresis / 2.0)))) { // Pointing the right way?
      if (!led) {
        led = true;
        latchTime = millis(); // reset latch timeout
        ubo.eps.outputSet(OUTPUT_3V3_3, 1); // No visible LEDs on top so using spare power bus...
      } else if ((millis() - latchTime) > 2000) {
        for (int i = 0; i < 6; i++) { // Lots of flashes = about to take a picture
          ubo.eps.outputSet(OUTPUT_3V3_3, 0);
          delay(50);
          ubo.eps.outputSet(OUTPUT_3V3_3, 1);
          delay(50);
        }
        break;
      }
    } else if ((millis() - latchTime) > 50) {
      led = false;
      latchTime = 0;
      ubo.eps.outputSet(OUTPUT_3V3_3, 0); // minimum period to make LED visible
    }
  }

  uint8_t msgCapt[] = "Satellite status: Capturing image";
  // Transmit to groundstation, request ACK, repeat 15 times
  if (!ubo.radio.sendMessage(msgCapt, sizeof(msgCapt), 1, true, 15)) {
    fault(2, true, "No response from groundstation", 31);
  }

  ledInit(); // turn off everything

  delay(1000); // Give it a second for voltage to stabilise...

  char filename[13];
  strcpy(filename, "IMAGE00.JPG");
  for (int i = 0; i < 100; i++) { // Note - will break when cards fill up to 100 images. May happen one of these days!
    filename[5] = '0' + i / 10;
    filename[6] = '0' + i % 10;
    // create if does not exist, do not open existing, write, sync after write
    if (! SD.exists(filename)) {
      break;
    }
  }

  // Create instance _before_ powering camera, because SD cards are contrary like that
  File imgFile = SD.open(filename, FILE_WRITE);

  if (!imgFile) {
    fault(4, true, "Could not access image file", 28);
  }

  delay(500); // take it steady, SD card rather touchy

  ubo.eps.outputSet(OUTPUT_BAT_1, 1); // Turn on the camera power line
  delay(1000); // Give it a moment to recover, camera is very high current draw...

  ubo.camera.init(115200); // intit camera
  ubo.camera.reset(); // reset camera
  ubo.camera.baudTemp(115200); // set baudrate (again...?)
  ubo.camera.takePic(); // Take a picture
  ubo.camera.getLen();
  if (ubo.camera.jpglen < 4096) { // Actually taken a picture?
    fault(5, true, "Image capture failed", 21); // Nope. Try replacement / replugging the camera
  }

  delay(500);

  uint32_t bytesRemain = ubo.camera.getPic(4096) + 4096; // don't ask...

  if (imgFile) { // Transfer image from camera buffer to SD card
    while (bytesRemain > 0) {
      imgFile.write(ubo.camera.byteBuffer, min(4096, bytesRemain));
      bytesRemain -= min(4096, bytesRemain);
      ubo.camera.getPic(min(4096, bytesRemain));
    }
  } else {
    fault(6, true, "Corrupt image file", 19); // Drat!
  }
  imgFile.close();
  delay(200); // Again, no rush, SD card is a bit dodgy sometimes, avoid spikes from camer power off

  ubo.eps.outputSet(OUTPUT_BAT_1, 0); // Turn off the camera power line

  delay(1000); // Phew, that was arduous, let's have a breather

  imgFile = SD.open(filename, FILE_READ); // Open image file for reading, for some reason has to be while everything is powered off

  delay(500); // ?? (Can you tell I'm paranoid about this SD card)

  // Ready to transmit?
  // Let's power on the radio
  ubo.eps.outputSet(OUTPUT_3V3_1, 1);
  delay(100); // Again, no rush, just don't corrupt my card please
  // Try and open file?

  if (!imgFile) {
    fault(6, true, "Corrupt image file", 19); // Double drat, no image data today...
  } else { // Opened file for reading, let's try initialising the radio
    delay(100); // Just for good measure
    if (!ubo.radio.initialise(SATELLITE_ID)) {
      fault(1); // Grr...
    }
    ubo.radio.setPower(31); // Substituting power for CRCs at the moment...

    uint8_t imgBuf[60];
    uint32_t imgLength = imgFile.size(); // Image files from this camera never over ~50000
    while (imgLength > 0 ) {
      //      Serial.println(imgLength);
      imgFile.read(imgBuf, (min(60, imgLength))); // Read 60 byte chunks, or smaller if EOF
      if (!ubo.radio.sendMessage(imgBuf, min(60, imgLength), 1, true, 15)) { // Request ack, attempt each packet 15 times if no ack
        digitalWrite(LED_AMBER, HIGH); // Dropped packet
      }
      imgLength -= (min(60, imgLength));
    }
    //    ubo.eps.outputSet(OUTPUT_3V3_1, 0); // Turn off radio
  }
  digitalWrite(LED_AMBER, LOW);
  delay(2200);
  uint8_t msgCapture[] = "Satellite status: Capture complete";
  // Transmit to groundstation, request ACK, repeat 15 times
  if (!ubo.radio.sendMessage(msgCapture, sizeof(msgCapture), 1, true, 15)) {
    fault(2, true, "No response from groundstation", 31);
  }
  delay(1000);
  // Whoop!
}

void cameraSerial() {
  Serial.println("Enabling camera power...");
  ubo.eps.outputSet(OUTPUT_BAT_1, 1); // Turn on the camera power line
  delay(1000); // Give it a moment to recover, camera is very high current draw...
  Serial.print("Configuring camera... ");
  Serial.print(ubo.camera.init(115200));
  Serial.print(", ");
  Serial.print(ubo.camera.reset());
  Serial.print(", ");
  Serial.println(ubo.camera.baudTemp(115200));
  Serial.print("Taking picture... ");
  Serial.print(ubo.camera.takePic());
  Serial.print(", ");
  Serial.println(ubo.camera.getLen());
  uint32_t timer = millis();
  if (ubo.camera.jpglen < 4096) { // Actually taken a picture?
    Serial.print("Picture taking failed");
  } else {
    uint32_t bytesRemain = ubo.camera.getPic(4096) + 4096; // Don't ask...
    while (bytesRemain > 0) {
      for ( int i = 0; i < min(4096, bytesRemain); i ++) {
        if ( ubo.camera.byteBuffer[i] < 16 ) {
          Serial.print("0");
        }
        Serial.print(ubo.camera.byteBuffer[i], HEX);
      }
      bytesRemain -= min(4096, bytesRemain);
      ubo.camera.getPic(min(4096, bytesRemain));
    }
  }
  ubo.eps.outputSet(OUTPUT_BAT_1, 0); // Turn off the camera power line
  Serial.println();
  Serial.print(millis() - timer);
  Serial.println(" milliseconds elapsed");
  Serial.println("End of routine");
}

void ledInit() {

  pinMode(GPIO_0, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_AMBER, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);

  digitalWrite(GPIO_0, LOW);
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(LED_AMBER, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN, LOW);

  ubo.eps.outputSet(OUTPUT_3V3_1, 0);
  ubo.eps.outputSet(OUTPUT_3V3_2, 0);
  ubo.eps.outputSet(OUTPUT_3V3_3, 0);

  ubo.eps.outputSet(OUTPUT_BAT_1, 0);
  ubo.eps.outputSet(OUTPUT_BAT_2, 0);

}

void fault(uint8_t id, bool radio, const void* description, uint8_t descriptionSize) {
  if (radio) {
    ubo.eps.outputSet(OUTPUT_3V3_1, 1); // Turn it on
    delay(20);
    if (!ubo.radio.initialise(SATELLITE_ID)) {
      ubo.eps.outputSet(OUTPUT_3V3_1, 0); // Turn it off
      fault(1); // Grr...
    } else {
      const uint8_t msgFlt[] = "Satellite fault code ";
      uint8_t msgBuffer[sizeof(msgFlt) + 3];
      for (uint8_t i = 0; i < sizeof(msgFlt); i ++) {
        msgBuffer[i] = msgFlt[i];
      }
      msgBuffer[sizeof(msgFlt) - 1] = id + 48; // dec to ascii number
      msgBuffer[sizeof(msgFlt)] = 0x3A; // Colon
      msgBuffer[sizeof(msgFlt) + 1] = 0x20; // Space
      msgBuffer[sizeof(msgFlt) + 2] = null;

      // Transmit to groundstation, request ACK, repeat 15 times
      if (!ubo.radio.sendMessage(msgBuffer, sizeof(msgBuffer), 1, true, 15)) {
        fault(2);
      }
      if (!ubo.radio.sendMessage(description, min(60, descriptionSize), 1, true, 15)) {
        fault(2);
      }
    }
  }
  while (1) {
    for (int j = 0; j < id; j++) {
      digitalWrite(LED_AMBER, HIGH);
      delay(50);
      digitalWrite(LED_AMBER, LOW);
      delay(180);
    }
    delay(1000);
    if (Serial) {
      break;
    }
  }
}

void charToContinue() {
  Serial.flush();
  Serial.println("Enter any character to continue...");
  while (!Serial.available()) {};
  while (Serial.available()) {
    Serial.read();
  }
}
