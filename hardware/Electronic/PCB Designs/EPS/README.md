# PQ60 Electrical Power System

### At a glance
The current EPS design features the following basic systems:

1. Four _IXYS_ solar panels as a power source

2. Two _LTC3105_ based MPPT circuits to maximise the solar power generated

3. A _MAX8606ETD_ charge management IC to facilitate safe battery charging and effective system load management.

4. A regulation circuit including:
	* A watchdog timer to detect unresponsive MCUs (_STWD100PYW83F_)
	* A brownout monitor to detect invalid voltages (_BU4231G-TR_)
	* A 3V3 LDO regulator with active-high enable, allowing supervisor ICs or external MCUs to trigger a reset (_MIC5353-3.3YMT_)
	
5. Current monitoring:
	* _FAN4010IL6X_F113_ based high-side unidirectional current sense amplifier ICs to monitor solar output, total 3V3 draw and draw from the battery voltage line on the PQ60 bus
	* _INA211A_ based high-side bi-directional current sense amplifier to monitor total current draw and supply to the battery
	
6. Voltage monitoring:
	* Two MOSFET switched divider networks to measure the MPPT output voltage, the raw battery voltage
	* Direct measurement through MCU ADC of the 3V3 bus voltage
	
7. A 650mAh 3.7V single cell lithium polymer battery

8. Five high-side MOSFET (_NTA4151P & FK3303010L_) switched lines for the __PQ60__ standard, three 3V3 and two raw battery voltage. Each line is reverse polarity protected by the MOSFET and over current protected by a resettable polyfuse (_1206L025YR_)

9. A single _MKL02Z32VFM4_ 32 bit Kinetis MCU, for power management, current and voltage monitoring, line switching and communication with the OBC through I2C

### Usage
Will write something in this section once we actually have an EPS and some code to go with it. Maybe unnecessary if all dealt with through cube library? Will list maximum ratings, tolerances and so on.

### Current design
The current revision of the EPS board uses four __IXYS__ solar panels (_SLMD121H10L-ND_) as a power source, or can also be charged from a standard USB supply. The board contains two Maximum Power Point Tracker (MPPT) circuits based on the __LTC3105__ (_LTC3105EDD#PBF_) DC-DC switching boost regulator, sharing two panels each, with a low forward voltage drop schottkey diode to prevent reverse current leakage from the panels while not illuminated. The output of the MPPT circuits is fed through a twin channel MOSFET based ideal diode IC (_LTC4413_) to the charge management IC (_MAX8606ETD+T_). The total current produced by the MPPT circuits and delivered to the charging IC is monitored by a high side current sense amplifier (_FAN4010IL6X_), and the supply voltage can be measured through a resistor divider network. A MOSFET exists (_NX7002AK_) to disable this divider circuit to prevent current draw when not required. The charge management IC includes integrated load servicing. When the battery voltage exceeds 3.5V, the system output will be internally connected to the battery. Below this voltage, the power supply to the IC will first be used to service the system load, with the remaining available current being used to charge the battery. Both charging sources, the MPPTs and the USB supply, can be disabled if required, in order to obtain accurate battery voltage measurements. The MPPTs can be disabled through a signal to the SHDN input, and the USB supply is connected through a high side switched MOSFET circuit to enable disconnecting. The SHDN signal to the _LTC3105_ MPPTs is connected through an opto-isolator to allow recovery in the event of a fully discharged battery.
