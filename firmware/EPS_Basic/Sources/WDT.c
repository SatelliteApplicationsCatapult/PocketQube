/*
 * WDT.c
 *
 *  Created on: 4 Feb 2016
 *      Author: George Addison
 */

#include "WDT.h"
#include "WD_WDI.h"
#include "OBC_IRQ.h"
#include "WAIT1.h"


static WDT_TDataState deviceData;

void WD_WDT_IRQ_SET(void) {
	// Sets the WD IRQ to OBC line high, waits 1ms then brings it low
	OBC_IRQ_SetVal(&deviceData);
	WAIT1_Waitms(1);
	OBC_IRQ_ClrVal(&deviceData);
}

uint8_t WDT_I2C_RX(void) {
	AUX_TP_SetVal(&deviceData);
	//WAIT1_Waitms(20);

	uint8_t res;
	byte data = 0;
	res = I2C2_SlaveReceiveBlock(&deviceData, &data, 1U);
	if (res != ERR_OK) {
	}
	WAIT1_Waitms(1); // Arbitrary delay as data received flags not working
	if (data != 0) {
		//toggle watchdog (or LED in this case)
		WAIT1_Waitms(20);
		AUX_TP_ClrVal(&deviceData);
	} else {
		WAIT1_Waitms(500);
		AUX_TP_ClrVal(&deviceData);
	}
	//while (!deviceData.dataReceivedFlg) {
	//} /* Wait until data is received received */
	//deviceData.dataReceivedFlg = FALSE;
	//WDT_I2C_TX();
	//AUX_TP_ClrVal(&deviceData);
	return ERR_OK;
}

uint8_t WDT_I2C_TX(void) {
	uint8_t res;
	uint8_t data = 0xF5;
	res = I2C2_SlaveSendBlock(&deviceData, &data, 1U);
}
