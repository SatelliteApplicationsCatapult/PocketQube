#ifndef RADIO_H
#define RADIO_H

#include "RFM69.h"      // Third party radio library
#include "Config.h"     // Local pin definitions and other preprocessor macros


/*****************************************************************************
* This class encapsulates the radio of the platform.
* It is an abstraction layer (wrapper) around specific hardware implementation.
******************************************************************************/

class Radio {
    public:
        Radio();
        ~Radio();
        bool initialise(uint8_t NODEID = 2, uint8_t NETWORKID = 100);
        virtual bool sendMessage(const void* buffer, uint8_t length = 61, uint8_t receiverID = 1, bool ack = false, uint8_t retries = 0, uint8_t retriesDelay = 40);
        bool sendBulk(); //TODO implement multi-packet messaging
        bool messageAvailable();
        void receiveMessage(char* buf);
        uint8_t getPower();
        bool setPower(uint8_t level);
        void getEncrypt();
        bool setEncrypt(uint8_t key[16]);
    private:
        RFM69 rfm69 = RFM69(CS_RFM, NIRQ_RFM, true, digitalPinToInterrupt(NIRQ_RFM));
        uint8_t ENCRYPTKEY[16] = { 0 };
        uint8_t POWERLEVEL = 0;
};

#endif
