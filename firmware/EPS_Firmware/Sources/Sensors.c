/*
 * Sensors.c
 *
 *  Created on: 11 Jan 2017
 *      Author: George Addison
 */

#include "Sensors.h"

void SENSORS_ADC_INIT(void) {
	ADCPtr = ADC_MODULE_Init((LDD_TUserData *)NULL);        /* Initialize the device */
}

void SENSORS_BATTERY_VOLTAGE_SENSE(void) {
	// Enable power to the divider circuit used to measure battery voltage
	BAT_VSEN_EN_SetVal(BAT_VSEN_EN_DeviceData);

	// Configure ADC measurement
	SampleGroup[0].ChannelIdx = 2U;
	Error = ADC_MODULE_CreateSampleGroup(ADCPtr, (LDD_ADC_TSample *)SampleGroup, ADC_SAMPLE_GROUP_SIZE);
	Error = ADC_MODULE_StartSingleMeasurement(ADCPtr);
	while (!ADC_MODULE_GetMeasurementCompleteStatus(ADCPtr)) {};
	Error = ADC_MODULE_GetMeasuredValues(ADCPtr, (LDD_TData *)MeasuredValues);

	// Disable divider circuit
	BAT_VSEN_EN_ClrVal(BAT_VSEN_EN_DeviceData);

	// Floating point battery voltage
	float SENSORS_BATTERY_VOLTAGE = BATTERY_VOLTAGE_DIVIDER_RATIO * REGULATED_RAIL_VOLTAGE * ((float)MeasuredValues[0] / ADC_FULL_SCALE_RESOLUTION);

	// Integer component (3V, 4V etc.)
	uint8_t SENSORS_BATTERY_VOLTS_COMPONENT = (uint8_t)SENSORS_BATTERY_VOLTAGE;

	//uint8_t SENSORS_BATTERY_MILLIVOLTS_COMPONENT = (SENSORS_BATTERY_VOLTAGE - SENSORS_BATTERY_VOLTS_COMPONENT) *
}

void SENSORS_SOLAR_MPPT_VOLTAGE_SENSE(void) {

}

void SENSORS_SOLAR_MPPT_CURRENT_SENSE(void) {

}

void SENSORS_BATTERY_BUS_CURRENT_SENSE(void) {

}

void SENSORS_BATTERY_RAW_CURRENT_SENSE(void) {

}

void SENSORS_REGULATED_SWITCHED_CURRENT_SENSE(void) {

}

void SENSORS_REGULATED_CONSTANT_CURRENT_SENSE(void) {

}
