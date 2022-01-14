/*
 * COMS.h
 *
 *  Created on: 20 Apr 2016
 *      Author: George Addison
 */

#ifndef SOURCES_COMS_H_
#define SOURCES_COMS_H_

#include "PE_Types.h"
#include "PE_LDD.h"
#include "I2C2.h"
#include "Registers.c"

extern volatile uint32_t* regPtr; // Pointer to current register address
extern volatile uint8_t lenData; // Length of data in I2C transmission
extern uint8_t inData[]; // I2C input buffer
extern uint8_t outData[]; // I2C output buffer
extern LDD_TDeviceData *I2CPtr;
extern LDD_TError Error;

uint8_t COMS_I2C_INIT(void);
uint8_t COMS_I2C_RX(void);
uint8_t COMS_I2C_TX(void);

#endif /* SOURCES_COMS_H_ */
