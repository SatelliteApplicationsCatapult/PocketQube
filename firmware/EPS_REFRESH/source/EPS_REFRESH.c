/*
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    EPS_REFRESH.c
 * @brief   Application entry point.
 */


#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL02Z4.h"
#include "fsl_debug_console.h"


/* TODO: insert other include files here. */
#include "fsl_adc16.h"
#include "fsl_i2c.h"

/* TODO: insert other definitions and declarations here. */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define ADC16_EXAMPLE_BASEADDR ADC0
#define ADC16_EXAMPLE_CHANNEL_GROUP 0U
#define ADC16_USER_CHANNEL 10U //ADC0_SE9

#define EXAMPLE_I2C_SLAVE_BASEADDR I2C0
#define I2C_SLAVE_CLK_SRC I2C0_CLK_SRC
#define I2C_SLAVE_CLK_FREQ CLOCK_GetFreq(I2C0_CLK_SRC)

#define I2C_DATA_LENGTH 14U
#define I2C_MASTER_SLAVE_ADDR_7BIT 0x2A //I2C address of the EPS

// Arbitrary register address definitions

#define EPS_WHO_AM_I_ADDR 						0x14
typedef union {
	struct {
		uint8_t DATA_BITS :8;
	} fields;
	uint8_t raw;
} EPS_WHO_AM_I_DATA;
volatile EPS_WHO_AM_I_DATA EPS_WHO_AM_I; //Is extern needed?

#define EPS_CURRENT_BATTERY_TOTAL_ADDR			0x22
typedef union {
	struct {
		uint16_t PADDING :4; //top 4 bits not used
		uint16_t DATA :12;  //12-bit data register
	} fields;
	uint16_t raw;
} EPS_CURRENT_BATTERY_DATA;
volatile EPS_CURRENT_BATTERY_DATA EPS_CURRENT_BATTERY;

/*******************************************************************************
 * Variables
 ******************************************************************************/
uint8_t g_slave_buff[I2C_DATA_LENGTH];
i2c_slave_handle_t g_s_handle;
volatile bool g_SlaveCompletionFlag = false;
uint8_t inData; //Data from OBC

static void i2c_slave_callback(I2C_Type *base, i2c_slave_transfer_t *xfer, void *userData)
{
    switch (xfer->event)
    {
        /*  Address match event */
        case kI2C_SlaveAddressMatchEvent:
            xfer->data = NULL; //Gets the member called data from the struct that xfer points to
            xfer->dataSize = 0;
            break;
        /*  Transmit request */
        case kI2C_SlaveTransmitEvent:
            /*  Update information for transmit process */
            xfer->data = &g_slave_buff[2];
            xfer->dataSize = g_slave_buff[1];
            break;

        /*  Receive request */
        case kI2C_SlaveReceiveEvent:
            /*  Update information for received process */
            xfer->data = g_slave_buff;
            xfer->dataSize = I2C_DATA_LENGTH;
            break;

        /*  Transfer done */
        case kI2C_SlaveCompletionEvent:
            g_SlaveCompletionFlag = true;
            xfer->data = NULL;
            xfer->dataSize = 0;
            break;

        default:
            g_SlaveCompletionFlag = false;
            break;
    }
}

