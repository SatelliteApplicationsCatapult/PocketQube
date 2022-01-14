// Ubo diagnostics shell

#include "Cube.h"
#include "MemoryFree.h"
#include <SPI.h>
#include <SD.h>
#include <string>

#define ARDUINO_MONITOR // For built in serial monitor. Prints blank lines
//#define TERMINAL_EMULATOR // For true emulators. Uses clear-screen commands

Cube ubo; //Declare an instance of the cube class, ubo.

uint8_t menuInput, inputArray[20] = {0};
uint8_t primaryMenu, menuSelect;

bool isMenuMain = 1;
bool isMenuSys = 0;
bool isMenuSh = 0;
bool isMenuSD = 0;

float battCurrent, battVoltage, solCurrent, solVoltage, sysCurrent, swiCurrent;

Sd2Card card;
SdVolume volume;
//SdFile root;

void setup() {
  ubo.initialise(); //Default baud rate is 115200
  menuMain();
}

void loop() {
  Serial.flush(); //Waits for the serial data to disappear
  if (Serial.available() > 1) {
    int i = 0;
    while (Serial.available()) {
      inputArray[i] = Serial.read();
      i++;
    }
  } else if (Serial.available()) {
    menuInput = Serial.read();

    if (isMenuMain) {
      switch (menuInput) {
        case 49:
          isMenuMain = 0;
          menuSys();
          break;
        case 50:
          isMenuMain = 0;
          menuSh();
          break;
        case 51:
          isMenuMain = 0;
          menuSD();
          break;
        default:
          invalidInput();
          menuMain();
      }
    } else if (isMenuSys) {
      switch (menuInput) {
        case 49:
          sysInfo();
          break;
        case 50:
          sysStat();
          break;
        case 51:
          sysTest();
          break;
        case 52:
          isMenuMain = 1;
          isMenuSys = 0;
          menuMain();
          break;
        default:
          invalidInput();
          menuSys();
      }
    } else if (isMenuSh) {
      switch (menuInput) {
        case 49:
          compCam();
          break;
        case 50:
          compIMU();
          break;
        case 51:
          compLight();
          break;
        case 52:
          compTemp();
          break;
        case 53:
          compSD();
          menuSh();
          break;
        case 54:
          compRF();
          break;
        case 55:
          compEPS();
          break;
        case 56:
          isMenuMain = 1;
          isMenuSh = 0;
          menuMain();
          break;
        default:
          invalidInput();
          menuSh();
      }
    } else if (isMenuSD) {
      switch (menuInput) {
        case 49:
          //View SD card information
          compSD();
          menuSD();
          break;
        case 50:
          //Transfer files over serial
          sdFileTransfer();
          charToContinue();
          menuSD();
          break;
        case 51:
          //View files on SD card
          Serial.println("1");
          Serial.println("2");
          File rootDirc = SD.open("/");
          Serial.println("3");
          printDirectory(rootDirc, 0);
          rootDirc.close();
          Serial.println("Que");
          charToContinue();
          Serial.println("Quebo");
          menuSD();
          break;
        case 52:
          //Exit menu
          isMenuMain = 1;
          isMenuSD = 0;
          menuMain();
          break;
        default:
          invalidInput();
          menuSD();
      }
    }
  }
}

void clearTerm() {
#if defined ARDUINO_MONITOR
  for (int i = 0; i < 50; i++) {
    Serial.print("\n");
  }
#elif defined TERMINAL_EMULATOR
  Serial.write(27);       // ESC command
  Serial.print("[2J");    // clear screen command
  Serial.write(27);
  Serial.print("[H");     // cursor to home command
#endif
}

void menuMain() {
  clearTerm();
  Serial.println();
  Serial.println("------------------------------------------");
  Serial.println("Ubo diagnostics shell: main menu");
  Serial.println("1) System report");
  Serial.println("2) Component interface ");
  Serial.println("3) Storage interface");
  Serial.println("------------------------------------------");
}

/////// SUB MENUS /////////

void invalidInput() {
  Serial.println("------------------------------------------");
  Serial.println("Input not recognised, please try again");
  Serial.println("------------------------------------------");
}

void menuSys() {
  clearTerm();
  isMenuSys = 1;
  Serial.println();
  Serial.println("------------------------------------------");
  Serial.println("Ubo diagnostics shell: System report");
  Serial.println("1) Basic system information");
  Serial.println("2) Current status");
  Serial.println("3) Full system self test report");
  Serial.println("4) <? Main menu");
  Serial.println("------------------------------------------");
}

void menuSh() {
  clearTerm();
  isMenuSh = 1;
  Serial.println();
  Serial.println("------------------------------------------");
  Serial.println("Ubo diagnostics shell: Component interface");
  Serial.println("1) Camera");
  Serial.println("2) Inertial Measurement Unit (IMU)");
  Serial.println("3) Light sensor");
  Serial.println("4) Temperature sensor");
  Serial.println("5) SD card");
  Serial.println("6) Radio");
  Serial.println("7) Electric Power System (EPS)");
  Serial.println("8) <? Main menu");
  Serial.println("------------------------------------------");
}

