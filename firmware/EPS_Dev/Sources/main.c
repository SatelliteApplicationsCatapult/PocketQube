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
#include "OBC_IRQ.h"
#include "I2C2.h"
#include "ADC_MODULE.h"
#include "WDI_TIMER.h"
#include "WAIT1.h"
#include "KSDK1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */

#include "COMS.h"
volatile bool DataReceivedFlg = FALSE;
volatile bool DataTransmittedFlg = FALSE;
uint8_t outData[2]; /* Initialization of output data buffer */
uint8_t inData[1];
uint8_t regPtr;
LDD_TError Error;
LDD_TDeviceData *I2CPtr;

#define SAMPLE_GROUP_SIZE 1U

#define u8 uint8_t
#define u16 uint16_t

#define pwrStat() 1
#define chargeStat() 1
#define solStat() 0
#define usbStat() 1

#define WD_TRIG 0x55
#define REGISTER_OFFSET 0x20000BC0

// Arbitrary register address definitions

#define EPS_WHO_AM_I_ADDR 						0x14
typedef union {
	struct {
		u8 DATA_BITS :8;
	} fields;
	u8 raw;
} EPS_WHO_AM_I_DATA;
extern volatile EPS_WHO_AM_I_DATA EPS_WHO_AM_I;

#define EPS_VERSION_ADDR						0x15
typedef union {
	struct {
		u16 MAJOR_BITS :4;
		u16 MINOR_BITS :4;
		u16 PATCH_BITS :8;
	} fields;
	u16 raw;
} EPS_VERSION_DATA;
extern volatile EPS_VERSION_DATA EPS_VERSION;

#define EPS_CONTROL_ADDR						0x17
typedef union {
	struct {
		u8 WD_WRITE_BIT :1;
		u8 WD_LONG_BIT :1;
		u8 SLAVE_RX :1;
		u8 SLAVE_TX :1;
		u8 PADDING :4;
	} fields;
	u8 raw;
} EPS_CONTROL_DATA;
extern volatile EPS_CONTROL_DATA EPS_CONTROL;

#define EPS_WATCHDOG_ADDR						0x18
typedef union {
	struct {
		u8 DATA_BITS :8;
	} fields;
	u8 raw;
} EPS_WATCHDOG_DATA;

#define EPS_STATUS_ADDR							0x19
typedef union {
	struct {
		u8 PWR_GOOD :1;
		u8 CHG :1;
		u8 SOL :1;
		u8 USB :1;
		u8 SWTCH_FLT :1;
		u8 SNS_FLT :1;
		u8 MCU_FLT :1;
		u8 DATA_VALID :1;
	} fields;
	u8 raw;
} EPS_STATUS_DATA;

#define EPS_OPERATIONAL_MODE_ADDR				0x1A
typedef union {
	struct {
		u8 RESET :1;
		u8 LOW_PWR_1 :1;
		u8 LOW_PWR_2 :1;
		u8 LOW_PWR_3 :1;
		u8 MODE_1 :1;
		u8 MODE_2 :1;
		u8 PADDING :2;
	} fields;
	u8 raw;
} EPS_OPERATIONAL_MODE_DATA;

#define EPS_SWITCHED_BUSES_ADDR					0x1B
typedef union {
	struct {
		u8 SW1_3V3 :1;
		u8 SW2_3V3 :1;
		u8 SW3_3V3 :1;
		u8 SW1_BATV :1;
		u8 SW2_BATV :1;
		u8 USBV :1;
		u8 PADDING :2;
	} fields;
	u8 raw;
} EPS_SWITCHED_BUSES_DATA;
extern volatile EPS_SWITCHED_BUSES_DATA EPS_SWITCHED_BUSES;

#define EPS_VOLTAGE_BATTERY_ADDR				0x1C
typedef union {
	struct {
		u16 PADDING :4; //top 4 bits not used
		u16 DATA :12;  //12-bit data register
	} fields;
	u16 raw;
} EPS_VOLTAGE_BATTERY_DATA;
extern volatile EPS_VOLTAGE_BATTERY_DATA EPS_VOLTAGE_BATTERY;

#define EPS_VOLTAGE_MPPT_ADDR					0x1E
typedef union {
	struct {
		u16 PADDING :4; //top 4 bits not used
		u16 DATA :12;  //12-bit data register
	} fields;
	u16 raw;
} EPS_VOLTAGE_MPPT_DATA;

#define EPS_CURRENT_MPPT_ADDR					0x20
typedef union {
	struct {
		u16 PADDING :4; //top 4 bits not used
		u16 DATA :12;  //12-bit data register
	} fields;
	u16 raw;
} EPS_CURRENT_MPPT_DATA;

#define EPS_CURRENT_BATTERY_TOTAL_ADDR			0x22
typedef union {
	struct {
		u16 PADDING :4; //top 4 bits not used
		u16 DATA :12;  //12-bit data register
	} fields;
	u16 raw;
} EPS_CURRENT_BATTERY_DATA;

#define EPS_CURRENT_BATTERY_SWITCHED_ADDR		0x24
typedef union {
	struct {
		u16 PADDING :4; //top 4 bits not used
		u16 DATA :12;  //12-bit data register
	} fields;
	u16 raw;
} EPS_CURRENT_BATTERY_SWITCHED_DATA;

