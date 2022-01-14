/* ###################################################################
**     Filename    : Events.h
**     Project     : EPS_Basic
**     Processor   : MKL02Z32VFM4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-02-03, 09:09, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.h
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "OPTO_SHDN.h"
#include "AUX_TP.h"
#include "BUS_BAT_SW2_EN.h"
#include "BUS_3V3_SW3_EN.h"
#include "BUS_3V3_SW2_EN.h"
#include "BUS_3V3_SW1_EN.h"
#include "BUS_BAT_SW1_EN.h"
#include "WD_WDI.h"
#include "RAW_BAT_ISEN_EN.h"
#include "USB_SHDN.h"
#include "SOL_VSEN_EN.h"
#include "BAT_VSEN_EN.h"
#include "I2C2.h"
#include "ADC_MODULE.h"
#include "WDI_TIMER.h"
#include "OBC_IRQ.h"
#include "ExtIntLdd1.h"
#include "WAIT1.h"
#include "KSDK1.h"

#ifdef __cplusplus
extern "C" {
#endif 

/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MKL02Z32FM4]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMIINT(void);


/*
** ===================================================================
**     Event       :  WDI_TIMER_OnCounterRestart (module Events)
**
**     Component   :  WDI_TIMER [TimerUnit_LDD]
*/
/*!
**     @brief
**         Called if counter overflow/underflow or counter is
**         reinitialized by modulo or compare register matching.
**         OnCounterRestart event and Timer unit must be enabled. See
**         [SetEventMask] and [GetEventMask] methods. This event is
**         available only if a [Interrupt] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
*/
/* ===================================================================*/
void WDI_TIMER_OnCounterRestart(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  I2C2_OnSlaveBlockSent (module Events)
**
**     Component   :  I2C2 [I2C_LDD]
*/
/*!
**     @brief
**         This event is called when I2C in slave mode finishes the
**         transmission of the data successfully. This event is not
**         available for the MASTER mode and if SlaveSendBlock is
**         disabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void I2C2_OnSlaveBlockSent(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  I2C2_OnSlaveBlockReceived (module Events)
**
**     Component   :  I2C2 [I2C_LDD]
*/
/*!
**     @brief
**         This event is called when I2C in slave mode finishes the
**         reception of the data successfully. This event is not
**         available for the MASTER mode and if SlaveReceiveBlock is
**         disabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void I2C2_OnSlaveBlockReceived(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  I2C2_OnSlaveRxRequest (module Events)
**
**     Component   :  I2C2 [I2C_LDD]
*/
/*!
**     @brief
**         This event is called when its own specific address is
**         matched with the calling address and the value of the R/W
**         command bit of the calling address is set to 0, i.e., the
**         Master requests writing to the slave (the slave will be
**         receiving). After the return from the event call the first
**         data byte receiving starts. This event is not available for
**         the MASTER mode.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void I2C2_OnSlaveRxRequest(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  I2C2_OnSlaveTxRequest (module Events)
**
**     Component   :  I2C2 [I2C_LDD]
*/
/*!
**     @brief
**         This event is called when its own specific address is
**         matched with the calling address and the value of the R/W
**         command bit of the calling address is set to 1, i.e., the
**         Master requests reading from slave (the slave will be
**         sending). After the return from the event call the first
**         data byte sending will start. This event is not available
**         for the MASTER mode.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void I2C2_OnSlaveTxRequest(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  I2C2_OnSlaveByteReceived (module Events)
**
**     Component   :  I2C2 [I2C_LDD]
*/
/*!
**     @brief
**         This event is called when I2C is in slave mode and finishes
**         the reception of the byte successfully. This event is not
**         available for the MASTER mode and if SlaveReceiveBlock is
**         disabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void I2C2_OnSlaveByteReceived(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  I2C2_OnError (module Events)
**
**     Component   :  I2C2 [I2C_LDD]
*/
/*!
**     @brief
**         This event is called when an error (e.g. Arbitration lost)
**         occurs. The errors can be read with GetError method.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void I2C2_OnError(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  OBC_IRQ_OnInterrupt (module Events)
**
**     Component   :  OBC_IRQ [ExtInt_LDD]
*/
/*!
**     @brief
**         This event is called when an active signal edge/level has
**         occurred.
**     @param
**         UserDataPtr     - Pointer to RTOS device
**                           data structure pointer.
*/
/* ===================================================================*/
void OBC_IRQ_OnInterrupt(void);

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __Events_H*/
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
