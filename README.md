# Whac-A-Mole
Electronic reaction game based on NodeMCU (ESP8266).

## Introduction
A reaction game inspired by "Whac-a-Mole" where the user has to push the correct button indicated by 3 colored LEDs. There are 3 game modes (simple/button/color) that are changed every 10 rounds. Every mode change the difficulty will be increased by reducing the available time. Also every round the reaction time will be decreased. This results in 10 rounds of play that get more and more intense, then after a mode change the stress is reduced as the new mode starts a little bit easier than the last few round in the previous mode.
## Design
The game will be placed in a chassis with an OLED display, 3 RGB-LEDs and 3 buttons (R/G/B) aligned with the LEDs. The ESP will be an ESP8266 on a NodeMCU board. As there are 9 LED stati to address (every LED has R/G/B), 3 buttons and an OLED I2C bus to be connected the LED control will be handled with an IC Shift Register (8-Bit SIPO) needing just 1 data PIN and 1 clock instead of 9 GPIOs.
## Game Modes
### Simple
The LED aligned with the button to be pressed will light up in the corresponding button color.
### correct button
The LED aligned with the button to be pressed will light up in a random color.
### correct color
A random LED will light up in the corresponding button color that is supposed to be pressed.
## Schematics
in progress
## Parts list
in progress
## Pictures
in progress
