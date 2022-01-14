#ifndef CUBE_H
#define CUBE_H

#include <Arduino.h>		// Access to core arduino functions
#include <stdint.h>         // Access the integers of a defined size
#include <stdbool.h>        // Access to C standard boolean functions
#include <SPI.h>			// Native arduino SPI library (SPI4teensy3 still experimental)
#include <Wire.h>			// Native arduino I2C library (i2c_t3 still experimental)
#include <SD.h>             // Default arduino SD card library
#include "Config.h"			// Global preprocessor definitions
#include "Telemetry.h" 		// Interal telemetry library
#include "Camera.h"			// Internal PTC06 camera library
#include "Radio.h"			// RFM69 433MHz transceiver module
#include "EPS.h"            // V2.0 ubo EPS module

/*****************************************************************************
* This class represents the ubo satellite platform.
******************************************************************************/
class Cube {
  public:
    Cube();
    ~Cube();
    uint8_t initialise(uint32_t rate = 115200, uint8_t timeout = 60);
//    void pluginPayload(Payload* pPayload);
    void sleep(int periods);
    void heartbeat();
    void checkFaults();
    float solarCurrent();
    float solarVoltage();
    float busCurrent();
    float busVoltage();
    void reset();
    Telemetry telemetry; // Instance of the telemetry class
	Camera camera = Camera(&Serial2); // Instance of the camera class, passing a h/w serial object
	Radio radio; // Instance of the radio class
    EPS eps;
//    Payload** pPayloads = new Payload*[10]; // max 10 payloads
	
  private:
//    void busSleep();
//    int payloadCount = 0;
};

#endif


