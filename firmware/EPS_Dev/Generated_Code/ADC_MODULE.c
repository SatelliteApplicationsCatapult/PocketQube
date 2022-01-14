/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : ADC_MODULE.c
**     Project     : EPS_Dev
**     Processor   : MKL02Z32VFM4
**     Component   : ADC_LDD
**     Version     : Component 01.183, Driver 01.08, CPU db: 3.00.000
**     Repository  : Kinetis
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-06-07, 15:36, # CodeGen: 42
**     Abstract    :
**         This device "ADC_LDD" implements an A/D converter,
**         its control methods and interrupt/event handling procedure.
**     Settings    :
**          Component name                                 : ADC_MODULE
**          A/D converter                                  : ADC0
**          Discontinuous mode                             : no
**          Interrupt service/event                        : Disabled
**          DMA                                            : Disabled
**          A/D channel list                               : 7
**            Channel 0                                    : 
**              Channel mode                               : Single Ended
**                Input                                    : 
**                  A/D channel (pin)                      : ADC0_SE6/PTB0/IRQ_5/EXTRG_IN/SPI0_SCK
**                  A/D channel (pin) signal               : ADC_3V3_BUS_ISEN
**            Channel 1                                    : 
**              Channel mode                               : Single Ended
**                Input                                    : 
**                  A/D channel (pin)                      : ADC0_SE11/PTB8
**                  A/D channel (pin) signal               : ADC_BATV_BUS_ISEN
**            Channel 2                                    : 
**              Channel mode                               : Single Ended
**                Input                                    : 
**                  A/D channel (pin)                      : ADC0_SE1/CMP0_IN1/PTB5/IRQ_12/NMI_b
**                  A/D channel (pin) signal               : ADC_BAT_VSEN
**            Channel 3                                    : 
**              Channel mode                               : Single Ended
**                Input                                    : 
**                  A/D channel (pin)                      : ADC0_SE9/PTB10/TPM0_CH1
**                  A/D channel (pin) signal               : ADC_SOL_ISEN
**            Channel 4                                    : 
**              Channel mode                               : Single Ended
**                Input                                    : 
**                  A/D channel (pin)                      : ADC0_SE0/CMP0_IN0/PTA12/IRQ_13/LPTMR0_ALT2/TPM1_CH0/TPM_CLKIN0
**                  A/D channel (pin) signal               : ADC_SOL_VSEN
**            Channel 5                                    : 
**              Channel mode                               : Single Ended
**                Input                                    : 
**                  A/D channel (pin)                      : ADC0_SE10/PTB9
**                  A/D channel (pin) signal               : ADC_BAT_RAW_ISEN
**            Channel 6                                    : 
**              Channel mode                               : Single Ended
**                Input                                    : 
**                  A/D channel (pin)                      : ADC0_SE7/PTA7/IRQ_4/SPI0_MISO/SPI0_MOSI
**                  A/D channel (pin) signal               : ADC_BUS_3V3_ISEN
**          Static sample groups                           : Disabled
**          Max. samples                                   : 8
**          A/D resolution                                 : 12 bits
**          Low-power mode                                 : Disabled
**          High-speed conversion mode                     : Disabled
**          Asynchro clock output                          : Disabled
**          Sample time                                    : 4 clock periods
**          Number of conversions                          : 1
**          Conversion time                                : 1.907349 µs
**          ADC clock                                      : 10.485 MHz (95.367 ns)
**          Single conversion time - Single-ended          : 2.622 us
**          Single conversion time - Differential          : Differential mode not supported
**          Additional conversion time - Single-ended      : 1.907 us
**          Additional conversion time - Differential      : Differential mode not supported
**          Result type                                    : unsigned 16 bits, right justified
**          Trigger                                        : Disabled
**          Voltage reference                              : 
**            High voltage reference                       : 
**              Volt. ref. pin                             : VREFH
**              Volt. ref pin signal                       : VREFH
**            Low voltage reference                        : 
**              Volt. ref. pin                             : VREFL
**              Volt. ref pin signal                       : VREFL
**          Initialization                                 : 
**            Enabled in init. code                        : yes
**            Auto initialization                          : yes
**            Event mask                                   : 
**              OnMeasurementComplete                      : Disabled
**              OnError                                    : Disabled
**          CPU clock/configuration selection              : 
**            Clock configuration 0                        : This component enabled
**            Clock configuration 1                        : This component disabled
**            Clock configuration 2                        : This component disabled
**            Clock configuration 3                        : This component disabled
**            Clock configuration 4                        : This component disabled
**            Clock configuration 5                        : This component disabled
**            Clock configuration 6                        : This component disabled
**            Clock configuration 7                        : This component disabled
**     Contents    :
**         Init                         - LDD_TDeviceData* ADC_MODULE_Init(LDD_TUserData *UserDataPtr);
**         Enable                       - LDD_TError ADC_MODULE_Enable(LDD_TDeviceData *DeviceDataPtr);
**         Disable                      - LDD_TError ADC_MODULE_Disable(LDD_TDeviceData *DeviceDataPtr);
**         StartSingleMeasurement       - LDD_TError ADC_MODULE_StartSingleMeasurement(LDD_TDeviceData *DeviceDataPtr);
**         GetMeasuredValues            - LDD_TError ADC_MODULE_GetMeasuredValues(LDD_TDeviceData *DeviceDataPtr,...
**         CreateSampleGroup            - LDD_TError ADC_MODULE_CreateSampleGroup(LDD_TDeviceData *DeviceDataPtr,...
**         GetMeasurementCompleteStatus - bool ADC_MODULE_GetMeasurementCompleteStatus(LDD_TDeviceData *DeviceDataPtr);
**
**     Copyright : 1997 - 2015 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file ADC_MODULE.c
** @version 01.08
** @brief
**         This device "ADC_LDD" implements an A/D converter,
**         its control methods and interrupt/event handling procedure.
*/         
/*!
**  @addtogroup ADC_MODULE_module ADC_MODULE module documentation
**  @{
*/         

/* MODULE ADC_MODULE. */

#include "ADC_MODULE.h"
/* {Default RTOS Adapter} No RTOS includes */

#ifdef __cplusplus
extern "C" { 
#endif

#define ADC_MODULE_AVAILABLE_CHANNEL0_31_PIN_MASK (LDD_ADC_CHANNEL_0_PIN | LDD_ADC_CHANNEL_1_PIN | LDD_ADC_CHANNEL_2_PIN | LDD_ADC_CHANNEL_3_PIN | LDD_ADC_CHANNEL_4_PIN | LDD_ADC_CHANNEL_5_PIN | LDD_ADC_CHANNEL_6_PIN) /*!< Mask of all allocated channel pins from 0 to 31 */
#define ADC_MODULE_AVAILABLE_CHANNEL32_63_PIN_MASK 0x00U /*!< Mask of all allocated channel pins from 32 to 63 */
#define ADC_MODULE_AVAILABLE_TRIGGER_PIN_MASK 0x00U /*!< Mask of all allocated trigger pins */
#define ADC_MODULE_AVAILABLE_VOLT_REF_PIN_MASK (LDD_ADC_LOW_VOLT_REF_PIN | LDD_ADC_HIGH_VOLT_REF_PIN) /*!< Mask of all allocated voltage reference pins */

static const uint8_t ChannelToPin[] = { /* Channel to pin conversion table */
  /* ADC0_SC1A: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,COCO=0,AIEN=0,??=0,ADCH=9 */
  0x09U,                               /* Status and control register value */
  /* ADC0_SC1A: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,COCO=0,AIEN=0,??=0,ADCH=0x0E */
  0x0EU,                               /* Status and control register value */
  /* ADC0_SC1A: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,COCO=0,AIEN=0,??=0,ADCH=1 */
  0x01U,                               /* Status and control register value */
  /* ADC0_SC1A: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,COCO=0,AIEN=0,??=0,ADCH=0x0C */
  0x0CU,                               /* Status and control register value */
  /* ADC0_SC1A: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,COCO=0,AIEN=0,??=0,ADCH=0 */
  0x00U,                               /* Status and control register value */
  /* ADC0_SC1A: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,COCO=0,AIEN=0,??=0,ADCH=0x0D */
  0x0DU,                               /* Status and control register value */
  /* ADC0_SC1A: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,COCO=0,AIEN=0,??=0,ADCH=0x0A */
  0x0AU                                /* Status and control register value */
};

typedef struct {
  uint8_t SampleCount;                 /* Number of samples in the last selected/created sample group */
  bool EnUser;                         /* Enable/Disable device */
  uint8_t FirstSample;                 /* First sample of group store */
  LDD_TUserData *UserData;             /* RTOS device data structure */
} ADC_MODULE_TDeviceData;              /* Device data structure type */

typedef ADC_MODULE_TDeviceData* ADC_MODULE_TDeviceDataPtr ; /* Pointer to the device data structure. */

/* {Default RTOS Adapter} Static object used for simulation of dynamic driver memory allocation */
static ADC_MODULE_TDeviceData DeviceDataPrv__DEFAULT_RTOS_ALLOC;
/*
** ===================================================================
**     Method      :  ADC_MODULE_Init (component ADC_LDD)
*/
/*!
**     @brief
**         Initializes the device. Allocates memory for the device data
**         structure, allocates interrupt vectors and sets interrupt
**         priority, sets pin routing, sets timing, etc.
**         If the "Enable in init. code" is set to "yes" value then the
**         device is also enabled(see the description of the Enable()
**         method). In this case the Enable() method is not necessary
**         and needn't to be generated. 
**         This method can be called only once. Before the second call
**         of Init() the Deinit() must be called first.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer will be
**                           passed as an event or callback parameter.
**     @return
**                         - Device data structure pointer.
*/
/* ===================================================================*/
LDD_TDeviceData* ADC_MODULE_Init(LDD_TUserData *UserDataPtr)
{
  /* Allocate LDD device structure */
  ADC_MODULE_TDeviceDataPtr DeviceDataPrv;

  /* {Default RTOS Adapter} Driver memory allocation: Dynamic allocation is simulated by a pointer to the static object */
  DeviceDataPrv = &DeviceDataPrv__DEFAULT_RTOS_ALLOC;
  DeviceDataPrv->UserData = UserDataPtr; /* Store the RTOS device structure */
  DeviceDataPrv->SampleCount = 0U;     /* Initializing SampleCount for right access of some methods to SC1n registers before first conversion is done */
  DeviceDataPrv->EnUser = TRUE;        /* Enable device */
  /* SIM_SCGC6: ADC0=1 */
  SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;
  /* PORTB_PCR0: ISF=0,MUX=0 */
  PORTB_PCR0 &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));
  /* PORTB_PCR8: ISF=0,MUX=0 */
  PORTB_PCR8 &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));
  /* PORTB_PCR5: ISF=0,MUX=0 */
  PORTB_PCR5 &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));
  /* PORTB_PCR10: ISF=0,MUX=0 */
  PORTB_PCR10 &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));
  /* PORTA_PCR12: ISF=0,MUX=0 */
  PORTA_PCR12 &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));
  /* PORTB_PCR9: ISF=0,MUX=0 */
  PORTB_PCR9 &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));
  /* PORTA_PCR7: ISF=0,MUX=0 */
  PORTA_PCR7 &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));
  /* ADC0_CFG1: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,ADLPC=0,ADIV=1,ADLSMP=0,MODE=1,ADICLK=0 */
  ADC0_CFG1 = ADC_CFG1_ADIV(0x01) |
              ADC_CFG1_MODE(0x01) |
              ADC_CFG1_ADICLK(0x00);

  /* ADC0_CFG2: ADACKEN=0,ADHSC=0,ADLSTS=0 */
  ADC0_CFG2 &= (uint32_t)~(uint32_t)(
                ADC_CFG2_ADACKEN_MASK |
                ADC_CFG2_ADHSC_MASK |
                ADC_CFG2_ADLSTS(0x03)
               );
  /* ADC0_SC2: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,ADACT=0,ADTRG=0,ACFE=0,ACFGT=0,ACREN=0,DMAEN=0,REFSEL=0 */
  ADC0_SC2 = ADC_SC2_REFSEL(0x00);
  /* ADC0_SC3: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,CAL=0,CALF=1,??=0,??=0,ADCO=0,AVGE=0,AVGS=0 */
  ADC0_SC3 = (ADC_SC3_CALF_MASK | ADC_SC3_AVGS(0x00));
  /* Registration of the device structure */
  PE_LDD_RegisterDeviceStructure(PE_LDD_COMPONENT_ADC_MODULE_ID,DeviceDataPrv);
  return ((LDD_TDeviceData *)DeviceDataPrv); /* Return pointer to the data data structure */
}

