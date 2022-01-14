/*
 * COMS.c
 *
 *  Created on: 20 Apr 2016
 *      Author: George Addison
 */

#include "COMS.h"
#include "I2C2.h"
#include "config.h"

uint8_t COMS_I2C_INIT(void) {
	lenData = 0; // Zero received data counter
	I2CPtr = I2C2_Init(NULL); // Initialising I2C pointer
	I2C2_SlaveReceiveBlock(I2CPtr, inData, IN_DATA_LENGTH); // Setting up input buffer
}

uint8_t COMS_I2C_RX(void) {

	EnterCritical(); // Disable all interrupts

	if (lenData == 5) {
		// Enough data to fill a register?
		// Check whether current register is writable
		// (Control, watchdog, mode or switches)
		if ((inData[0] == 2) || (inData[0] == 3) || (inData[0] == 5) || (inData[0] == 6) ) {
			// Temporary register pointer
			uint32_t* tmpPtr = (uint32_t*) (REGISTER_OFFSET + (4 * inData[0]));
			// Write register contents
			*tmpPtr = (inData[1] ) | (inData[2] << 8 ) | (inData[3] << 16 ) | (inData[4] << 24 );
		}
	} else if (lenData == 1) {
		// 1 byte, set register pointer to this address
		if (inData[0] < (REGISTER_LENGTH / 4)) { // Between 0 and 15?
			// Set register pointer address only
			regPtr = (uint32_t*) (REGISTER_OFFSET + (4 * inData[0])); // Set register pointer to given address
			// All addresses can be read, so populate TX buffer immediately
			COMS_I2C_TX();
		}
	}

	for (int i = 0; i < IN_DATA_LENGTH; i++) {
		inData[i] = 0;
	}

	// reset input counter
	lenData = 0;

	I2C2_SlaveCancelReceptionBlock(I2CPtr); // Cancel reception, see if it resets the internal buffer counter...?
	I2C2_SlaveReceiveBlock(I2CPtr, inData, IN_DATA_LENGTH); // Reset I2C receive buffer (non-blocking)

	ExitCritical(); // Re-enable interrupts
}

uint8_t COMS_I2C_TX(void) {

	EnterCritical(); // Disable all interrupts

	outData[0] = (*regPtr >> (8 * 0)) & 0xFF;
	outData[1] = (*regPtr >> (8 * 1)) & 0xFF;
	outData[2] = (*regPtr >> (8 * 2)) & 0xFF;
	outData[3] = (*regPtr >> (8 * 3)) & 0xFF;

	Error = I2C2_SlaveSendBlock(I2CPtr, outData, OUT_DATA_LENGTH); // Send 4 bytes of data to TX buffer

	ExitCritical(); // Re-enable interrupts
}
