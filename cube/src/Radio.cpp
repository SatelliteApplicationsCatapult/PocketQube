#include "Radio.h"

//
// PUBLIC METHODS
//

Radio::Radio() {
    pinMode(NIRQ_RFM, INPUT);
};
Radio::~Radio() {};


bool Radio::initialise(uint8_t NODEID, uint8_t NETWORKID) {
    if (!rfm69.initialize(RF69_433MHZ, NODEID, NETWORKID)) {
        return 0;
    }
    rfm69.setHighPower();
    rfm69.setPowerLevel(POWERLEVEL);
    //rfm69.encrypt((char *)ENCRYPTKEY);
    rfm69.encrypt(null);
    return 1;
}

bool Radio::sendMessage(const void* buffer, uint8_t length, uint8_t receiverID, bool ack, uint8_t retries, uint8_t retriesDelay) {
    if (!ack && retries == 0) { // Single transmission, no ack (default)
        rfm69.send(receiverID, buffer, length, false);
        rfm69.receiveDone(); // Put it into receive mode
        return 0; // Didn't want an ack anyway
    } else { // Multiple retries or require an ack (Override ack=false if retrying)
        if (rfm69.sendWithRetry(receiverID, buffer, length, retries, retriesDelay)) {
            rfm69.receiveDone(); // Put it into receive mode
            return 1;
        } else {
            rfm69.receiveDone(); // Put it into receive mode
            return 0; 
        } 
    }
}

bool Radio::sendBulk() {
    // TODO implement bulk transactions > 60 bytes with acks and CRCs and so on
}

bool Radio::messageAvailable() {
    return rfm69.receiveDone();
}

void Radio::receiveMessage(char* buf) {
    // Copy message data to the provided buffer
    strncpy(buf, (char*)rfm69.DATA, sizeof(rfm69.DATA));
}

bool Radio::setPower(uint8_t level) {
    if ((level <= 0) && (level >= 31)) {
        POWERLEVEL = level;
        return 1;
    }
    return 0;
}

uint8_t Radio::getPower() {
    return POWERLEVEL;
}

bool Radio::setEncrypt(uint8_t key[16]) {
    
}

void Radio::getEncrypt() {
    
}