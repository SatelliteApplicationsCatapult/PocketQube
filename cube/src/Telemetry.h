#ifndef TELEMETRY_H
#define TELEMETRY_H

// Library includes
#include <Adafruit_Sensor.h>
#include <Adafruit_SI1145.h>
#include <SparkFunLSM9DS1.h>
#include <Config.h>

// Local constants
#define TMP102_OFFSET -1.3 		// TMP102 temperature offset
#define LOCAL_DECLINATION 1.2	// Local declination in degrees
#define LOCAL_GRAVITY 9.81		// Local force due to gravity in ms^{-2}

/*****************************************************************************
* This class encapsulates access to all sensor data of the platform.
* It is an abstraction layer (wrapper) around specific hardware implementation.
******************************************************************************/

class Telemetry {
	public:
		Telemetry();
		~Telemetry();
		double getTemperature();
		uint16_t getUV();
		uint16_t getIR();
		uint16_t getVisible();
		float getAccelX();
		float getAccelY();
		float getAccelZ();
		float getMagX();
		float getMagY();
		float getMagZ();
		float getGyroX();
		float getGyroY();
		float getGyroZ();
		float getRoll();
		float getPitch();
		float getYaw();
	private:
		Adafruit_SI1145 si1145; // SI1145 object
		LSM9DS1 lsm9ds1; 			// LSM9DS1 object
};

#endif

