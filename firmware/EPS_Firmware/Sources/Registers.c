/*
 * Registers.c
 *
 *  Created on: 10 Jun 2016
 *      Author: George Addison
 *      Register map definitions, accessible as C bitfields. Address in memory defined in RegisterMap.ld.
 */

#ifndef REGISTERS_H_
#define REGISTERS_H_

// Including default data types
#include "PE_Types.h"
#include "PE_LDD.h"

// Data field type shortcuts
#define u8	uint8_t
#define u16	uint16_t
#define u32	uint32_t

// Register definitions
#define WD_TRIG 		0x55
#define EPS_I2C_ADDRR 	0x2A
#define REGISTER_OFFSET 0x20000BC0
#define REGISTER_LENGTH	0x3C

// Register definitions

// Who am I register, set to known value on boot, for checking comms.
typedef union {
	struct {
		u8 DATA_BITS :8;
	} fields;
	u8 raw;
} EPS_WHO_AM_I_DATA;
extern volatile EPS_WHO_AM_I_DATA EPS_WHO_AM_I;

// EPS firmware version register. Major, minor and patch fields, for compatibility with semantic versioning.
// Full 32 bit register, 4294967295 firmware revisions should be sufficient.

typedef union {
	struct {
		u16 MAJOR_BITS :8;
		u16 MINOR_BITS :8;
		u16 PATCH_BITS :8;
	} fields;
	u32 raw;
} EPS_VERSION_DATA;
extern volatile EPS_VERSION_DATA EPS_VERSION;

//EPS control register. For handling RX / TX requests, watchdog interrupts etc.
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

// Watchdog register. Data bits must be set correctly to prevent rampant code accidentally reseting timer
// Period bits used for setting timeout period. Default 1s, max 256s
typedef union {
	struct {
		u8 DATA_BITS :8;
		u8 PERIOD :8;
	} fields;
	u16 raw;
} EPS_WATCHDOG_DATA;
extern volatile EPS_WATCHDOG_DATA EPS_WATCHDOG;

// Status register. Quick overview of operational status in a single register.
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
extern volatile EPS_STATUS_DATA EPS_STATUS;

// Mode register. For setting low power modes etc.
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
extern volatile EPS_OPERATIONAL_MODE_DATA EPS_OPERATIONAL_MODE;

// Switched buses, 3V3, BATV and usb disable.
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

// Data registers, voltage and current measurements.
// 12-bit SAR ADC, 2 bytes per value
typedef union {
	struct {
		u16 PADDING :4; //top 4 bits not used
		u16 DATA :12;  //12-bit data register
	} fields;
	u16 raw;
} EPS_VOLTAGE_BATTERY_DATA;
extern volatile EPS_VOLTAGE_BATTERY_DATA EPS_VOLTAGE_BATTERY;

typedef union {
	struct {
		u16 PADDING :4; //top 4 bits not used
		u16 DATA :12;  //12-bit data register
	} fields;
	u16 raw;
} EPS_VOLTAGE_MPPT_DATA;
extern volatile EPS_VOLTAGE_MPPT_DATA EPS_VOLTAGE_MPPT;

typedef union {
	struct {
		u16 PADDING :4; //top 4 bits not used
		u16 DATA :12;  //12-bit data register
	} fields;
	u16 raw;
} EPS_CURRENT_MPPT_DATA;
extern volatile EPS_CURRENT_MPPT_DATA EPS_CURRENT_MPPT;

typedef union {
	struct {
		u16 PADDING :4; //top 4 bits not used
		u16 DATA :12;  //12-bit data register
	} fields;
	u16 raw;
} EPS_CURRENT_BATTERY_DATA;
extern volatile EPS_CURRENT_BATTERY_DATA EPS_CURRENT_BATTERY;

typedef union {
	struct {
		u16 PADDING :4; //top 4 bits not used
		u16 DATA :12;  //12-bit data register
	} fields;
	u16 raw;
} EPS_CURRENT_BATTERY_SWITCHED_DATA;
extern volatile EPS_CURRENT_BATTERY_SWITCHED_DATA EPS_CURRENT_BATTERY_SWITCHED;

typedef union {
	struct {
		u16 PADDING :4; //top 4 bits not used
		u16 DATA :12;  //12-bit data register
	} fields;
	u16 raw;
} EPS_CURRENT_3V3_SYSTEM_DATA;
extern volatile EPS_CURRENT_3V3_SYSTEM_DATA EPS_CURRENT_3V3_SYSTEM;

typedef union {
	struct {
		u16 PADDING :4; //top 4 bits not used
		u16 DATA :12;  //12-bit data register
	} fields;
	u16 raw;
} EPS_CURRENT_3V3_SWITCHED_DATA;
extern volatile EPS_CURRENT_3V3_SWITCHED_DATA EPS_CURRENT_3V3_SWITCHED;

#endif