/*
** ===================================================================
**     Method      :  ADC_MODULE_Enable (component ADC_LDD)
*/
/*!
**     @brief
**         Enables ADC device. If possible, this method switches on A/D
**         converter device, voltage reference, etc. This method is
**         intended to be used together with [Disable()] method to
**         temporary switch On/Off the device after the device is
**         initialized. This method is required if the [Enabled in init.
**         code] property is set to "no" value.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The device doesn't work in the
**                           active clock configuration
*/
/* ===================================================================*/
LDD_TError ADC_MODULE_Enable(LDD_TDeviceData *DeviceDataPtr)
{
  ((ADC_MODULE_TDeviceDataPtr)DeviceDataPtr)->EnUser = TRUE; /* Set the flag "device enabled" */
  return ERR_OK;                       /* If yes then set the flag "device enabled" */
}

/*
** ===================================================================
**     Method      :  ADC_MODULE_Disable (component ADC_LDD)
*/
/*!
**     @brief
**         Disables the ADC device. If possible, this method switches
**         off A/D converter device, voltage reference, etc. (for
**         example to avoid power consumption and possible interference).
**         When the device is disabled, some component methods should
**         not be called. If so, error ERR_DISABLED is reported. This
**         method is intended to be used together with [Enable()]
**         method to temporary switch On/Off the device after the
**         device is initialized. This method is not required. The
**         [Deinit()] method can be used to switch off and uninstall
**         the device.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The device doesn't work in the
**                           active clock configuration
*/
/* ===================================================================*/
LDD_TError ADC_MODULE_Disable(LDD_TDeviceData *DeviceDataPtr)
{
  ((ADC_MODULE_TDeviceDataPtr)DeviceDataPtr)->EnUser = FALSE; /* Set the flag "device disabled" */
  ADC_PDD_SetConversionTriggerType(ADC0_BASE_PTR, ADC_PDD_SW_TRIGGER); /* Select SW triggering */
  ADC_PDD_WriteStatusControl1Reg(ADC0_BASE_PTR, 0U, 0x1FU); /* Disable device */
  return ERR_OK;                       /* If yes then set the flag "device enabled" */
}

