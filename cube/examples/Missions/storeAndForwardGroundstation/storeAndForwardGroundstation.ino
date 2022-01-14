#include <RFM69.h>    //get it here: https://www.github.com/lowpowerlab/rfm69
#include <SPI.h>

#define NETWORKID     100  //the same on all nodes that talk to each other
#define NODEID        1

#define FREQUENCY     RF69_433MHZ
#define ENCRYPTKEY     null
#define IS_RFM69HCW    true

#define SERIAL_BAUD   115200

#define RFM69_CS      8
#define RFM69_IRQ     3
#define RFM69_IRQN    3  // Pin 3 is IRQ 3!
#define RFM69_RST     4

int16_t packetnum = 0;  // packet counter, we increment per xmission
char transmitMessage[61];

RFM69 radio = RFM69(RFM69_CS, RFM69_IRQ, IS_RFM69HCW, RFM69_IRQN);

void setup() {
  Serial.begin(SERIAL_BAUD);
  while (!Serial) {};
  Serial.println("Ubo groundstation");

  pinMode(RFM69_RST, OUTPUT);
  digitalWrite(RFM69_RST, HIGH);
  delay(100);
  digitalWrite(RFM69_RST, LOW);
  delay(100);

  // Initialize radio
  radio.initialize(FREQUENCY, NODEID, NETWORKID);
  if (IS_RFM69HCW) {
    radio.setHighPower();    // Only for RFM69HCW & HW!
  }
  radio.setPowerLevel(31); // power output ranges from 0 (5dBm) to 31 (20dBm)

  radio.encrypt(ENCRYPTKEY);
  Serial.println("Listening for messages...");
  Serial.println("Type a new message and send it to update the satellite message");

  Serial.setTimeout(50);

}

void loop() {

  if (radio.receiveDone())
    {
      //print message received to serial
      Serial.print('['); Serial.print(radio.SENDERID); Serial.print("] ");
      Serial.print("[RX_RSSI:"); Serial.print(radio.RSSI); Serial.print("] ");
      Serial.println((char*)radio.DATA);
    }

  if (Serial.available()) {
    Serial.readBytes(transmitMessage, 60); // Read 60 bytes (times out if less)
    delay(10); // If we enter more than 60 characters, we just ignore the rest
    while (Serial.available()) { 
      Serial.read(); // Discard remaining bytes
    }
    radio.send(55, transmitMessage, strlen(transmitMessage)); // Transmit new message
    memset(transmitMessage, 0, sizeof(transmitMessage)); // empty array for next time
  }
}
