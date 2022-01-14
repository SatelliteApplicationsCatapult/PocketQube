#include "Cube.h"

//
// PUBLIC METHODS - TO OPERATE PLATFORM
//

Cube::Cube() {};
Cube::~Cube() {};

// 0 is no coms, 1 is serial, 2 is radio and 3 is radio and serial
// rate is the baud rate, if serial is used or data rate if radio is used
// timeout is serial only, in seconds. Zero is an infinite timeout
uint8_t Cube::initialise(uint32_t rate, uint8_t timeout) {
	Serial.begin(rate);
	uint32_t timer = millis();
	while (!Serial) {
		if ((millis() - timer) > (1000 * timeout)) {
			return 0;
		}
	};
  	Serial.println("Welcome to ubo, initialisation sequence has completed.");
	return 1;
}

void Cube::checkFaults() {
  //Reads the bus current and voltage,
  //then checks for fault conditions and can reset.
  // int rawBusCurrent = analogRead(IBUS_PIN);
  // int rawBusVoltage = analogRead(VBUS_PIN);
  // float busCurrent = rawBusCurrent * IBUS_SCALE + IBUS_OFFSET;
  // float busVoltage = rawBusVoltage * VBUS_SCALE + VBUS_OFFSET;
  // if (busCurrent > IBUS_LIMIT) {
    //Let's hope a reset solves it!
    // reset();
  // }
}


//
// PUBLIC METHODS - TO OPERATE PAYLOAD
//
/*
void Cube::pluginPayload(Payload* pPayload) {
  if (payloadCount > 9 )
  {
    // TODO complain
    return;
  }
  pPayloads[payloadCount] = pPayload;
  payloadCount++;
}
*/
//
// PRIVATE METHODS
//
/*
void Cube::busSleep() {
  heartbeat();
  LowPower.powerDown(SLEEP_1S, ADC_OFF, BOD_OFF);
}
*/
