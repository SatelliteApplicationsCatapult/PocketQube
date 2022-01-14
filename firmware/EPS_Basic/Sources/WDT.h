/*
 * WDT.h
 *
 *  Created on: 4 Feb 2016
 *      Author: George Addison
 */

#ifndef SOURCES_WDT_H_
#define SOURCES_WDT_H_

#include "PE_Types.h"
#include "PE_LDD.h"

typedef struct {
	volatile bool dataReceivedFlg; /* Set TRUE by IRQ on I2C data receipt */
	volatile bool dataTransmittedFlg; /* Set TRUE on data transmission */
	LDD_TDeviceData *handle; /* pointer to the device handle */
} WDT_TDataState;

void WD_WDT_IRQ_SET(void);

uint8_t WDT_I2C_RX(void);
uint8_t WDT_I2C_TX(void);

#endif /* SOURCES_WDT_H_ */