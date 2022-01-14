# Ubo - an open source nano-satellite project 

## Overview
Ubo is a nano-satellite. 
The software in this repo contains software for Satellite Applications Catapult's Ubo. 

#### Nano-satellite?
Nano satellite is not a nano scale satellite, but relatively to the existing satellites (e.g. the International Space Station is of the size of a football pitch), nano-satellites are really tiny. The Ubo currently is designed to have the form factor or a PocketQube. A PocketQube defines that one unit (of satellite) is 5cm x 5cm x 5cm. Ubo is designed to be a 2.5 unit satellite, i.e it is 5cm x 5cm x 12.5cm

## Getting Started

#### Installation
1. Install ProMicro driver to your computer: 
	* For instructions, see "Installing:Windows" or "Installing:Max&Linux" section at:
	* https://learn.sparkfun.com/tutorials/pro-micro--fio-v3-hookup-guide
	* When you have done this correctly, you should see ProMicro in your port (might not be exactly same port as the diagram):
(insert screenshot)

2. Install SFE board libraries for the Arduino IDE by following the instructions here: https://github.com/sparkfun/SF32u4_boards

3. Install platform libraries: Copy sub-directory from platform/ to <Arduino IDE installed location>\libraries http://www.arduino.cc/en/Guide/Libraries#toc3

4. Open any sketch in examples/ for reference

_Arduino IDE installed location_ is the folder where your Arduino IDE is installed to, for example on windows, it could be: C:\Program Files (x86)\Arduino

#### Repo structure 
* src/platform - the satellite platform
** src/platform/example - main example Arduino sketches to demonstrate the use of the satellite's basic platform, excluding specific payloads
** src/platform/lib - required library dependencies for the satellite platform
* src/payload - optional library dependencies for Arduino to add instrumentation to the platform, for example, to carry out science and research functions. 
** src/payload/_A Custom Payload_ - a payload that plugs in on the satellite platform
** src/payload/_A Custom Payload_/example - example for the custom payload
** src/payload/_A Custom Payload_/lib - library dependency for the custom payload, if any.
* learn - example code for experimenting with each individual components, independent of the satellite. The same examples are probably available in your examples as they come included with all of the dependencies we install. 

Each subdirectory in the above folder contain the library code for a component (cpp, h) with an example subfolder containing Arduino sketch(s) to demonstrate/test the use of the component.

#### Software Architecture
The following is a class diagram for the satellite platform.

![softwarearchitecture.png](https://github.com/SACatapultAdmin/UboFirmware/blob/readme_update/softwarearchitecture.png)

The cleanest entry point if you are new to Arduino or satellite is the Cube class, otherwise you are welcome to use the Radio class etc as modules for building your own satellite platform. 

## Contributions

#### Contributors
* Laurence Stant
* Jonathan Crabb
* Chris Brunskill 
* Stephanie Pau
* George Addison
* Kevin Singh
