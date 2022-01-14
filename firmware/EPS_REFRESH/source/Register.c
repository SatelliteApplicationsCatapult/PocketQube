/*
 * Register.c
 *
 *  Created on: 12 Sep 2019
 *      Author: Ken.Diep
 */

//This code will establish registers and structures


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

EPS_WHO_AM_I.raw = 0xAA; //170 decimal
EPS_CONTROL.raw = 0x00; //Initialising control register to zeros


