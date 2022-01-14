#include "EPS.h"
#include <Wire.h>
#include <string>
using namespace std;

EPS::EPS() {
    Wire.begin();
}
EPS::~EPS() {};

void EPS::reset() {
    // Resets the entire satellite.
    // No need to return as will be turned off...
}

bool EPS::statusCheck() {
  //Check statuses from registers
    Wire.beginTransmission(ADDR_EPS);
    //Read from high and low battery current registers
    Wire.write(0); //Put EPS into slave TX mode
    Wire.write(STATUS_REG);
    Wire.endTransmission();

    static uint8_t buffer;

    Wire.requestFrom(ADDR_EPS, 1);
    buffer = Wire.read();

    pwrFlag = bitRead(buffer, 7); //Power good?
    chgFlag = bitRead(buffer, 6); //Need to declare these
    solFlag = bitRead(buffer, 5);
    usbFlag = bitRead(buffer, 4);
    // swtFLT = bitRead(buffer, 3);
    // snsFLT = bitRead(buffer, 2);
    // mcuFLT = bitRead(buffer, 1);

}

bool EPS::watchdogTimeoutSet(uint8_t timeout) {
    // Sets the watchdog timeout period.
    return 1;
}

bool EPS::watchdogKick() {
    // Resets the watchdog counter.
    return 1;
}

bool EPS::outputGet(uint8_t output) {
    // Returns the status of the requested output.
    return 0;
}

bool EPS::outputSet(uint8_t output, bool status) {
    // Sets the status of the provided output, either enabled (1) or disabled (0).
    outputStatus ^= (-status ^ outputStatus) & (1 << output);
    uint8_t regSet[4] = {outputStatus, 0, 0, 0};
    i2c_set(outputReg, regSet);
    return 1; // on success
}

float EPS::batteryVoltage() {
    // Returns the battery voltage as a float.
    Wire.beginTransmission(ADDR_EPS);
    //Read from high and low battery current registers
    Wire.write(0); //Put EPS into slave TX mode
    Wire.write(VOLTAGE_BATTERY_H);
    Wire.endTransmission();

    Wire.requestFrom(ADDR_EPS, 2);
    buffer[1] = Wire.read();
    buffer[2] = Wire.read();

    uint16_t batteryVoltage_bin = buffer[1];
    batteryVoltage_bin = (batteryVoltage_bin << 4) | buffer[2]; //combine buffers

    float batteryVoltage = batteryVoltage_bin;
    return batteryVoltage; // Well, it's not plugged in as I'm writing this...
}

float EPS::batteryCurrent() {
    // Returns the total battery current as a float.
    // A positive value indicates a charging battery, negative discharging.
    Wire.beginTransmission(ADDR_EPS);
    Wire.write(0); //Put EPS into slave TX mode
    //Read from high and low battery current registers
    Wire.write(CURRENT_BATTERY_TOTAL_H);
    Wire.endTransmission();

    static uint8_t buffer[2] = {0};

    Wire.requestFrom(ADDR_EPS, 2);

    buffer[1] = Wire.read();
    buffer[2] = Wire.read();

    uint16_t batteryCurrent_bin = buffer[1];
    batteryCurrent_bin = (batteryCurrent_bin << 4) | buffer[2];

    float batteryCurrent = batteryCurrent_bin;
    return batteryCurrent;
}

float EPS::batteryPower() {
    // Returns the total battery power (battery voltage * current).
    // A positive value indicates a charging battery, negative discharging.
    return 0;
}

float EPS::solarVoltage() {
    // Returns the combined solar output voltage after the MPPT circuitry.
    return 0;
}

float EPS::solarCurrent() {
    // Returns the combined solar output current after the MPPT circuitry.
    Wire.beginTransmission(ADDR_EPS);
    Wire.write(0); //Put EPS into slave TX mode
    Wire.write(CURRENT_MPPT_H);
    Wire.endTransmission();

    Wire.requestFrom(ADDR_EPS, 2);
    buffer[1] = Wire.read();
    buffer[2] = Wire.read();

    uint16_t solarCurrent_bin = buffer[1];
    solarCurrent_bin = (solarCurrent_bin << 4) | buffer[2];

    float solarCurrent = solarCurrent_bin;
    return solarCurrent;
}

float EPS::solarPower() {
    // Returns the combined solar power generated after the MPPT circuitry.
    // Calculated from the solar voltage * solar current.
    return 0;
}

float EPS::systemCurrent() {
    // Returns the total current drawn on the 3.3V system line.
    // Includes MCU, IMU, light and temperature sensors, SD card and the EPS itself.
    return 0;
}

float EPS::systemPower() {
    // Returns the total power drawn on the 3.3V system line
    // Includes MCU, IMU, light and temperature sensors, SD card and the EPS itself
    // Assumes the voltage to be 3.3V as set by the regulator. This is accurate as the system will
    // shut down at low battery voltages.
    return 0;
}

float EPS::switchedCurrentReg() {
    // Returns the total current drawn by all devices on the switched 3.3V lines.
    // This includes the RFM69 radio and camera payload on lines 1 and 2 respectively.
    return 0;
}

float EPS::switchedPowerReg() {
    // Returns the total power drawn by all devices on the switched 3.3V lines.
    // This includes the RFM69 radio and camera payload on lines 1 and 2 respectively.
    // Assumes the voltage to be 3.3V as set by the regulator. This is accurate as the system will
    // shut down at low battery voltages.
    return 0;
}

float EPS::switchedCurrentRaw() {
    // Returns the total current drawn by all devices on the switched raw battery voltage lines.
    // There are currently no internal devices utilising the outputs, but they are available
    // for custon payloads that require them.
    return 0;
}
float EPS::switchedPowerRaw() {
    // Returns the total power drawn by all devices on the switched raw battery voltage lines.
    // Calculated from the raw current and measured battery voltage.
    // There are currently no internal devices utilising the outputs, but they are available
    // for custom payloads that require them.
    return 0;
}

bool EPS::i2c_set(uint8_t reg, uint8_t val[4]) {
    Wire.beginTransmission(ADDR_EPS);
    Wire.write(reg);
    for (unsigned int i = 0; i < sizeof(val); i++) {
        Wire.write(val[i]);
    }
    Wire.endTransmission();
}