/*
** ===================================================================
**     Method      :  ADC_MODULE_StartSingleMeasurement (component ADC_LDD)
*/
/*!
**     @brief
**         This method starts one measurement of the selected group of
**         samples and exits immediately. This is ADC SW trigger method.
**         The group of samples for measurement is specified by
**         preceding call to [SelectSampleGroup()] or
**         [CreateSampleGroup] method. 
**         DMA disabled: The [OnMeasurementComplete() ] event is
**         invoked after the measurement is done and if the event is
**         enabled. Results of the measurement can be read by the
**         [GetMeasuredValues()] method. 
**         DMA enabled: DMA request from configured ADC is enabled
**         automatically. The [OnMeasurementComplete() ] event is
**         invoked after the requested number of results are
**         transferred to destination buffer by DMA and if the event is
**         enabled. [GetMeasuredValues()] method is not available if
**         DMA mode is enabled. If the DMA transfer was completed
**         before and DMA is not recofingured, DMA error can occur. See
**         also [SetBuffer()] method. 
**         The state of the measurement can be also polled by the
**         [GetMeasurementCompleteStatus()] method. The [Discontinuous
**         mode] doesn't support this method.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The device doesn't work in the
**                           active clock configuration
**                           ERR_DISABLED - Component is disabled
**                           ERR_BUSY - A measurement is in progress 
*/
/* ===================================================================*/
LDD_TError ADC_MODULE_StartSingleMeasurement(LDD_TDeviceData *DeviceDataPtr)
{
  /* Device state test - this test can be disabled by setting the "Ignore enable test"
     property to the "yes" value in the "Configuration inspector" */
  if (!((ADC_MODULE_TDeviceDataPtr)DeviceDataPtr)->EnUser) { /* Is the device disabled by user? */
    return ERR_DISABLED;               /* If yes then error */
  }
  if (ADC_PDD_GetConversionActiveFlag(ADC0_BASE_PTR) != 0U) { /* Last measurement still pending? */
    return ERR_BUSY;                   /* Yes, return ERR_BUSY */
  }
  ADC_PDD_SetContinuousMode(ADC0_BASE_PTR, ADC_PDD_ONE_CONVERSION); /* Set one conversion mode */
  ADC_PDD_SetConversionTriggerType(ADC0_BASE_PTR, ADC_PDD_SW_TRIGGER); /* Select SW triggering */
  ADC_PDD_WriteStatusControl1Reg(ADC0_BASE_PTR, 0U, ((ADC_MODULE_TDeviceDataPtr)DeviceDataPtr)->FirstSample); /* Set sample 0 and start conversion */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  ADC_MODULE_CreateSampleGroup (component ADC_LDD)
*/
/*!
**     @brief
**         This method prepares HW for next measurement according to
**         array of samples defined during run-time. The array of
**         samples should be prepared prior to calling this method.
**         Pointer to the array is passed into this method in parameter
**         SampleGroupPtr. The number of samples is defined by
**         parameter SampleCount. Once any group is prepared, the
**         measurement can be started multiple times. Note: This method
**         works only with the sample groups defined during run-time.
**         For design-time defined groups use [SelectSampleGroup()]
**         method.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         SampleGroupPtr  - Pointer to the
**                           sample definition array. This array can be
**                           released as soon as the method ends.
**     @param
**         SampleCount     - Number of items in the
**                           sample definition array. Must be less than
**                           or equal to
**                           ComponentName_MAX_HW_SAMPLE_COUNT.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The device doesn't work in the
**                           active clock configuration
**                           ERR_DISABLED - Component is disabled
**                           ERR_PARAM_INDEX - Channel index in
**                           SampleGroup structure is out of range
**                           ERR_PARAM_SAMPLE_COUNT - SampleCount
**                           variable value is out of range
**                           ERR_BUSY - Measurement is in progress 
*/
/* ===================================================================*/
LDD_TError ADC_MODULE_CreateSampleGroup(LDD_TDeviceData *DeviceDataPtr, LDD_ADC_TSample *SampleGroupPtr, uint8_t SampleCount)
{
  ADC_MODULE_TDeviceDataPtr DeviceDataPrv = (ADC_MODULE_TDeviceDataPtr)DeviceDataPtr;

  /* Device state test - this test can be disabled by setting the "Ignore enable test"
     property to the "yes" value in the "Configuration inspector" */
  if (!((ADC_MODULE_TDeviceDataPtr)DeviceDataPtr)->EnUser) { /* Is the device disabled by user? */
    return ERR_DISABLED;               /* If yes then error */
  }
  /* Sample count test - this test can be disabled by setting the "Ignore range checking"
     property to the "yes" value in the "Configuration inspector" */
  if ((SampleCount > ADC_MODULE_MAX_HW_SAMPLE_COUNT) || (SampleCount == 0U)) { /* Is number of sample greater then supported by the HW? */
    return ERR_PARAM_SAMPLE_COUNT;     /* Yes, return ERR_PARAM_SAMPLE_COUNT */
  }
  if (ADC_PDD_GetConversionActiveFlag(ADC0_BASE_PTR) != 0U) { /* Last measurement still pending? */
    return ERR_BUSY;                   /* Yes, return ERR_BUSY */
  }
  DeviceDataPrv->SampleCount = SampleCount; /* Remember sample count */
  /* Channel index test - this test can be disabled by setting the "Ignore range checking"
     property to the "yes" value in the "Configuration inspector" */
  if (SampleGroupPtr[0].ChannelIdx >= ADC_MODULE_CHANNEL_COUNT) { /* Is channel index out of range? */
    return ERR_PARAM_INDEX;            /* Yes, return ERR_PARAM_INDEX */
  }
  DeviceDataPrv->FirstSample = ChannelToPin[SampleGroupPtr[0].ChannelIdx]; /* Remember first sample */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  ADC_MODULE_GetMeasuredValues (component ADC_LDD)
*/
/*!
**     @brief
**         This method copies results of the last measurement to the
**         user supplied buffer. Data size depends on the size of
**         measured sample group (see [SelectSampleGroup()] or
**         [CreateSampleGroup()] method). Data representation is
**         defined by the [Result type] property. Typically this method
**         is called from [OnMeasurementComplete] event to get results
**         of the last measurement. This method is not available if DMA
**         is enabled.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         BufferPtr       - Pointer to the start of the
**                           buffer for new results. Count of stored
**                           measured values equals to the count of the
**                           samples in the active sample group. It is
**                           in the user responsibility to provide
**                           buffer with appropriate size.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The device doesn't work in the
**                           active clock configuration
**                           ERR_DISABLED - Component is disabled
*/
/* ===================================================================*/
LDD_TError ADC_MODULE_GetMeasuredValues(LDD_TDeviceData *DeviceDataPtr, LDD_TData *BufferPtr)
{
  uint8_t Sample;
  ADC_MODULE_TResultData *pBuffer = (ADC_MODULE_TResultData *)BufferPtr;

  /* Device state test - this test can be disabled by setting the "Ignore enable test"
     property to the "yes" value in the "Configuration inspector" */
  if (!((ADC_MODULE_TDeviceDataPtr)DeviceDataPtr)->EnUser) { /* Is the device disabled by user? */
    return ERR_DISABLED;               /* If yes then error */
  }
  /* Copy values from result registers defined in the active sample
     group to the user supplied buffer */
  for (Sample = 0U; Sample < ((ADC_MODULE_TDeviceDataPtr)DeviceDataPtr)->SampleCount; Sample++) {
    pBuffer[Sample] =(uint16_t)(ADC_PDD_GetResultValueRaw(ADC0_BASE_PTR, Sample));
  }
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  ADC_MODULE_GetMeasurementCompleteStatus (component ADC_LDD)
*/
/*!
**     @brief
**         Returns whether the measurement is done and the results can
**         be read by the user. It can be used to poll the state of
**         measurement if [Interrupt service/event] is disabled or if
**         [OnMeasurementComplete] event is disabled by the
**         [SetEventMask()] methods.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Error code
**                           true - Measurement is done
**                           false - Measurement is in progress
*/
/* ===================================================================*/
bool ADC_MODULE_GetMeasurementCompleteStatus(LDD_TDeviceData *DeviceDataPtr)
{
  uint32_t Status;
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  Status = ADC_PDD_GetConversionCompleteFlag(ADC0_BASE_PTR, 0U); /* Get conversion complete flag from HW */
  if (Status) {
    (void)ADC_PDD_GetResultValueRaw(ADC0_BASE_PTR, 0U); /* Clear conversion complete flag */
    return (bool)(TRUE);               /* Return TRUE if measurement has been done */
  }
  return (bool)(FALSE);                /* Return FALSE if measurement has not been done */
}

/* END ADC_MODULE. */

#ifdef __cplusplus
}  /* extern "C" */
#endif

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