# Whac-A-Mole
Electronic reaction game based on NodeMCU (ESP8266).

## Introduction
A reaction game inspired by "Whac-a-Mole" where the user has to push the correct button indicated by 3 colored LEDs. There are 3 game modes (simple/button/color) that are changed every 10 rounds. Every mode change the difficulty will be increased by reducing the available time. Also every round the reaction time will be decreased. This results in 10 rounds of play that get more and more intense, then after a mode change the stress is reduced as the new mode starts a little bit easier than the last few round in the previous mode.
## Design
The game will be placed in a chassis with an OLED display, 3 RGB-LEDs and 3 buttons (R/G/B) aligned with the LEDs. The ESP will be an ESP8266 on a NodeMCU board. As there are 9 LED stati to address (every LED has R/G/B), 3 buttons and an OLED I2C bus to be connected, the LED control will be handled with an IC Shift Register (8-Bit SIPO) acting as a serial2parallel converter, therefore needing just 1 data PIN and 1 clock instead of 9 GPIOs.
## Game Modes
### Simple
The LED aligned with the button to be pressed will light up in the corresponding button color.
### correct button
The LED aligned with the button to be pressed will light up in a random color.
### correct color
A random LED will light up in the corresponding button color that is supposed to be pressed.
## Parts list
* 1x NodeMCU
* 3x Kingbright LF 59 LED RGB
* 1x Resistor for LEDs (~100Ohm)
* 3x push buttons with RGB heads
* 3x resistors as pullup for buttons (>1kOhm anything would do)
* 1x SN74LS164N shift register
* 1x DIP14 socket
* wires
* PCP Lab board
## Schematics
The 3 buttons are connected with one leg to ground. Each other leg is connected with one resistor to V+ and to the NodeMCU input Pins GPIO14, 12, 13.

The 2 input pins (A,B) of the shift register are connected to GPIO 0. The clock input to GPIO 2. The CLR input to V+. The output PINs and the input PINs are connected to the anodes of the LEDs (it might be that I reversed the order - Im not sure anymore). Only one blue per LED is beeing used (this model has 2 blue builtin):
* Input => LED1 red
* Output0 => LED1 green
* Output0 => LED1 blue
* Output0 => LED2 red
* Output0 => LED2 green
* Output0 => LED2 blue
* Output0 => LED3 red
* Output0 => LED3 green
* Output0 => LED3 blue

The Catodes of all 3 LEDs are connected via a resistor to ground (this means only 1 LED should be activated at a time - if you want to activate multiple at once you should use 1 resistor for each LED).

A buzzer can be connected between GPIO 15 and ground (optional - be aware: annoying).

The OLED display uses I2C on its default PINs and power supply of course.
## Pictures
in progress
