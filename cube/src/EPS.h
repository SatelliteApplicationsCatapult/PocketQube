#ifndef EPS_H
#define EPS_H

#include <stdint.h>
#include <stdbool.h>
#include "Config.h"     // Local pin definitions and other preprocessor macros


/*****************************************************************************
* This class provides access to the version 2.0 ubo PocketQube EPS (Electric
* Power System).
******************************************************************************/

class EPS {
    public:
        EPS();
        ~EPS();
        void reset();
        bool watchdogTimeoutSet(uint8_t timeout);
        bool watchdogKick();
        bool outputGet(uint8_t output);
        bool outputSet(uint8_t output, bool status);
        float batteryVoltage();
        float batteryCurrent();
        float batteryPower();
        float solarVoltage();
        float solarCurrent();
        float solarPower();
        float systemCurrent();
        float systemPower();
        float switchedCurrentReg();
        float switchedPowerReg();
        float switchedCurrentRaw();
        float switchedPowerRaw();
        bool statusCheck();
        bool pwrFlag; //Power good?
        bool chgFlag = 0;
        bool solFlag;
        bool usbFlag;
        bool swtFLT;
        bool snsFLT;
        bool mcuFLT;
        bool i2c_get();
        bool i2c_set(uint8_t reg, uint8_t val[4]);
        uint8_t outputStatus = 0xE0;
        uint8_t outputReg = 0x06;
        uint8_t buffer[2] = {0};

        //EPS register addresses
        #define STATUS_REG 5
        #define VOLTAGE_BATTERY_H 8 //Raw battery voltage high register
        #define VOLTAGE_BATTERY_L 9
        #define CURRENT_MPPT_H 12
        #define CURRENT_MPPT_L 13
        #define CURRENT_BATTERY_TOTAL_H 14 //Raw battery current high register
        #define CURRENT_BATTERY_TOTAL_L 15 //Raw battery current low register

};

#endif
