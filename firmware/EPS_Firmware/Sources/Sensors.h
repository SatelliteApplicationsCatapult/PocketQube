/*
 * Sensors.h
 *
 *  Created on: 11 Jan 2017
 *      Author: George Addison
 */

#ifndef SOURCES_SENSORS_H_
#define SOURCES_SENSORS_H_

#include "config.h"
#include "ADC_MODULE.h"
#include "SOL_VSEN_EN.h"
#include "BAT_VSEN_EN.h"
#include "RAW_BAT_ISEN_EN.h"


ADC_MODULE_TResultData MeasuredValues[ADC_SAMPLE_GROUP_SIZE];
LDD_ADC_TSample SampleGroup[ADC_SAMPLE_GROUP_SIZE];
LDD_TDeviceData *ADCPtr;
LDD_TError Error;

void SENSORS_ADC_INIT(void);
void SENSORS_BATTERY_VOLTAGE_SENSE(void);
void SENSORS_SOLAR_MPPT_VOLTAGE_SENSE(void);
void SENSORS_SOLAR_MPPT_CURRENT_SENSE(void);
void SENSORS_BATTERY_BUS_CURRENT_SENSE(void);
void SENSORS_BATTERY_RAW_CURRENT_SENSE(void);
void SENSORS_REGULATED_SWITCHED_CURRENT_SENSE(void);
void SENSORS_REGULATED_CONSTANT_CURRENT_SENSE(void);

#endif /* SOURCES_SENSORS_H_ */
