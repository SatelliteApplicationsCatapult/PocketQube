#include "Telemetry.h"

// Constructor configures IMU settings
Telemetry::Telemetry() {
    si1145.begin();
	lsm9ds1.settings.device.commInterface = IMU_MODE_I2C; 	// Set to I2C mode
	lsm9ds1.settings.device.mAddress = ADDR_IMU_M;			// Set magnetometer address
	lsm9ds1.settings.device.agAddress = ADDR_IMU_AG;		// Set accelerometer / gyroscope address
	lsm9ds1.begin();	// Apply configuration settings
};

// Destructor
Telemetry::~Telemetry() {};

double Telemetry::getTemperature(){
	byte lsb, msb;
	uint16_t val;
	double temperature;
	Wire.begin();
	Wire.beginTransmission(ADDR_TEMP);
	Wire.write(0x00);
	Wire.endTransmission();
	Wire.requestFrom(ADDR_TEMP,4);
	Wire.endTransmission();
	
	msb = Wire.read();
	lsb = Wire.read();
	val = (msb << 8) | lsb; // Concatenating bytes
	val >>= 4; // Left justified to right
	
	// Twos compliment, but negative bit in wrong place
	if (val & (1<<11)) {
		val |= 0xF800; // Set bits 11-15 to 1s to give true twos compliment
	}
	
	temperature = val / 16.0; // Converting to degrees celcius
	return temperature += TMP102_OFFSET; // Offset defined in header file
}

uint16_t Telemetry::getVisible(){
    si1145.begin();
	return si1145.readVisible(); 
}

uint16_t Telemetry::getUV(){
    si1145.begin();
	return si1145.readUV();
}

uint16_t Telemetry::getIR(){
    si1145.begin();
	return si1145.readIR();
}

float Telemetry::getAccelX(){
	lsm9ds1.readAccel();
	return lsm9ds1.calcAccel(lsm9ds1.ax);
}

float Telemetry::getAccelY(){
	lsm9ds1.readAccel();
	return lsm9ds1.calcAccel(lsm9ds1.ay);
}

float Telemetry::getAccelZ(){
	lsm9ds1.readAccel();
	return lsm9ds1.calcAccel(lsm9ds1.az);
}

float Telemetry::getMagX(){
	lsm9ds1.readMag();
	return lsm9ds1.calcMag(lsm9ds1.mx);	
}

float Telemetry::getMagY(){
	lsm9ds1.readMag();
	return lsm9ds1.calcMag(lsm9ds1.my);
}

float Telemetry::getMagZ(){
	lsm9ds1.readMag();
	return lsm9ds1.calcMag(lsm9ds1.mz);	
}

float Telemetry::getGyroX(){
	lsm9ds1.readGyro();
	return lsm9ds1.calcGyro(lsm9ds1.gx);
}

float Telemetry::getGyroY(){
	lsm9ds1.readGyro();
	return lsm9ds1.calcGyro(lsm9ds1.gy);
}

float Telemetry::getGyroZ(){
	lsm9ds1.readGyro();
	return lsm9ds1.calcGyro(lsm9ds1.gz);
}

float Telemetry::getRoll(){
	lsm9ds1.readAccel();
	return (atan2(lsm9ds1.ay, lsm9ds1.az)) * 180 / PI;
}

float Telemetry::getPitch(){
	lsm9ds1.readAccel();
	return (atan2(-lsm9ds1.ax, sqrt(lsm9ds1.ay * lsm9ds1.ay + lsm9ds1.az * lsm9ds1.az))) * 180 / PI;
}

float Telemetry::getYaw(){
	float heading;
	lsm9ds1.readMag();
	if (lsm9ds1.my == 0){
		heading = (lsm9ds1.mx < 0) ? 180.0 : 0;
	} else {
		heading = atan2(lsm9ds1.mx, lsm9ds1.my);
	}
	heading -= LOCAL_DECLINATION * PI / 180;
	if (heading > PI) {
		heading -= (2 * PI);
	} else if (heading < -PI) {
		heading += (2 * PI);
	} else if (heading < 0) {
		heading += 2 * PI;
	}
	return heading * 180 / PI;
}