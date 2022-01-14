/*
 * COMS.c
 *
 *  Created on: 20 Apr 2016
 *      Author: George Addison
 */

#include "COMS.h"
#include "I2C2.h"

//static COMS_TDataState ComsDeviceData;
//
//uint8_t COMS_I2C_RX(void) {
//	MyI2CPtr = I2C2_Init(NULL);
//	OBC_IRQ_SetVal(OBC_IRQ_DeviceData);
//	WAIT1_Wait100Cycles();
//	//COMS_I2C_RX();
//	Error = I2C2_SlaveReceiveBlock(MyI2CPtr, InpData, 1U); /* Receive InpData (16bytes) from I2C BUS */
//	while (!DataReceivedFlg) { /* Wait until InpData are received */
//	}
//	DataReceivedFlg = FALSE;
//	OBC_IRQ_ClrVal(OBC_IRQ_DeviceData);
//	I2C2_Deinit(NULL);
//}
//