int main(void) {
  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
	BOARD_InitDebugConsole();

	EPS_WHO_AM_I.raw = 0xAA; //170 decimal

	i2c_slave_config_t slaveConfig;

	I2C_SlaveGetDefaultConfig(&slaveConfig);
	slaveConfig.addressingMode = kI2C_Address7bit;
	slaveConfig.slaveAddress = I2C_MASTER_SLAVE_ADDR_7BIT;
	slaveConfig.upperAddress = 0; //Unused

	I2C_SlaveInit(EXAMPLE_I2C_SLAVE_BASEADDR, &slaveConfig, I2C_SLAVE_CLK_FREQ);

	for (uint32_t i = 0U; i < I2C_DATA_LENGTH; i++)
	    {
	        g_slave_buff[i] = 14; //Random choice
	    }

//    /* Use hardware average to increase stability of the measurement  */
//    ADC16_SetHardwareAverage(base, kADC16_HardwareAverageCount32);
//
//	adc16_config_t adc16ConfigStruct;
//	adc16_channel_config_t adc16ChannelConfigStruct;
//
//	ADC16_GetDefaultConfig(&adc16ConfigStruct);
//
//	ADC16_Init(ADC16_EXAMPLE_BASEADDR, &adc16ConfigStruct);
//	ADC16_EnableHardwareTrigger(ADC16_EXAMPLE_BASEADDR, false); //Make sure that the software trigger is used.
//
//#if defined(FSL_FEATURE_ADC16_HAS_CALIBRATION) && FSL_FEATURE_ADC16_HAS_CALIBRATION
//	if (kStatus_Success == ADC16_DoAutoCalibration(ADC16_EXAMPLE_BASEADDR))
//	{
//		PRINTF("ADC16_DoAutoCalibration() Done.\r\n");
//	}
//	else
//	{
//		PRINTF("ADC16_DoAutoCalibration() Failed.\r\n");
//	}
//#endif /* FSL_FEATURE_ADC16_HAS_CALIBRATION */
//	PRINTF("Press any key to get user channel's ADC value ...\r\n");
//
//	adc16ChannelConfigStruct.channelNumber = ADC16_USER_CHANNEL;
//	adc16ChannelConfigStruct.enableInterruptOnConversionCompleted = false;
//
//#if defined(FSL_FEATURE_ADC16_HAS_DIFF_MODE) && FSL_FEATURE_ADC16_HAS_DIFF_MODE
//	adc16ChannelConfigStruct.enableDifferentialConversion = false;
//#endif /* FSL_FEATURE_ADC16_HAS_DIFF_MODE */
//
//	while (1)
//	{
//		GETCHAR();
//		/*
//		 When in software trigger mode, each conversion would be launched once calling the "ADC16_ChannelConfigure()"
//		 function, which works like writing a conversion command and executing it. For another channel's conversion,
//		 just to change the "channelNumber" field in channel's configuration structure, and call the
//		 "ADC16_ChannelConfigure() again.
//		 */
//		ADC16_SetChannelConfig(ADC16_EXAMPLE_BASEADDR, ADC16_EXAMPLE_CHANNEL_GROUP, &adc16ChannelConfigStruct);
//		while (0U == (kADC16_ChannelConversionDoneFlag &
//				ADC16_GetChannelStatusFlags(ADC16_EXAMPLE_BASEADDR, ADC16_EXAMPLE_CHANNEL_GROUP)))
//		{
//		}
//		ADC16_reading = ADC16_GetChannelConversionValue(ADC16_EXAMPLE_BASEADDR, ADC16_EXAMPLE_CHANNEL_GROUP);
//		PRINTF("ADC Value: %d\r\n", ADC16_reading);
//
//		//Store the raw battery current in register
//		EPS_CURRENT_BATTERY.fields.DATA = ADC16_reading;
//	}
//
//	/* Wait for the converter to be done. */
//	while (!ADC_GetChannelConversionResult(ADC_EXAMPLE_BASEADDR, ADC_EXAMPLE_CHANNEL_GROUP, &adc16ResultInfoStruct))
//	{
//	}

	memset(&g_s_handle, 0, sizeof(g_s_handle)); //Populate g_s_handle with zeros

	I2C_SlaveTransferCreateHandle(EXAMPLE_I2C_SLAVE_BASEADDR, &g_s_handle, i2c_slave_callback, NULL);

	I2C_SlaveTransferNonBlocking(EXAMPLE_I2C_SLAVE_BASEADDR, &g_s_handle,
	                             kI2C_SlaveCompletionEvent | kI2C_SlaveAddressMatchEvent);

	/*  wait for transfer completed. */
	while (!g_SlaveCompletionFlag)
	{
	}
	g_SlaveCompletionFlag = false;

	PRINTF("Slave received data :");
	for (uint32_t i = 0U; i < g_slave_buff[1]; i++)
	{
	    if (i % 8 == 0)
	    {
	        PRINTF("\r\n");
	    }
	    PRINTF("0x%2x  ", g_slave_buff[2 + i]);
	}
	PRINTF("\r\n\r\n");

	/* Wait for master receive completed.*/
	while (!g_SlaveCompletionFlag)
	{
	}
	g_SlaveCompletionFlag = false;

	return 0;
}

