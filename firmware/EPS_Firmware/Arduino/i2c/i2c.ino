#include <i2c_t3.h>
#define WDI     2
#define LED1     33
#define LED2     32
#define target  0x2A
#define kick    0x55

void setup() {
  pinMode(LED1, OUTPUT);   // LED
  pinMode(LED2, OUTPUT);   // LED
  pinMode(WDI, OUTPUT); // EPS IRQ line
  
  digitalWrite(LED1, LOW); // LED off
  digitalWrite(LED2, LOW); // LED off
  digitalWrite(WDI, LOW); // OBC IRQ low
  
  Serial.begin(115200);
}

void loop() {
  delay(1000);
  digitalWrite(LED1, !digitalRead(LED1));
  digitalWrite(WDI, HIGH);
  delay(1);
  digitalWrite(WDI, LOW);
}
