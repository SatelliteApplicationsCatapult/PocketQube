# Ubo Platform Library

## Overview 
Ubo platform is the minimal requirement for making a Ubo satellite - a nano-satellite of PocketQube specification. 

This directory in the repo contains the code that forms the platform part of a Ubo. 

#### What platform?
The basic elements of a platform is:
1. Microcontroller board - the motherboard of the satellite
2. Radio - provides comms to the satellite
	* https://www.sparkfun.com/tutorials/381 
3. IMU - provide basic sense of direction to the satellite

## Getting started - running the platform

* Install Ubo as a library 
* Open Arduino IDE, load up any examples in Examples > Ubo > basic > blink 
* Upload the code to your Ubo and see that the LED blinks on your [OBC]()
* Now go ahead and load other examples and try making changes!

## Getting started - developing the platform
So now you've updated the examples and feel more savvy. You want to modify the behaviour of the platform. 
Well, here's a bit of a jump but we'll guide you through it. 

First, you will need to install the dependency library for the platform before you can develop on it. 

The following assume you will get started using Arduino IDE, which you have already installed. 
* If you have not installed Arduino IDE, please follow the [instructions here for download and install of Arduino IDE](http://www.arduino.cc/en/Main/Software).

#### Installation dependencies
The platform make use of several hardware components, like radio, which also comes with software. So you will need to install these dependencies following these instructions:

* \lib - The libraries this platform dependent on can be found here
* [Import these libraries into your Arduino IDE] (http://arduino.cc/en/Guide/Libraries). i.e. copy all the subfolders under \lib into _Your Arduino IDE installed location_\libraries
 
#### Open up the examples
* Once you have installed the 

#### Main classes
Finally you are now ready to start coding on the platform!

_Cube_ is the main class that represents the highest level entry point to the platform and it has access to all of its components: radio, telemetry and interface to payload.
* Create an instance of _Cube_ for calling on basic functions of the satellites
* If you are a payload developer, please refer to the README at payload directory