void menuSD() {
  clearTerm();
  isMenuSD = 1;
  Serial.println();
  Serial.println("------------------------------------------");
  Serial.println("Ubo diagnostics shell: Storage interface");
  Serial.println("1) View SD card information");
  Serial.println("2) View files on SD card");
  Serial.println("3) Transfer files over serial");
  Serial.println("4) <? Main menu");
  Serial.println("----------------------------------------");
}

///////// SUBROUTINES /////////////

void sysInfo() {
  clearTerm();
  Serial.println("UBO pocketQube V2.0");
  Serial.println("Hardware revision 2.1");
  Serial.println("Software revision 0.8.16");
  charToContinue();
  menuSys();
}

void sysStat() {
  clearTerm();
  Serial.println("Power system information: ");
  if (ubo.eps.chgFlag) {
    Serial.println("EPS charging");
  }
  else {
    Serial.println("EPS not plugged in");
  }

  Serial.println("System currently running at full clock speed");
  charToContinue();
  menuSys();
}

void sysTest() {
  clearTerm();
  Serial.println("Initiating full system self test...");
  Serial.print("Enabling power to camera... ");
  if (ubo.eps.outputSet(OUTPUT_3V3_2, 1)) {
    Serial.println("Success!");
  } else {
    Serial.println("Failed");
  }
  delay(500); // Give it a second to stabilise
  Serial.print("Initialising camera module... ");
  if (ubo.camera.init(115200)) {
    Serial.println("Success!");
  } else {
    Serial.println("Failed");
  }
  //Serial.print("reset: "); Serial.println(ubo.camera.reset()); // reset camera
  Serial.print("Setting temporary communications baud rate to 115200... ");
  if (ubo.camera.baudTemp(115200)) {
    Serial.println("Success!");
  } else {
    Serial.println("Failed");
  }
  ubo.eps.outputSet(OUTPUT_3V3_2, 0);
  Serial.println("Requesting data from IMU");
  Serial.println("Accelerometer readings in the X, Y and Z axis respectively: ");
  Serial.print(ubo.telemetry.getAccelX(), 2);
  Serial.print(", ");
  Serial.print(ubo.telemetry.getAccelY(), 2);
  Serial.print(", ");
  Serial.println(ubo.telemetry.getAccelZ(), 2);
  Serial.print("Current temperature: ");
  Serial.print(ubo.telemetry.getTemperature());
  Serial.println(" degrees celsius");
  Serial.println("TMP102 sensor functioning normally");
  Serial.println("Testing SD card functionality");

  Serial.print("Initialising SD card... ");

  if (!card.init(SPI_HALF_SPEED, CS_SD)) {
    Serial.println("Failed");
  }

  else {
    Serial.println("Success!");
  }

  Serial.print("Card type: ");
  switch (card.type()) {
    case SD_CARD_TYPE_SD1:
      Serial.println("SD1");
      break;
    case SD_CARD_TYPE_SD2:
      Serial.println("SD2");
      break;
    case SD_CARD_TYPE_SDHC:
      Serial.println("SDHC");
      break;
    default:
      Serial.println("Unknown");
  }
  Serial.print("Mounting volume... ");
  if (!volume.init(card)) {
    Serial.println("Failed. Is the card formatted to FAT32?");
  } else {
    Serial.println("Success!");
  }
  uint32_t volumesize;
  Serial.print("Volume type is FAT");
  Serial.println(volume.fatType(), DEC);

  volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
  volumesize *= volume.clusterCount();       // we'll have a lot of clusters
  if (volumesize < 8388608ul) {
    Serial.print("Volume size (bytes): ");
    Serial.println(volumesize * 512);        // SD card blocks are always 512 bytes
  }
  Serial.print("Volume size (Kbytes): ");
  volumesize /= 2;
  Serial.println(volumesize);
  Serial.print("Volume size (Mbytes): ");
  volumesize /= 1024;
  Serial.println(volumesize);
  Serial.println("Configuring RFM69 radio module");
  ubo.eps.outputSet(OUTPUT_3V3_1, 1); // Turn on radio
  delay(500);
  if (ubo.radio.initialise(55)) {
    Serial.println("Radio initialisation successful");
  } else {
    Serial.println("Radio initialisation failed");
  }
  Serial.println("Test complete");
  ubo.eps.outputSet(OUTPUT_3V3_1, 0); // Turn off radio
  Serial.println("System self test complete");
  charToContinue();
  menuSys();
}

