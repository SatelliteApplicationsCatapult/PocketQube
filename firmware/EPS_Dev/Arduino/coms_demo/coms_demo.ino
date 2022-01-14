#include <i2c_t3.h>
#define WDI     2
#define LED1     33
#define LED2     32
#define target  0x2A
#define kick    0x55
#define WRITE    0x00
#define READ     0x20
#define SETRATE  0x30

uint8_t var = 0;
uint8_t ctl_wd = 0x80;
char buf;
int ledState = LOW;
uint8_t data[2];
uint8_t i = 0;

void setup() {
  //Serial.begin(9600); // USB is always 12 Mbit/sec
  //Serial.println("Init...");
  pinMode(LED1, OUTPUT);   // LED
  pinMode(LED2, OUTPUT);   // LED
  digitalWrite(LED1, LOW); // LED off
  digitalWrite(LED2, LOW); // LED off

  pinMode(WDI, INPUT);
  attachInterrupt(WDI, isrService, RISING);
  Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_100);

  Serial.begin(115200);
}

void loop() {
  Serial.print("Battery voltage: ");
  uint16_t voltage = (data[0] << 4) | (data[1] & 0xF);
  double true_voltage = voltage * 3.266 * 2;
  true_voltage = true_voltage / 4096;
  //true_voltage *= 3.266 * 2;
  Serial.print(true_voltage);
  Serial.println("V");
  delay(2000);
}

void isrService() {
    cli(); //Disable interrupts
    digitalWrite(LED1, HIGH);
    Wire.beginTransmission(target); // Addressing target to WRITE
    Wire.write(0x10); // Slave transmit data CMD
    Wire.write(0x1C); // Register address, relative to 0x20000BC0 (so 20000BDC, battery V)
    Wire.endTransmission(I2C_NOSTOP); // Blocking write, triggers repeated start
    Wire.requestFrom(target,2);
    while(Wire.available()) {
      data[i] = Wire.readByte();
      i++;
    }
    i = 0;
    //Wire.write(ctl_wd);
    //Wire.write(kick);
    //Wire.write(var);
//    Wire.write(0x20); // Slave receive data
//    Wire.write(0x08); // Register address, relative to 0x20000BBF (so 20000BC3)
//    Wire.write(0x55); // Data to write to address
   // Wire.endTransmission(I2C_STOP);
    //var += 1;
    //Wire.requestFrom(target, 1, I2C_STOP);
    //var = Wire.readByte();
    //var += 1;
    //Wire.finish();
    //delay(50);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2,  ledState = ledState ? LOW : HIGH);
    sei(); //Re-enable interupts
  }
