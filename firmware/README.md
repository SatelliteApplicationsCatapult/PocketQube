# UboEPS
Firmware for the ubo electrical power system.

Overview
------

This repoisitory containes the code required for the MKL02ZVFM4 ARM microcontroller on the EPS board of the ubo satellite. This chip provides power management for the entire satellite. Communication between the EPS and OBC is through the I<sup>2</sup>C lines on the PQ60 header. Power line switching is performed using the chip IOs and PTC polyfuse protected high side MOSFET switches, and current and voltage measurements are performed using the chips internal ADC.

Wiki
------

For full details of the hardware and software involved in the electrical power system, including advice on installing the toolchain, please see the relevant pages of the [company wiki](http://185.30.10.76/wiki/index.php/Ubo).
