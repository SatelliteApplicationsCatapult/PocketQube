/* ###################################################################
 **     Filename    : main.c
 **     Project     : EPS_Dev
 **     Processor   : MKL02Z32VFM4
 **     Version     : Driver 01.01
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2016-02-03, 09:09, # CodeGen: 0
 **     Abstract    :
 **         Main module.
 **         This module contains user's application code.
 **     Settings    :
 **     Contents    :
 **         No public methods
 **
 ** ###################################################################*/
/*!
 ** @file main.c
 ** @version 01.01
 ** @brief
 **         Main module.
 **         This module contains user's application code.
 */
/*!
 **  @addtogroup main_module main module documentation
 **  @{
 */
/* MODULE main */

/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "OPTO_SHDN.h"
#include "AUX_TP.h"
#include "BUS_BAT_SW2_EN.h"
#include "BUS_3V3_SW3_EN.h"
#include "BUS_3V3_SW2_EN.h"
#include "BUS_3V3_SW1_EN.h"
#include "BUS_BAT_SW1_EN.h"
#include "WD_WDI.h"
#include "RAW_BAT_ISEN_EN.h"
#include "OBC_IRQ.h"
#include "USB_SHDN.h"
#include "SOL_VSEN_EN.h"
#include "BAT_VSEN_EN.h"
#include "I2C2.h"
#include "ADC_MODULE.h"
#include "WDI_TIMER.h"
#include "WAIT1.h"
#include "KSDK1.h"
#include "GPIO_1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */

#include "config.h"
#include "COMS.h"
#include "Sensors.h"
#include "WDT.h"
#include "Registers.c"
#include <string.h> /* memset */

volatile bool DataReceivedFlg = FALSE;
volatile bool DataTransmittedFlg = FALSE;
//volatile bool EPSReceiveFlg = FALSE;
//volatile bool EPSTransmitFlg = FALSE;

#define SAMPLE_GROUP_SIZE 1U

//#define pwrStat() 1
//#define chargeStat() 1
//#define solStat() 0
//#define usbStat() 1

//ADC_MODULE_TResultData MeasuredValues[SAMPLE_GROUP_SIZE];
//LDD_ADC_TSample SampleGroup[SAMPLE_GROUP_SIZE];
//LDD_TDeviceData *ADCPtr;
//LDD_TError Error;

volatile uint32_t* regPtr; // Pointer to current register address

volatile uint8_t lenData = 0; // Length of data in I2C transmission
uint8_t inData[IN_DATA_LENGTH] = { 0 }; // I2C input buffer
uint8_t outData[OUT_DATA_LENGTH] = { 0 }; // I2C output buffer

