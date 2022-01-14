# Ubo Payload Library

## Overview 
Payload is the instruments that a satellite carries for the purpose of completing its designated research/science task. 
Whilst the PocketQube platform libraries supply the minimal function of a satellite, payloads here can be different depending on the designed goal. 

This directory in the repo contains the code of a variety of payloads of the Ubo. 

### What payload?

The available payloads for use with the platform are:
1) Camera
2) Mock - an example of a payload that doesn't do very much but demonstrates how you can develop a payload to connect to the platform. 

Each payload is in its own folder. 

Each payload folder should have the following structure:
* <payload_folder>\ : cpp and h files at the root of the folder
* <payload_folder>\lib\ : library dependendency for the specific payload
* <payload_folder>\examples\ : example arduino sketch(es) to demonstrate the use of the payload

### Usage
1) Install the desired library (sub-folder) into the Arduino IDE 
2) Load up the examples
3) Let the platform know about this new payload

### Contribution
Each subfolder represents a payload, please ensure your payload folder has an example directory containing Arduino sketches (and a README if possible).