void compCam() { //Take picture using camera
  Serial.print("Enabling power to camera... ");
  if (ubo.eps.outputSet(OUTPUT_3V3_2, 1)) {
    Serial.println("Success!");
  } else {
    Serial.println("Failed");
  }
  delay(500); // Give it a second to stabilise
  Serial.print("Initialising camera module... ");
  if (ubo.camera.init(115200) ) {
    Serial.println("Success!");
  } else {
    Serial.println("Failed");
  }
  //Serial.print("reset: "); Serial.println(ubo.camera.reset()); // reset camera
  Serial.print("Setting temporary communications baud rate to 115200... ");
  if (ubo.camera.baudTemp(115200) ) {
    Serial.println("Success!");
  } else {
    Serial.println("Failed");
  }
  Serial.print("Commanding camera to take picture to internal buffer... ");
  if (ubo.camera.takePic() ) {
    Serial.println("Success!");
  } else {
    Serial.println("Failed");
  }
  Serial.println("Requesting image size in bytes... "); // picture length
  ubo.camera.getLen();
  Serial.print(ubo.camera.jpglen);
  Serial.println(" bytes of image data in buffer");
  Serial.println("Camera test completed");
  ubo.eps.outputSet(OUTPUT_3V3_2, 0); // Turn on camera
  charToContinue();
  menuSh();
}

void compIMU() { //Take readings from inertial measurement unit
  Serial.println("Accelerometer readings in the X, Y and X axis respectively:");
  Serial.print(ubo.telemetry.getAccelX(), 2);
  Serial.print(", ");
  Serial.print(ubo.telemetry.getAccelY(), 2);
  Serial.print(", ");
  Serial.println(ubo.telemetry.getAccelZ(), 2);
  Serial.println("Gyroscope readings in the X, Y and X axis respectively:");
  Serial.print(ubo.telemetry.getGyroX(), 2);
  Serial.print(", ");
  Serial.print(ubo.telemetry.getGyroY(), 2);
  Serial.print(", ");
  Serial.println(ubo.telemetry.getGyroZ(), 2);
  Serial.println("Magnetometer readings in the X, Y and X axis respectively:");
  Serial.print(ubo.telemetry.getMagX(), 2);
  Serial.print(", ");
  Serial.print(ubo.telemetry.getMagY(), 2);
  Serial.print(", ");
  Serial.println(ubo.telemetry.getMagZ(), 2);
  Serial.println("Computed orientation readings:");
  Serial.print("Roll, "); Serial.println(ubo.telemetry.getRoll(), 2);
  Serial.print("Pitch, "); Serial.println(ubo.telemetry.getPitch(), 2);
  Serial.print("Yaw, "); Serial.println(ubo.telemetry.getYaw(), 2);
  Serial.println("End of IMU readings");
  charToContinue();
  menuSh();
}

void compLight() {
  Serial.println("Retriving values from SI1145 light sensor module");
  Serial.print("Visible light reading: "); Serial.println(ubo.telemetry.getVisible());
  Serial.print("Infra red reading: "); Serial.println(ubo.telemetry.getIR());
  Serial.print("Ultra violet reading: "); Serial.println(ubo.telemetry.getUV());
  Serial.println("All values returned from sensor module, test complete");
  charToContinue();
  menuSh();
}

void compTemp() {
  Serial.println("Retrieving values from the TMP102 temperature sensor");
  Serial.print("Current temperature: ");
  Serial.print(ubo.telemetry.getTemperature());
  Serial.println(" degrees celsius");
  Serial.println("All values returned from sensor module, test complete");
  charToContinue();
  menuSh();
}


void compSD() {
  Serial.print("Initialising SD card... ");
  if (!card.init(SPI_HALF_SPEED, CS_SD)) {
    Serial.println("Failed");
  }

  else {
    Serial.println("Success!");
  }

  Serial.print("Card type: ");
  switch (card.type()) {
    case SD_CARD_TYPE_SD1:
      Serial.println("SD1");
      break;
    case SD_CARD_TYPE_SD2:
      Serial.println("SD2");
      break;
    case SD_CARD_TYPE_SDHC:
      Serial.println("SDHC");
      break;
    default:
      Serial.println("Unknown");
  }
  Serial.print("Mounting volume... ");
  if (!volume.init(card)) {
    Serial.println("Failed. Is the card formatted to FAT32?");
  } else {
    Serial.println("Success!");
  }
  uint32_t volumesize;
  Serial.print("Volume type is FAT");
  Serial.println(volume.fatType(), DEC);

  volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
  volumesize *= volume.clusterCount();       // we'll have a lot of clusters
  if (volumesize < 8388608ul) {
    Serial.print("Volume size (bytes): ");
    Serial.println(volumesize * 512);        // SD card blocks are always 512 bytes
  }
  Serial.print("Volume size (Kbytes): ");
  volumesize /= 2;
  Serial.println(volumesize);
  Serial.print("Volume size (Mbytes): ");
  volumesize /= 1024;
  Serial.println(volumesize);
  charToContinue();
  //menuSh();
}