LDD_TDeviceData *I2CPtr;

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
	/* Write your local variable definition here */

	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
    PE_low_level_init();

	COMS_I2C_INIT();
	/*** End of Processor Expert internal initialisation.                    ***/

	// PE init sets all appropriate pin modes
	for (;;) {

		// Initial population of register map
		// Fill with zeros to start
		// Why don't we memset()?

		for (int i = 0; i <= (REGISTER_LENGTH / 4); i++) {
			regPtr = (uint32_t*) (REGISTER_OFFSET + (4 * i));
			*regPtr = 0x00000000; // Correct syntax? Seems to work...
		}

		regPtr = (uint32_t*) REGISTER_OFFSET; // Reset to who am I register

/*
		EPS_SWITCHED_BUSES.fields.SW1_3V3 = 1;
		EPS_SWITCHED_BUSES.fields.SW2_3V3 = 1;
		EPS_SWITCHED_BUSES.fields.SW3_3V3 = 1;
*/

		EPS_WHO_AM_I.raw = 0xAA; // Setting value of who am I register

		EPS_VERSION.fields.MAJOR_BITS = 0x00; // Setting the major firmware version
		EPS_VERSION.fields.MINOR_BITS = 0x02; // Setting the minor firmware version
		EPS_VERSION.fields.PATCH_BITS = 0x1A; // Setting the patch firmware version

		EPS_WATCHDOG.fields.PERIOD = 0x3C; // Setting the default timeout period to 60 seconds
		//memset(inData, 0, 6); // Emptying input buffer

		SENSORS_ADC_INIT();
		SENSORS_BATTERY_VOLTAGE_SENSE();
		SENSORS_BATTERY_VOLTAGE_SENSE();
		SENSORS_BATTERY_VOLTAGE_SENSE();
		SENSORS_BATTERY_VOLTAGE_SENSE();
		SENSORS_BATTERY_VOLTAGE_SENSE();

		while (1) {}; // Wait here... COMs are interrupt driven

		while (1) {
			//AUX_TP_NegVal(AUX_TP_DeviceData); // Toggle LED
			//WAIT1_Waitms(1000); // Wait 1 second
			if (EPS_SWITCHED_BUSES.fields.SW1_BATV == 0b1) {
				BUS_BAT_SW1_EN_SetVal(BUS_BAT_SW1_EN_DeviceData);
			} else {
				BUS_BAT_SW1_EN_ClrVal(BUS_BAT_SW1_EN_DeviceData);
			}

			if (EPS_SWITCHED_BUSES.fields.SW2_BATV == 0b1) {
				BUS_BAT_SW2_EN_SetVal(BUS_BAT_SW2_EN_DeviceData);
			} else {
				BUS_BAT_SW2_EN_ClrVal(BUS_BAT_SW2_EN_DeviceData);
			}

			if (EPS_SWITCHED_BUSES.fields.SW1_3V3 == 0b1) {
				BUS_3V3_SW1_EN_SetVal(BUS_3V3_SW1_EN_DeviceData);
			} else {
				BUS_3V3_SW1_EN_ClrVal(BUS_3V3_SW1_EN_DeviceData);
			}

			if (EPS_SWITCHED_BUSES.fields.SW2_3V3 == 0b1) {
				BUS_3V3_SW2_EN_SetVal(BUS_3V3_SW2_EN_DeviceData);
			} else {
				BUS_3V3_SW2_EN_ClrVal(BUS_3V3_SW2_EN_DeviceData);
			}

			if (EPS_SWITCHED_BUSES.fields.SW3_3V3 == 0b1) {
				BUS_3V3_SW3_EN_SetVal(BUS_3V3_SW3_EN_DeviceData);
			} else {
				BUS_3V3_SW3_EN_ClrVal(BUS_3V3_SW3_EN_DeviceData);
			}
		}

//		Error = I2C2_SlaveReceiveBlock(I2CPtr, inData, 6U); // Non blocking call to initialise I2C receive buffer for 7 data byte
//
//		while (1) {
//			while (!DataReceivedFlg) { // Wait until data received
//			}
//			DataReceivedFlg = FALSE;
//			AUX_TP_NegVal(AUX_TP_DeviceData); // Enable BLFNAR
//			Error = I2C2_SlaveReceiveBlock(I2CPtr, inData, 1U);
//			//WAIT1_Waitms(20);
//			//AUX_TP_ClrVal(AUX_TP_DeviceData); // Disable BLFNAR
//		}
//
//		// EPS startup code
////		USB_SHDN_SetVal(USB_SHDN_DeviceData);
//		//USB_SHDN_SetVal(USB_SHDN_DeviceData);
////		BUS_3V3_SW1_EN_SetVal(BUS_3V3_SW1_EN_DeviceData);
////		BUS_3V3_SW2_EN_SetVal(BUS_3V3_SW2_EN_DeviceData);
////		BUS_3V3_SW3_EN_SetVal(BUS_3V3_SW3_EN_DeviceData);
//		I2CPtr = I2C2_Init(NULL);
		//BUS_3V3_SW2_EN_ClrVal(BUS_3V3_SW2_EN_DeviceData);

		//u16 readregister(u16);
		//void writeregister(u16, u16);

		//uint8_t volatile * const p_led_reg = (uint8_t *) 0x80000;

		//volatile EPS_WHO_AM_I_DATA who;
		//EPS_WHO_AM_I_DATA volatile * const WHO_AM_I = (EPS_WHO_AM_I_DATA *) 0x7C20;
		//WHO_AM_I->raw = 0xAA;
		//who = readregister(EPS_WHO_AM_I_ADDR);

		//who.raw = 0xAA; // Setting the WHO_AM_I value
		//writeregister(EPS_WHO_AM_I_ADDR, who);

		//volatile EPS_WHO_AM_I_DATA WHO_AM_I;
		//uint8_t regPtr = &WHO_AM_I;
//		EPS_WHO_AM_I.raw = 0xAA;
//		EPS_CONTROL.raw = 0x00;
//
//		//volatile EPS_VERSION_DATA EPS_VERSION;
//		EPS_VERSION.fields.MAJOR_BITS = 0x00; // Setting the major firmware version
//		EPS_VERSION.fields.MINOR_BITS = 0x00; // Setting the minor firmware version
//		EPS_VERSION.fields.PATCH_BITS = 0x01; // Setting the patch firmware version
//
//		//volatile EPS_CONTROL_DATA EPS_CONTROL;
//		EPS_CONTROL.raw = 0x00; // Initialising control register to zeros
//
//		volatile EPS_WATCHDOG_DATA wd;
//		wd.raw = 0x00; // Setting watchdog period to default
//
//		volatile EPS_STATUS_DATA stat;
//		stat.raw = 0x00; // Set all bits to zero
//		stat.fields.PWR_GOOD = pwrStat(); //Setting individual bits
//		stat.fields.CHG = chargeStat(); // (not implemented, cheating with DEFs at the moment)
//		stat.fields.SOL = solStat();
//		stat.fields.USB = usbStat();
//
//		EPS_VOLTAGE_BATTERY.fields.DATA = 0xFC0;
//		batv.raw = 0xFF00;

		/*CTL_REG_DATA reg;
		 STATUS_REG_DATA rd;
		 rd = readregister(STATUS_REG_ADDR);
		 if (rd.fields.bar_bit) {
		 reg.raw = 0xffff;        //set every bit
		 reg.fields.bar_bit = 0;  //but clear this one bit
		 writeregister(CTL_REG_ADDR, reg);
		 }
		 */

		// disable USB charging (while on test bed)
		//USB_SHDN_ClrVal(USB_SHDN_DeviceData);
		//volatile uint32_t *tmp;
		/*		while (1) {

		 //while (!EPSReceiveFlg) {
		 //}; // Wait here, let's see if we can interrupt you...
		 //EPSReceiveFlg = FALSE; // RX request, reset flag
		 //Error = I2C2_SlaveReceiveBlock(I2CPtr, inData, 5U); // Receive 5 byte of data from OBC

		 while (1) {
		 };
		 BAT_VSEN_EN_SetVal(BAT_VSEN_EN_DeviceData); // Enable divider MOSFET to allow voltage measurements
		 ADCPtr = ADC_MODULE_Init((LDD_TUserData *) NULL);
		 SampleGroup[0].ChannelIdx = 2U;
		 Error = ADC_MODULE_CreateSampleGroup(ADCPtr,
		 (LDD_ADC_TSample *) SampleGroup, SAMPLE_GROUP_SIZE);  Set created sample group
		 Error = ADC_MODULE_StartSingleMeasurement(ADCPtr);  Start continuous measurement
		 while (!ADC_MODULE_GetMeasurementCompleteStatus(ADCPtr)) {
		 };  Wait for conversion completeness
		 Error = ADC_MODULE_GetMeasuredValues(ADCPtr,
		 (LDD_TData *) MeasuredValues);
		 BAT_VSEN_EN_ClrVal(BAT_VSEN_EN_DeviceData); // Disable divider MOSFET to reduce power consumption

		 EPS_VOLTAGE_BATTERY.fields.DATA = *MeasuredValues;

		 AUX_TP_SetVal(AUX_TP_DeviceData); // Enable BLFNAR (Blinky Light For No Apparent Reason)
		 //			OBC_IRQ_SetVal(OBC_IRQ_DeviceData); // Interrupt OBC

		 Error = I2C2_SlaveReceiveBlock(I2CPtr, inData, 1U); // Receive data from OBC
		 while (!DataReceivedFlg) { // Wait until data received
		 }
		 DataReceivedFlg = FALSE;
		 //			OBC_IRQ_ClrVal(OBC_IRQ_DeviceData); // Clear OBC interrupt

		 EPS_CONTROL.raw = *inData; // Writing control register

		 switch (EPS_CONTROL.raw) {
		 case 0b10000000:
		 // Watchdog kick
		 // Receive data again, kick watchdog if correct
		 Error = I2C2_SlaveReceiveBlock(I2CPtr, inData, 1U); // Receive value from OBC
		 while (!DataReceivedFlg) { // Wait until data received
		 }
		 DataReceivedFlg = FALSE;
		 if (*inData == WD_TRIG) {
		 // Reset watchdog timer
		 WD_WDI_SetVal(WD_WDI_DeviceData);
		 WAIT1_Waitus(2); // 2us pulse to reset watchdog timer
		 WD_WDI_ClrVal(WD_WDI_DeviceData);
		 AUX_TP_ClrVal(AUX_TP_DeviceData); // Turn off BLFNAR
		 }
		 break;
		 case 0b01000000:
		 // Watchdog period
		 // Receive data again, set watchdog data
		 // TODO implement variable watchdog timeout period
		 break;
		 case 0b00100000:
		 // Slave RX
		 // Receive address to write to
		 Error = I2C2_SlaveReceiveBlock(I2CPtr, inData, 1U); // Receive address from OBC
		 while (!DataReceivedFlg) { // Wait until data received
		 }
		 DataReceivedFlg = FALSE;
		 // TODO Add register read/write check here

		 //*tmp = *(uint32_t*) (*inData + REGISTER_OFFSET); // Pointer to memory address specified by OBC

		 Error = I2C2_SlaveReceiveBlock(I2CPtr, inData, 1U); // Receive data from OBC
		 while (!DataReceivedFlg) { // Wait until data received
		 }
		 DataReceivedFlg = FALSE;
		 //*tmp = (uint32_t) *inData; // Setting the memory contents of the specified address at *tmp equal to the received value
		 break;
		 case 0b00010000:
		 // Slave TX
		 // Receive address to transmit from
		 Error = I2C2_SlaveReceiveBlock(I2CPtr, inData, 1U); // Receive address from OBC
		 while (!DataReceivedFlg) { // Wait until data received
		 }
		 DataReceivedFlg = FALSE;

		 volatile uint32_t *tmp = (uint32_t*) (*inData + REGISTER_OFFSET); // Pointer to memory address specified by OBC

		 // TODO implement continuous incremental transfer until NACK

		 uint8_t i = 1;
		 while (!nack) {
		 Error =
		 I2C2_SlaveSendBlock(I2CPtr,
		 ((uint8_t*) ((*inData + REGISTER_OFFSET)
		 >> (8 * i))), 1U);
		 while (!DataTransmittedFlg) {
		 }
		 DataTransmittedFlg = FALSE;
		 // Check nack?
		 i++;
		 }

		 outData[0] = (uint8_t) (*tmp >> 8) & 0xFF; // Two data bytes, bit shifted for I2C coms
		 outData[1] = (uint8_t) (*tmp >> 16) & 0xFF;

		 // Transmit contents of address
		 Error = I2C2_SlaveSendBlock(I2CPtr, outData, 2U);
		 while (!DataTransmittedFlg) { // Wait until data transmitted
		 }
		 DataTransmittedFlg = FALSE;
		 break;
		 default:
		 break;
		 // OBC done goofed
		 }*/

		/*if (*InpData == 0x64) {
		 BUS_3V3_SW1_EN_SetVal(BUS_3V3_SW1_EN_DeviceData);
		 BUS_3V3_SW2_EN_ClrVal(BUS_3V3_SW2_EN_DeviceData);
		 BUS_3V3_SW3_EN_ClrVal(BUS_3V3_SW3_EN_DeviceData);
		 } else if (*InpData == 0x65) {
		 BUS_3V3_SW1_EN_ClrVal(BUS_3V3_SW1_EN_DeviceData);
		 BUS_3V3_SW2_EN_SetVal(BUS_3V3_SW2_EN_DeviceData);
		 BUS_3V3_SW3_EN_ClrVal(BUS_3V3_SW3_EN_DeviceData);
		 } else if (*InpData == 0x66) {
		 BUS_3V3_SW1_EN_ClrVal(BUS_3V3_SW1_EN_DeviceData);
		 BUS_3V3_SW2_EN_ClrVal(BUS_3V3_SW2_EN_DeviceData);
		 BUS_3V3_SW3_EN_SetVal(BUS_3V3_SW3_EN_DeviceData);
		 }
		 OBC_IRQ_ClrVal(OBC_IRQ_DeviceData);
		 // Deal with data here. Master writing to slave, either to set value or read data.
		 WAIT1_Waitms(1000);
		 }*/

	}

	/*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
 ** @}
 */
/*
 ** ###################################################################
 **
 **     This file was created by Processor Expert 10.5 [05.21]
 **     for the Freescale Kinetis series of microcontrollers.
 **
 ** ###################################################################
 */
