#ifndef Camera_h
#define Camera_h

#include <Arduino.h> 
#include <stdint.h>
/*****************************************************************************
* This class provides access to the functions of the VC0706 camera module.
******************************************************************************/

class Camera {
  public:
		Camera(HardwareSerial *serial);
		~Camera();
		uint8_t init(uint32_t baud = 115200);
		uint8_t reset();
		uint8_t baudDefault(uint32_t baud = 115200);
		uint8_t baudTemp(uint32_t baud = 115200);
		uint8_t setRes(uint16_t res = 640);
		uint8_t setComp(uint16_t comp = 0x36);
		uint8_t takePic();
		uint16_t getLen();
		uint16_t getPic(uint16_t bytes = 512);
		uint16_t jpglen, bytesRemain;
		uint8_t byteBuffer[4096];
	private:
		HardwareSerial *hwSerial;
		bool readSerial(uint16_t bytes = 65535);
		bool waitSerial(uint16_t timeout = 3000);
		void clearSerial();

};

#endif
