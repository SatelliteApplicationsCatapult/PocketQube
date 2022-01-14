#include "MockPayload.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM9DS0.h>
#include <Adafruit_SI1145.h>
#include <Cube.h>
//
// PUBLIC METHODS
//

//add led on in doing method
//add lef off in done method 

MockPayload::MockPayload() {};
MockPayload::~MockPayload() {};
Cube bubo;

void MockPayload::initialise() {
	Adafruit_SI1145 uv = Adafruit_SI1145();
	if (!uv.begin()){
		Serial.println("Didn't find SI1145");
	}else{
		Serial.println("Initialization of SI1145 library was successful");
	}
	pinMode(LED_PIN, OUTPUT);
};

int MockPayload::doing(){
	pinMode(LED_PIN, OUTPUT);
	Serial.println("Hello Doing method initialised");
	Serial.println("Turning the LED ON");
	digitalWrite(LED_PIN, HIGH);
	Adafruit_SI1145 uv = Adafruit_SI1145();
	float Light;
	Serial.println("Taking a light reading");
	// Light = uv.readVisible();
	Light = bubo.telemetry.getLight();
	Serial.println("Printing a light reading to serial");
	Serial.println(Light);
	Serial.println("Exiting the Doing Method");
	return Light;
};


int MockPayload::done() {
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, LOW);
	Serial.println("MockPayload has finished its mission!");
    return 0;
};
