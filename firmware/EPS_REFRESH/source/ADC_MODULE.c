#include "ADC_MODULE.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define ADC16_EXAMPLE_BASEADDR ADC0
#define ADC16_EXAMPLE_CHANNEL_GROUP 0U
#define ADC16_USER_CHANNEL 9U //ADC0_SE9

/*******************************************************************************
 * Code
 ******************************************************************************/
//typedef struct {
//  uint8_t SampleCount;                 /* Number of samples in the last selected/created sample group */
//  bool EnUser;                         /* Enable/Disable device */
//  uint8_t FirstSample;                 /* First sample of group store */
//  LDD_TUserData *UserData;             /* RTOS device data structure */
//} ADC_MODULE_TDeviceData;              /* Device data structure type */
//
//typedef ADC_MODULE_TDeviceData* ADC_MODULE_TDeviceDataPtr ; /* Pointer to the device data structure. */

adc16_config_t adc16ConfigStruct;
adc16_channel_config_t adc16ChannelConfigStruct;

//Calibration.

if (ADC16_DoAutoCalibration(ADC_EXAMPLE_BASEADDR)) {
	PRINTF("ADC_DoSelfCalibration() done.\r\n");
}
else {
	PRINTF("ADC_DoSelfCalibration() done.\r\n");
}

ADC16_GetDefaultConfig(&adc16ConfigStruct);

//Configure the converter.
adc16ConfigStruct.clockMode = kADC_ClockSynchronousMode;
adc16ConfigStruct.clockDividerNumber = 0;
adc16ConfigStruct.resolution = kADC_Resolution12bit;
adc16ConfigStruct.enableBypassCalibration = false;
adc16ConfigStruct.sampleTimeNumber = 0U;

ADC16_Init(ADC16_EXAMPLE_BASEADDR, &adc16ConfigStruct);
ADC16_EnableHardwareTrigger(ADC16_EXAMPLE_BASEADDR, false); //Make sure that the software trigger is used.

#if defined(FSL_FEATURE_ADC16_HAS_CALIBRATION) && FSL_FEATURE_ADC16_HAS_CALIBRATION
    if (kStatus_Success == ADC16_DoAutoCalibration(ADC16_EXAMPLE_BASEADDR))
    {
        PRINTF("ADC16_DoAutoCalibration() Done.\r\n");
    }
    else
    {
        PRINTF("ADC16_DoAutoCalibration() Failed.\r\n");
    }
#endif /* FSL_FEATURE_ADC16_HAS_CALIBRATION */
    PRINTF("Press any key to get user channel's ADC value ...\r\n");

adc16ChannelConfigStruct.channelNumber = ADC16_USER_CHANNEL;
adc16ChannelConfigStruct.enableInterruptOnConversionCompleted = false;

#if defined(FSL_FEATURE_ADC16_HAS_DIFF_MODE) && FSL_FEATURE_ADC16_HAS_DIFF_MODE
    adc16ChannelConfigStruct.enableDifferentialConversion = false;
#endif /* FSL_FEATURE_ADC16_HAS_DIFF_MODE */

while (1)
	{
		GETCHAR();
		/*
		 When in software trigger mode, each conversion would be launched once calling the "ADC16_ChannelConfigure()"
		 function, which works like writing a conversion command and executing it. For another channel's conversion,
		 just to change the "channelNumber" field in channel's configuration structure, and call the
		 "ADC16_ChannelConfigure() again.
		*/
		ADC16_SetChannelConfig(ADC16_EXAMPLE_BASEADDR, ADC16_EXAMPLE_CHANNEL_GROUP, &adc16ChannelConfigStruct);
		while (0U == (kADC16_ChannelConversionDoneFlag &
					  ADC16_GetChannelStatusFlags(ADC16_EXAMPLE_BASEADDR, ADC16_EXAMPLE_CHANNEL_GROUP)))
		{
		}
		PRINTF("ADC Value: %d\r\n", ADC16_GetChannelConversionValue(ADC16_EXAMPLE_BASEADDR, ADC16_EXAMPLE_CHANNEL_GROUP));
	}

/* Wait for the converter to be done. */
while (!ADC_GetChannelConversionResult(ADC_EXAMPLE_BASEADDR, ADC_EXAMPLE_CHANNEL_GROUP, &adc16ResultInfoStruct))
{
}

