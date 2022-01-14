#include <Arduino.h>
#include "Camera.h"

Camera::Camera(HardwareSerial *serial) {
	hwSerial = serial;
}

Camera::~Camera() {};

uint8_t Camera::init(uint32_t baud) {
	hwSerial->begin(baud); // Initialising serial
	uint16_t timeout = millis();
	while(!hwSerial) { // 3 second timeout in case serial unavailable
		if ((millis() - timeout) > 3000) {
			return 0;
		}
	};
	return 1;
}

uint8_t Camera::reset() {
	// Transmit reset command
	hwSerial->write(0x56); 
	hwSerial->write(0x00);
	hwSerial->write(0x26);
	hwSerial->write(0x00);
	clearSerial();	
	// Read camera response. First transmission is ACK, second info, third confirmation of initialisation
	for (int i = 0; i < 3; i++) {
		if (!waitSerial()) { // Wait for something to be available on the serial port
			return 0;
		}			
		if (!readSerial()) { // Read available bytes
			return 0; 
		}
	}
	//TODO Check the returned data for 'Init end', maybe camera version? 
	return 1;
}

uint8_t Camera::baudDefault(uint32_t baud) {
	uint8_t byte_1, byte_2;
	switch (baud) { // Baud selection
		case 115200 :
			byte_1 = 0x0D;
			byte_2 = 0xA6;
			break;
		case 57600 :
			byte_1 = 0x1C;
			byte_2 = 0x4C;
			break;
		case 38400 :
			byte_1 = 0x2A;
			byte_2 = 0xF2;
			break;
		case 19200 :
			byte_1 = 0x56;
			byte_2 = 0xE4;
			break;
		case 9600 :
			byte_1 = 0xAE;
			byte_2 = 0xC8;
			break;
		default :
			return 0;
	}
	// Issue default baud rate selection commands
	hwSerial->write(0x56);
	hwSerial->write(0x00);
	hwSerial->write(0x31);
	hwSerial->write(0x06);
	hwSerial->write(0x04);
	hwSerial->write(0x02);
	hwSerial->write(0x00);
	hwSerial->write(0x08);
	hwSerial->write(byte_1); // Baud value bytes
	hwSerial->write(byte_2);
	
	clearSerial();
	if (!waitSerial()) { // Wait for something to be available on the serial port
		return 0;
	}			
	if (!readSerial()) { // Read available bytes
		return 0; 
	}
	if (!reset()) { // Reset camera
		return 0;
	}
	return 1;
}

uint8_t Camera::baudTemp(uint32_t baud) {
	uint8_t byte_1, byte_2;
	switch (baud) { // Baud selection
		case 115200 :
			byte_1 = 0x0D;
			byte_2 = 0xA6;
			break;
		case 57600 :
			byte_1 = 0x1C;
			byte_2 = 0x4C;
			break;
		case 38400 :
			byte_1 = 0x2A;
			byte_2 = 0xF2;
			break;
		case 19200 :
			byte_1 = 0x56;
			byte_2 = 0xE4;
			break;
		case 9600 :
			byte_1 = 0xAE;
			byte_2 = 0xC8;
			break;
		default :
			return 0;
	}
	// Issue temporary baud rate selection commands
	hwSerial->write(0x56);
	hwSerial->write(0x00);
	hwSerial->write(0x24);
	hwSerial->write(0x03);
	hwSerial->write(0x01);
	hwSerial->write(byte_1); // Baud value bytes
	hwSerial->write(byte_2);
	
	clearSerial();
	if (!waitSerial()) { // Wait for something to be available on the serial port
		return 0;
	}			
	if (!readSerial()) { // Read available bytes
		return 0; 
	}
	return 1;
}

uint8_t Camera::setRes(uint16_t res) {
	if ((res != 640) && (res != 320)) {
		return 0;
	}
	hwSerial->write(0x56);
	hwSerial->write(0x00);
	hwSerial->write(0x31);
	hwSerial->write(0x05);
	hwSerial->write(0x04);
	hwSerial->write(0x01);
	hwSerial->write(0x00);
	hwSerial->write(0x19);
	if (res == 320) {
		hwSerial->write(0x11);
	} else {
		hwSerial->write(0x00);
	}
	
	clearSerial();
	if (!waitSerial()) { // Wait for something to be available on the serial port
		return 0;
	}			
	if (!readSerial()) { // Read available bytes
		return 0; 
	}
	reset();
	return 1;
}