void compRF() {
  Serial.println("Configuring RFM69 radio module");
  ubo.eps.outputSet(OUTPUT_3V3_1, 1); // Turn on radio
  delay(500);
  if (ubo.radio.initialise(55)) {
    Serial.println("Radio initialisation successful");
  } else {
    Serial.println("Radio initialisation failed");
  }
  Serial.println("Test complete");
  ubo.eps.outputSet(OUTPUT_3V3_1, 0); // Turn off radio
  charToContinue();
  menuSh();
}

void compEPS() {

  Serial.println("Displaying EPS statistics \n");

//  Wire.beginTransmission(ADDR_EPS);
//  //Read from high and low battery current registers
//  //Wire.write(B00001000);
//  Wire.write(0x00); //Slave tX
//  Wire.endTransmission();
//
//  Wire.requestFrom(ADDR_EPS, 100);
  while (Wire.available()) {
    Serial.println(Wire.read());
  }
    Serial.println("Scanning for I2C devices");
    byte error, address;
    int nDevices;
  
    for (address = 1; address < 127; address ++) {
      Wire.beginTransmission(address);
      error = Wire.endTransmission();
  
  
    if (error == 0) {
      Serial.print("I2C at 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }

  }

  //Print battery voltage
  battVoltage = ubo.eps.batteryVoltage();
  Serial.print("Battery voltage: ");
  Serial.print(battVoltage);
  Serial.println(" V");

  //Print battery current
  battCurrent = ubo.eps.batteryCurrent();
  Serial.print("Battery output current: ");
  Serial.print(abs(battCurrent));
  Serial.println(" A");
  if (battCurrent > 0) {
    Serial.println("Battery charging");
  }
  else {
    Serial.println("Battery discharging");
  }

  //Print combined solar panel current
  solCurrent = ubo.eps.solarCurrent();
  Serial.print("Solar current: ");
  Serial.print(solCurrent);
  Serial.println(" A");
  
  //Print combined solar panel voltage
  solVoltage = ubo.eps.solarVoltage();
  Serial.print("Solar voltage: ");
  Serial.print(solVoltage);
  Serial.println(" V");

  //Print system current - total current drawn on the 3.3V system line
  //Includes MCU, IMU, light and temperature sensors, SD card and the EPS itself
  sysCurrent = ubo.eps.systemCurrent();
  Serial.print("System current: ");
  Serial.print(sysCurrent);
  Serial.println(" V");

  //Print switched current - total current drawn on the switched 3.3V lines
  //Includes RFM69 radio and camera payload
  swiCurrent = ubo.eps.switchedCurrentReg();
  Serial.print("Switched current: ");
  Serial.print(swiCurrent);
  Serial.println(" A");

  charToContinue();
  menuSh();

}

void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry = dir.openNextFile();
    if (!entry) {
      //No more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    }
    else {
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}

void sdFileTransfer() {
  if (!SD.begin(CS_SD)) {
    Serial.println("Card failed or not present");
    return;
  }

  const byte numChars = 32;
  char receivedChars[numChars];
  char endMarker = '\n';
  char rc;
  int ndx = 0;
  String fileName;
  String contents;
  
  Serial.println("Card initialized");
  Serial.println("Enter file name: ");
  while (Serial.available()==0) {
    //Wait for user input
  }
  fileName = Serial.readString(); //Read user input
  const char * fileNameC = fileName.c_str();
  if (SD.exists(fileNameC)) {
    Serial.println(fileName + " already exists");
  }
  else {
    File myFile = SD.open(fileNameC, FILE_WRITE);
    Serial.println("Enter contents of file: ");
    while (Serial.available()==0) {
      //Wait for user input
    }

    contents = Serial.readString();
    const char * contentsC = contents.c_str();
    myFile.write(contentsC);
    //myFile.flush();
    
//    while (Serial.available()) {
//      //Read serial monitor input
//      Serial.println("Enter contents: ");
//      
//      rc = Serial.read();
//
//      while (rc != endMarker) {
//        //Input ends with new line
//        if (ndx <= numChars) {
//          receivedChars[ndx] = rc;
//          ndx++;
//        }
//        else {
//          myFile.write(receivedChars, numChars); //Write the buffer to file
//          ndx = 0;
//        }
//      }
//      Serial.println("Input written to file.");
//      
//    }
    Serial.println("Input written to file.");
    myFile.close();
    Serial.println("File closed.");
  }

  //Input the information

  Serial.println("File successfully saved!");
}

void charToContinue() {
  Serial.flush();
  Serial.println("Enter any character to continue...");
  while (!Serial.available()) {};
  while (Serial.available()) {
    Serial.read();
  }
}
