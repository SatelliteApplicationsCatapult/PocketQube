/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : I2C2.h
**     Project     : EPS_UART
**     Processor   : MKL02Z32VFM4
**     Component   : I2C_LDD
**     Version     : Component 01.016, Driver 01.07, CPU db: 3.00.000
**     Repository  : Kinetis
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-04-18, 11:43, # CodeGen: 0
**     Abstract    :
**          This component encapsulates the internal I2C communication
**          interface. The implementation of the interface is based
**          on the Philips I2C-bus specification version 2.0.
**          Interface features:
**          MASTER mode
**            - Multi master communication
**            - The combined format of communication possible
**              (see SendStop parameter in MasterSend/ReceiveBlock method)
**            - 7-bit slave addressing (10-bit addressing can be made as well)
**            - Acknowledge polling provided
**            - No wait state initiated when a slave device holds the SCL line low
**            - Holding of the SCL line low by slave device recognized as 'not available bus'
**            - Invalid start/stop condition detection provided
**          SLAVE mode
**            - 7-bit slave addressing
**            - General call address detection provided
**     Settings    :
**          Component name                                 : I2C2
**          I2C channel                                    : I2C0
**          Interrupt service                              : Enabled
**            Interrupt                                    : INT_I2C0
**            Interrupt priority                           : high priority
**          Settings                                       : 
**            Mode selection                               : SLAVE
**            MASTER mode                                  : Disabled
**            SLAVE mode                                   : Enabled
**              Address mode                               : 7-bit addressing
**              Slave address                              : 0x2A
**              General call address                       : Disabled
**              Clock stretching                           : Disabled
**                Empty character                          : 0
**              Slave baud rate control                    : Disabled
**              Wake-up                                    : Enabled
**            Pins                                         : 
**              SDA pin                                    : 
**                SDA pin                                  : PTB4/IRQ_11/I2C0_SDA/UART0_RX
**                SDA pin signal                           : I2C_SDA
**              SCL pin                                    : 
**                SCL pin                                  : PTB3/IRQ_10/I2C0_SCL/UART0_TX
**                SCL pin signal                           : I2C_SCL
**              High drive select                          : Disabled
**              Input Glitch filter                        : 5
**            Internal frequency (multiplier factor)       : 20.97152 MHz
**            Bits 0-2 of Frequency divider register       : 010
**            Bits 3-5 of Frequency divider register       : 100
**            SCL frequency                                : 93.623 kHz
**            SDA Hold                                     : 1.574 us
**            SCL start Hold                               : 5.245 us
**            SCL stop Hold                                : 5.388 us
**          Initialization                                 : 
**            Enabled in init code                         : yes
**            Auto initialization                          : yes
**            Event mask                                   : 
**              OnMasterBlockSent                          : Disabled
**              OnMasterBlockReceived                      : Disabled
**              OnMasterByteReceived                       : Disabled
**              OnSlaveBlockSent                           : Enabled
**              OnSlaveBlockReceived                       : Enabled
**              OnSlaveByteReceived                        : Enabled
**              OnSlaveRxRequest                           : Enabled
**              OnSlaveTxRequest                           : Enabled
**              OnSlaveGeneralCallAddr                     : Disabled
**              OnError                                    : Enabled
**              OnBusStartDetected                         : Disabled
**              OnBusStopDetected                          : Disabled
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
**         Init                         - LDD_TDeviceData* I2C2_Init(LDD_TUserData *UserDataPtr);
**         SlaveSendBlock               - LDD_TError I2C2_SlaveSendBlock(LDD_TDeviceData *DeviceDataPtr, LDD_TData...
**         SlaveGetBlockSentStatus      - bool I2C2_SlaveGetBlockSentStatus(LDD_TDeviceData *DeviceDataPtr);
**         SlaveGetSentDataNum          - LDD_I2C_TSize I2C2_SlaveGetSentDataNum(LDD_TDeviceData *DeviceDataPtr);
**         SlaveCancelTransmissionBlock - LDD_TError I2C2_SlaveCancelTransmissionBlock(LDD_TDeviceData *DeviceDataPtr);
**         SlaveReceiveBlock            - LDD_TError I2C2_SlaveReceiveBlock(LDD_TDeviceData *DeviceDataPtr, LDD_TData...
**         SlaveGetBlockReceivedStatus  - bool I2C2_SlaveGetBlockReceivedStatus(LDD_TDeviceData *DeviceDataPtr);
**         SlaveGetReceivedDataNum      - LDD_I2C_TSize I2C2_SlaveGetReceivedDataNum(LDD_TDeviceData *DeviceDataPtr);
**         SlaveUpdateReceiveBlockSize  - LDD_TError I2C2_SlaveUpdateReceiveBlockSize(LDD_TDeviceData *DeviceDataPtr,...
**         SlaveCancelReceptionBlock    - LDD_TError I2C2_SlaveCancelReceptionBlock(LDD_TDeviceData *DeviceDataPtr);
**         GetError                     - LDD_TError I2C2_GetError(LDD_TDeviceData *DeviceDataPtr, LDD_I2C_TErrorMask...
**         CheckBus                     - LDD_TError I2C2_CheckBus(LDD_TDeviceData *DeviceDataPtr, LDD_I2C_TBusState...
**         GetStats                     - LDD_I2C_TStats I2C2_GetStats(LDD_TDeviceData *DeviceDataPtr);
**         ClearStats                   - void I2C2_ClearStats(LDD_TDeviceData *DeviceDataPtr);
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
** @file I2C2.h
** @version 01.07
** @brief
**          This component encapsulates the internal I2C communication
**          interface. The implementation of the interface is based
**          on the Philips I2C-bus specification version 2.0.
**          Interface features:
**          MASTER mode
**            - Multi master communication
**            - The combined format of communication possible
**              (see SendStop parameter in MasterSend/ReceiveBlock method)
**            - 7-bit slave addressing (10-bit addressing can be made as well)
**            - Acknowledge polling provided
**            - No wait state initiated when a slave device holds the SCL line low
**            - Holding of the SCL line low by slave device recognized as 'not available bus'
**            - Invalid start/stop condition detection provided
**          SLAVE mode
**            - 7-bit slave addressing
**            - General call address detection provided
*/         
/*!
**  @addtogroup I2C2_module I2C2 module documentation
**  @{
*/         

#ifndef __I2C2_H
#define __I2C2_H

/* MODULE I2C2. */

/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* Include inherited components */

#include "Cpu.h"

/* Don't know why this isn't included already */
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif 

#define I2C2_EMPTY_CHAR 0x00U          /* Empty character */
#define I2C2_SLAVE_ADDRESS 0x2AU       /* Slave address value */

/*! Peripheral base address of a device allocated by the component. This constant can be used directly in PDD macros. */
#define I2C2_PRPH_BASE_ADDRESS  0x40066000U
  
/*! Device data structure pointer used when auto initialization property is enabled. This constant can be passed as a first parameter to all component's methods. */
#define I2C2_DeviceData  ((LDD_TDeviceData *)PE_LDD_GetDeviceStructure(PE_LDD_COMPONENT_I2C2_ID))

/* Methods configuration constants - generated for all enabled component's methods */
#define I2C2_Init_METHOD_ENABLED       /*!< Init method of the component I2C2 is enabled (generated) */
#define I2C2_SlaveSendBlock_METHOD_ENABLED /*!< SlaveSendBlock method of the component I2C2 is enabled (generated) */
#define I2C2_SlaveGetBlockSentStatus_METHOD_ENABLED /*!< SlaveGetBlockSentStatus method of the component I2C2 is enabled (generated) */
#define I2C2_SlaveGetSentDataNum_METHOD_ENABLED /*!< SlaveGetSentDataNum method of the component I2C2 is enabled (generated) */
#define I2C2_SlaveCancelTransmissionBlock_METHOD_ENABLED /*!< SlaveCancelTransmissionBlock method of the component I2C2 is enabled (generated) */
#define I2C2_SlaveReceiveBlock_METHOD_ENABLED /*!< SlaveReceiveBlock method of the component I2C2 is enabled (generated) */
#define I2C2_SlaveGetBlockReceivedStatus_METHOD_ENABLED /*!< SlaveGetBlockReceivedStatus method of the component I2C2 is enabled (generated) */
#define I2C2_SlaveGetReceivedDataNum_METHOD_ENABLED /*!< SlaveGetReceivedDataNum method of the component I2C2 is enabled (generated) */
#define I2C2_SlaveUpdateReceiveBlockSize_METHOD_ENABLED /*!< SlaveUpdateReceiveBlockSize method of the component I2C2 is enabled (generated) */
#define I2C2_SlaveCancelReceptionBlock_METHOD_ENABLED /*!< SlaveCancelReceptionBlock method of the component I2C2 is enabled (generated) */
#define I2C2_GetError_METHOD_ENABLED   /*!< GetError method of the component I2C2 is enabled (generated) */
#define I2C2_CheckBus_METHOD_ENABLED   /*!< CheckBus method of the component I2C2 is enabled (generated) */
#define I2C2_GetStats_METHOD_ENABLED   /*!< GetStats method of the component I2C2 is enabled (generated) */
#define I2C2_ClearStats_METHOD_ENABLED /*!< ClearStats method of the component I2C2 is enabled (generated) */

/* Events configuration constants - generated for all enabled component's events */
#define I2C2_OnSlaveBlockSent_EVENT_ENABLED /*!< OnSlaveBlockSent event of the component I2C2 is enabled (generated) */
#define I2C2_OnSlaveBlockReceived_EVENT_ENABLED /*!< OnSlaveBlockReceived event of the component I2C2 is enabled (generated) */
#define I2C2_OnSlaveByteReceived_EVENT_ENABLED /*!< OnSlaveByteReceived event of the component I2C2 is enabled (generated) */
#define I2C2_OnSlaveRxRequest_EVENT_ENABLED /*!< OnSlaveRxRequest event of the component I2C2 is enabled (generated) */
#define I2C2_OnSlaveTxRequest_EVENT_ENABLED /*!< OnSlaveTxRequest event of the component I2C2 is enabled (generated) */
#define I2C2_OnError_EVENT_ENABLED     /*!< OnError event of the component I2C2 is enabled (generated) */



/*
** ===================================================================
**     Method      :  I2C2_Init (component I2C_LDD)
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
**                         - Pointer to the device data structure. 
*/
/* ===================================================================*/
LDD_TDeviceData* I2C2_Init(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Method      :  I2C2_SlaveSendBlock (component I2C_LDD)
*/
/*!
**     @brief
**         This method writes a block of characters to the I2C bus
**         after the master starts the communication. If no character
**         is ready for a transmission (user's output slave buffer is
**         empty or method SlaveSendBlock is not call), the "Empty
**         character" will be sent (see "Empty character" property). In
**         SLAVE mode the data are not copied to an internal buffer and
**         remains in the original location. Therefore the content of
**         the buffer should not be changed until the transmission is
**         complete. If the method returns ERR_OK, it doesn't mean that
**         transmission was successful. The state of transmission is
**         detectable by means of events (OnSlaveBlockSent or OnError).
**         This method is available only for the SLAVE or MASTER -
**         SLAVE mode.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
**     @param
**         BufferPtr       - Pointer to the block of data
**                           to send.
**     @param
**         Size            - Size of the data block.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_DISABLED -  Device is disabled
**                           ERR_SPEED - This device does not work in
**                           the active clock configuration
**                           ERR_BUSY - The I2C device is busy
*/
/* ===================================================================*/
LDD_TError I2C2_SlaveSendBlock(LDD_TDeviceData *DeviceDataPtr, LDD_TData *BufferPtr, LDD_I2C_TSize Size);

/*
** ===================================================================
**     Method      :  I2C2_SlaveGetBlockSentStatus (component I2C_LDD)
*/
/*!
**     @brief
**         This method returns current state of SlaveSendBlock method.
**         This method is available only for the SLAVE mode and if
**         method SlaveSendBlock is enabled.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
**     @return
**                         - Return value:
**                           <true> - data block is completely
**                           transmitted.
**                           <false> - data block isn't completely
**                           transmitted.
*/
/* ===================================================================*/
bool I2C2_SlaveGetBlockSentStatus(LDD_TDeviceData *DeviceDataPtr);

/*
** ===================================================================
**     Method      :  I2C2_SlaveGetSentDataNum (component I2C_LDD)
*/
/*!
**     @brief
**         This method returns the number of transmitted characters
**         from the transmit buffer. This method is available only for
**         the SLAVE mode and if method SlaveSendBlock is enabled.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
**     @return
**                         - The number of sent characters.
*/
/* ===================================================================*/
LDD_I2C_TSize I2C2_SlaveGetSentDataNum(LDD_TDeviceData *DeviceDataPtr);

/*
** ===================================================================
**     Method      :  I2C2_SlaveCancelTransmissionBlock (component I2C_LDD)
*/
/*!
**     @brief
**         This method cancels transmission of SlaveSendBlock method.
**         This method is available only for the SLAVE mode and if
**         method SlaveSendBlock is enabled.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_DISABLED - Device is disabled
**                           ERR_SPEED - This device does not work in
**                           the active clock configuration
*/
/* ===================================================================*/
LDD_TError I2C2_SlaveCancelTransmissionBlock(LDD_TDeviceData *DeviceDataPtr);

/*
** ===================================================================
**     Method      :  I2C2_SlaveReceiveBlock (component I2C_LDD)
*/
/*!
**     @brief
**         This method receives a block of characters of the I2C bus
**         after the master starts the communication. In SLAVE mode the
**         data are not copied to an internal buffer and remains in the
**         original location. Therefore the content of the buffer
**         should not be changed until the transmission is complete. If
**         the method returns ERR_OK, it doesn't mean that transmission
**         was successful. The state of transmission is detectable by
**         means of events (OnSlaveBlockReceived or OnError). State
**         LDD_I2C_SLAVE_TX_UNDERRUN of method GetError is return, when
**         no character is ready for a reception  (user's input slave
**         buffer is empty). This method is available only for the
**         SLAVE or MASTER - SLAVE mode.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
**     @param
**         BufferPtr       - Pointer to A buffer where
**                           received characters will be stored.
**     @param
**         Size            - The size of the block.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_DISABLED -  Device is disabled
**                           ERR_SPEED - This device does not work in
**                           the active clock configuration
**                           ERR_BUSY - The I2C device is busy
*/
/* ===================================================================*/
LDD_TError I2C2_SlaveReceiveBlock(LDD_TDeviceData *DeviceDataPtr, LDD_TData *BufferPtr, LDD_I2C_TSize Size);

/*
** ===================================================================
**     Method      :  I2C2_SlaveGetBlockReceivedStatus (component I2C_LDD)
*/
/*!
**     @brief
**         This method returns current state of SlaveReceiveBlock
**         method. This method is available only for the SLAVE mode and
**         if method SlaveReceiveBlock is enabled.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
**     @return
**                         - Return value:
**                           <true> - data block is completely received.
**                           <false> - data block isn't completely
**                           received.
*/
/* ===================================================================*/
bool I2C2_SlaveGetBlockReceivedStatus(LDD_TDeviceData *DeviceDataPtr);

/*
** ===================================================================
**     Method      :  I2C2_SlaveGetReceivedDataNum (component I2C_LDD)
*/
/*!
**     @brief
**         This method returns the number of received characters in the
**         receive buffer. This method is available only for the SLAVE
**         mode and if method SlaveReceiveBlock is enabled.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
**     @return
**                         - The number of characters in the input
**                           buffer.
*/
/* ===================================================================*/
LDD_I2C_TSize I2C2_SlaveGetReceivedDataNum(LDD_TDeviceData *DeviceDataPtr);

/*
** ===================================================================
**     Method      :  I2C2_SlaveUpdateReceiveBlockSize (component I2C_LDD)
*/
/*!
**     @brief
**         This method updates received block size in slave mode. For
**         correct function must this method called in
**         OnSlaveByteReceived. This method is available only for the
**         Slave or MASTER - SLAVE mode.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
**     @param
**         Size            - The size of the block.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_DISABLED -  Device is disabled
**                           ERR_SPEED - This device does not work in
**                           the active clock configuration
**                           ERR_NOTAVAIL - It is not possible set new
**                           value receive block size, slave is not
**                           receive block.
**                           ERR_PARAM_SIZE -  Value of block size is
**                           out of range.
*/
/* ===================================================================*/
LDD_TError I2C2_SlaveUpdateReceiveBlockSize(LDD_TDeviceData *DeviceDataPtr, LDD_I2C_TSize Size);

/*
** ===================================================================
**     Method      :  I2C2_SlaveCancelReceptionBlock (component I2C_LDD)
*/
/*!
**     @brief
**         This method cancels reception of SlaveReceiveBlock method.
**         This method is available only for the SLAVE mode and if
**         method SlaveReceiveBlock is enabled.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_DISABLED - Device is disabled
**                           ERR_SPEED - This device does not work in
**                           the active clock configuration
*/
/* ===================================================================*/
LDD_TError I2C2_SlaveCancelReceptionBlock(LDD_TDeviceData *DeviceDataPtr);

/*
** ===================================================================
**     Method      :  I2C2_GetError (component I2C_LDD)
*/
/*!
**     @brief
**         Returns value of error mask, e.g. LDD_I2C_ARBIT_LOST.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
**     @param
**         ErrorMaskPtr    - Pointer to a variable
**                           where errors value mask will be stored.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_DISABLED -  Device is disabled
**                           ERR_SPEED - This device does not work in
**                           the active clock configuration
*/
/* ===================================================================*/
LDD_TError I2C2_GetError(LDD_TDeviceData *DeviceDataPtr, LDD_I2C_TErrorMask *ErrorMaskPtr);

/*
** ===================================================================
**     Method      :  I2C2_CheckBus (component I2C_LDD)
*/
/*!
**     @brief
**         This method returns the status of the bus. If the START
**         condition has been detected, the method returns LDD_I2C_BUSY.
**         If the STOP condition has been detected, the method returns
**         LDD_I2C_IDLE.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
**     @param
**         BusStatePtr     - Pointer to a variable,
**                           where value of status is stored.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_DISABLED -  Device is disabled
**                           ERR_SPEED - This device does not work in
**                           the active clock configuration
*/
/* ===================================================================*/
LDD_TError I2C2_CheckBus(LDD_TDeviceData *DeviceDataPtr, LDD_I2C_TBusState *BusStatePtr);

/*
** ===================================================================
**     Method      :  I2C2_GetStats (component I2C_LDD)
*/
/*!
**     @brief
**         Returns receive/transmit statistics.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
**     @return
**                         - Device receive/transmit statistics since the
**                           device initialization or since the
**                           statistical information has been cleared.
*/
/* ===================================================================*/
LDD_I2C_TStats I2C2_GetStats(LDD_TDeviceData *DeviceDataPtr);

/*
** ===================================================================
**     Method      :  I2C2_ClearStats (component I2C_LDD)
*/
/*!
**     @brief
**         Clears the receive/transmit statistics. This method is
**         available only when GetStats methos is enabled.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
*/
/* ===================================================================*/
void I2C2_ClearStats(LDD_TDeviceData *DeviceDataPtr);

/*
** ===================================================================
**     Method      :  I2C2_Interrupt (component I2C_LDD)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes event(s) of the component.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
/* {Default RTOS Adapter} ISR function prototype */
PE_ISR(I2C2_Interrupt);

/* END I2C2. */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif
/* ifndef __I2C2_H */
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