uint8_t Camera::setComp(uint16_t comp) {
	// Setting compressibility. Value from 0x00 to 0xFF. Default is 0x36.
	// Camera seems to ignore this anyway.
	hwSerial->write(0x56);
	hwSerial->write(0x00);
	hwSerial->write(0x31);
	hwSerial->write(0x05);
	hwSerial->write(0x01);
	hwSerial->write(0x01);
	hwSerial->write(0x12);
	hwSerial->write(0x04);
	hwSerial->write(comp);
	clearSerial();
	if (!waitSerial()) { // Wait for something to be available on the serial port
		return 0;
	}			
	if (!readSerial()) { // Read available bytes
		return 0; 
	}
	return 1;
}

uint8_t Camera::takePic() {
	hwSerial->write(0x56);
	hwSerial->write(0x00);
	hwSerial->write(0x36);
	hwSerial->write(0x01);
	hwSerial->write(0x00);
	clearSerial();
	if (!waitSerial()) { // Wait for something to be available on the serial port
		return 0;
	}			
	if (!readSerial()) { // Read available bytes
		return 0; 
	}
	return 1;
}

uint16_t Camera::getLen() {
	hwSerial->write(0x56);
	hwSerial->write(0x00);
	hwSerial->write(0x34);
	hwSerial->write(0x01);
	hwSerial->write(0x00);
	clearSerial();
	if (!waitSerial()) { // Wait for something to be available on the serial port
		return 0;
	}			
	if (!readSerial(7)) { // Read 7 available bytes
		return 0; 
	}
	
	uint16_t timer = millis();
	while (hwSerial->available() < 2) { // Wait for bytes to be available on the serial port
		if ((millis() - timer) > 3000) { // Timeout after three seconds
			return 0;
		}
	}; 	
	uint8_t byte_1 = hwSerial->read();
	uint8_t byte_2 = hwSerial->read();
	jpglen = (byte_1 << 8) | (byte_2 & 0xFF);
	bytesRemain = jpglen;
	return 1;
}

uint16_t Camera::getPic(uint16_t bytes) {
	if (bytesRemain < bytes) { // If remaining image data is smaller than buffer
		bytes = bytesRemain;   // only return remaining data
	} else if (bytesRemain < 1) { // Return 0 if we've returned all bytes
		return 0;
	}
	
	hwSerial->write(0x56);
	hwSerial->write(0x00);
	hwSerial->write(0x32);
	hwSerial->write(0x0C);
	hwSerial->write(0x00);
	hwSerial->write(0x0A);
	hwSerial->write(0x00);
	hwSerial->write(0x00);
	hwSerial->write((jpglen - bytesRemain) >> 8); // Starting frame upper bit
	hwSerial->write((jpglen - bytesRemain) & 0xFF); // Starting frame lower bit
	hwSerial->write(0x00);
	hwSerial->write(0x00);
	hwSerial->write(bytes >> 8); // Number of bytes to transmit
	hwSerial->write(bytes & 0xFF); // Two 8-bit values concatenated
	hwSerial->write(0x00);
	hwSerial->write(0xFF);
	clearSerial();
	if (!waitSerial()) { // Wait for ACK
		return 0;
	}
	if (!readSerial(5)) { // Read 5 byte ACK
		return 0; 
	}
	if (!waitSerial()) { // Wait for data
		return 0;
	}
	uint16_t timer = millis();
	uint16_t i = 0;
	while ((millis() - timer) < 2) { // 2ms timeout, assume end of data if exceeded
		if (hwSerial->available()) { // Keep checking serial
			byteBuffer[i] = hwSerial->read(); // Add bytes to buffer if available
			i++; // Increment buffer
			timer = millis(); // reset timeout
		}
	}
	bytesRemain -= i;
	if (!waitSerial()) { // Wait for second ACK
		return 0;
	}
	if (!readSerial(5)) { // Read 5 byte ACK
		return 0; 
	}
	return bytesRemain;
}

bool Camera::readSerial(uint16_t bytes) {
	uint16_t timer = millis();
	while ((millis() - timer) < 2) { // Greater than 4ms without transmission deemed a seperate transmission
		while (hwSerial->available()) {
			hwSerial->read(); // Read camera info
			bytes -= 1;
			if (!bytes) {
				return 1;
			}
			timer = millis(); // Reset timer
		}
	}
	return 1;
}

bool Camera::waitSerial(uint16_t timeout) {
	uint16_t timer = millis();
	while (!hwSerial->available()) { // Wait for bytes to be available on the serial port
		if ((millis() - timer) > timeout) { // Timeout after three seconds
			return 0;
		}
	}; 	
	return 1;
}

void Camera::clearSerial() {
	while (hwSerial->available()) {
		hwSerial->read();
	}
}