#define EPS_CURRENT_3V3_SYSTEM_ADDR				0x26
typedef union {
	struct {
		u16 PADDING :4; //top 4 bits not used
		u16 DATA :12;  //12-bit data register
	} fields;
	u16 raw;
} EPS_CURRENT_3V3_SYSTEM_DATA;

#define EPS_CURRENT_3V3_SWITCHED_ADDR			0x28
typedef union {
	struct {
		u16 PADDING :4; //top 4 bits not used
		u16 DATA :12;  //12-bit data register
	} fields;
	u16 raw;
} EPS_CURRENT_3V3_SWITCHED_DATA;

ADC_MODULE_TResultData MeasuredValues[SAMPLE_GROUP_SIZE];
LDD_ADC_TSample SampleGroup[SAMPLE_GROUP_SIZE];
LDD_TDeviceData *ADCPtr;
LDD_TError Error;

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
	/* Write your local variable definition here */

	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialisation.                    ***/

	for (;;) {
		// EPS startup code
		USB_SHDN_SetVal(USB_SHDN_DeviceData);
		//USB_SHDN_SetVal(USB_SHDN_DeviceData);
		BUS_3V3_SW1_EN_SetVal(BUS_3V3_SW1_EN_DeviceData);
		BUS_3V3_SW2_EN_SetVal(BUS_3V3_SW2_EN_DeviceData);
		BUS_3V3_SW3_EN_SetVal(BUS_3V3_SW3_EN_DeviceData);
		I2CPtr = I2C2_Init(NULL);
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
		EPS_WHO_AM_I.raw = 0xAA;
		EPS_CONTROL.raw = 0x00;

		//volatile EPS_VERSION_DATA EPS_VERSION;
		EPS_VERSION.fields.MAJOR_BITS = 0x00; // Setting the major firmware version
		EPS_VERSION.fields.MINOR_BITS = 0x00; // Setting the minor firmware version
		EPS_VERSION.fields.PATCH_BITS = 0x01; // Setting the patch firmware version

		//volatile EPS_CONTROL_DATA EPS_CONTROL;
		EPS_CONTROL.raw = 0x00; // Initialising control register to zeros

		volatile EPS_WATCHDOG_DATA wd;
		wd.raw = 0x00; // Setting watchdog period to default

		volatile EPS_STATUS_DATA stat;
		stat.raw = 0x00; // Set all bits to zero
		stat.fields.PWR_GOOD = pwrStat(); //Setting individual bits
		stat.fields.CHG = chargeStat(); // (not implemented, cheating with DEFs at the moment)
		stat.fields.SOL = solStat();
		stat.fields.USB = usbStat();

		EPS_VOLTAGE_BATTERY.fields.DATA = 0xFC0;
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
		while (1) {

			BAT_VSEN_EN_SetVal(BAT_VSEN_EN_DeviceData); // Enable divider MOSFET to allow voltage measurements
			ADCPtr = ADC_MODULE_Init((LDD_TUserData *) NULL);
			SampleGroup[0].ChannelIdx = 2U;
			Error = ADC_MODULE_CreateSampleGroup(ADCPtr,
					(LDD_ADC_TSample *) SampleGroup, SAMPLE_GROUP_SIZE); /* Set created sample group */
			Error = ADC_MODULE_StartSingleMeasurement(ADCPtr); /* Start continuous measurement */
			while (!ADC_MODULE_GetMeasurementCompleteStatus(ADCPtr)) {
			}; /* Wait for conversion completeness */
			Error = ADC_MODULE_GetMeasuredValues(ADCPtr,
					(LDD_TData *) MeasuredValues);
			BAT_VSEN_EN_ClrVal(BAT_VSEN_EN_DeviceData); // Disable divider MOSFET to reduce power consumption

			EPS_VOLTAGE_BATTERY.fields.DATA = *MeasuredValues;

			AUX_TP_SetVal(AUX_TP_DeviceData); // Enable BLFNAR (Blinky Light For No Apparent Reason)
			OBC_IRQ_SetVal(OBC_IRQ_DeviceData); // Interrupt OBC

			Error = I2C2_SlaveReceiveBlock(I2CPtr, inData, 1U); // Receive data from OBC
			while (!DataReceivedFlg) { // Wait until data received
			}
			DataReceivedFlg = FALSE;
			OBC_IRQ_ClrVal(OBC_IRQ_DeviceData); // Clear OBC interrupt

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

//				uint8_t i = 1;
//				while (!nack) {
//					Error =
//							I2C2_SlaveSendBlock(I2CPtr,
//									((uint8_t*) ((*inData + REGISTER_OFFSET)
//											>> (8 * i))), 1U);
//					while (!DataTransmittedFlg) {
//					}
//					DataTransmittedFlg = FALSE;
//					// Check nack?
//					i++;
//				}

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
			}

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
			 // Deal with data here. Master writing to slave, either to set value or read data.*/
			WAIT1_Waitms(1000);
		}

	}

	/*** Don't write any code pass this line, or it will be deleted during code generation. ***/
	/*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
#ifdef PEX_RTOS_START
	PEX_RTOS_START(); /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
#endif
	/*** End of RTOS startup code.  ***/
	/*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
	for (;;) {
	}
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
