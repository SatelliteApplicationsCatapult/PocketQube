#include <i2c_t3.h>

#define TMP102_I2C_ADDRESS 72

void setup() {
  // put your setup code here, to run once:
  Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_400); 
  Serial.begin(115200); //defining the baud rate
  while(!Serial){};  //command to start the code once the serial terminal is opened
}

void loop() {
  // put your main code here, to run repeatedly:
  getTemp102(); //calling the function to print temperature from sensor to the serial terminal
  delay(1000); //delay of 1 second before loop repeats
}

void getTemp102(){

  //variable definitions
  byte firstByte, secondByte;
  int val;
  float convTemp;
  float correctedTemp;

  //Setting up communications with Temperature Sensor via I2C
  Wire.beginTransmission(TMP102_I2C_ADDRESS);
  Wire.write(0x00);
  Wire.endTransmission();
  Wire.requestFrom(TMP102_I2C_ADDRESS,2);
  Wire.endTransmission();

  //requesting temperature
  firstByte = Wire.read();
  secondByte = Wire.read();
  val = (firstByte << 4); //firstByte bitshifted to left by 4
  val |= (secondByte >> 4); //Bitwise OR operator
  convTemp = val*0.0625;
  correctedTemp = (convTemp - 5);  

  //printing data
  Serial.print(F("The Temperature is: "));
  Serial.print(correctedTemp);
  Serial.print(F(" Celsius \n")); 
}
