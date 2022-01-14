/* ###################################################################
 **     Filename    : Events.c
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
 ** @file Events.c
 ** @version 01.00
 ** @brief
 **         This is user's event module.
 **         Put your event handler code here.
 */
/*!
 **  @addtogroup Events_module Events module documentation
 **  @{
 */
/* MODULE Events */

#include "Cpu.h"
#include "WDT.h"
#include "Events.h"

#ifdef __cplusplus
extern "C" {
#endif 

/* User includes (#include below this line is not maintained by Processor Expert) */

#include "WDT.h"

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
void Cpu_OnNMIINT(void) {
	/* Write your code here ... */
}

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
void WDI_TIMER_OnCounterRestart(LDD_TUserData *UserDataPtr) {
//	WD_WDI_SetVal(WD_WDI_DeviceData);
//	WAIT1_Waitms(1);
//	WD_WDI_ClrVal(WD_WDI_DeviceData);
}

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
void I2C2_OnSlaveBlockSent(LDD_TUserData *UserDataPtr) {
	WDT_TDataState *ptr = (WDT_TDataState*) UserDataPtr;
	ptr->dataTransmittedFlg = TRUE;
}

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
void I2C2_OnSlaveBlockReceived(LDD_TUserData *UserDataPtr) {
	WDT_TDataState *ptr = (WDT_TDataState*) UserDataPtr;
	ptr->dataReceivedFlg = TRUE;
}

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
void I2C2_OnSlaveRxRequest(LDD_TUserData *UserDataPtr) {
	//WDT_I2C_RX();
}

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
void I2C2_OnSlaveTxRequest(LDD_TUserData *UserDataPtr) {
	//WDT_I2C_TX();
}

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
void I2C2_OnSlaveByteReceived(LDD_TUserData *UserDataPtr) {
	/* Write your code here ... */
}

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
void I2C2_OnError(LDD_TUserData *UserDataPtr) {
	/* Write your code here ... */
}

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
void OBC_IRQ_OnInterrupt(void) {
	//WDT_I2C_RX();
}

/* END Events */

#ifdef __cplusplus
} /* extern "C" */
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
