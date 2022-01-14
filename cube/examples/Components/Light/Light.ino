#include <Wire.h>
#include "Adafruit_SI1145.h"
#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>
Adafruit_SI1145 uv = Adafruit_SI1145();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // setting the baud rate
  while(!Serial);     // wait until serial monitor is open to run code
  Serial.println("Adafruit SI1145 test");

  // if statement to show whether or not SI1145 has been successfully initialised or not
  if(!uv.begin()){
    Serial.println("Didn't find SI1145");
    while(1);
  } else{
    Serial.println("SI1145 initialisation successful.");
  }
}

void getData(){
  Serial.print("Vis: ");
  Serial.println(uv.readVisible()); //reading visible light data
  Serial.print("IR: ");
  Serial.println(uv.readIR()); //reading IR data
  Serial.print("UV Index: ");
  Serial.print((uv.readUV()/100.0)); //reading UV data and postprocessing
  Serial.print("\n"); // starts next print on new line
}

void loop() {
  // put your main code here, to run repeatedly:
  getData(); //runs the getData function
  delay(1000); //delay of 1 seconds before loop repeats
}
