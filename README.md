# CMPE453 Embedded Systems

## Lab 6 - Adjustable Clock Design by Using Timers

In this lab, you will design a real clock by programming Timer1 of the AVR Microcontroller. 

### Hardware Requirements
1) Arduino Uno Board 
2) Arduino Base Shield 
3) Breadboard 
4) Push Button 
5) LCD Display 
6) 2 LEDs with Resistors 
7) Connecting wires

> [!TIP]
> [Code snippet for the Grove LCD](https://wiki.seeedstudio.com/Grove-LCD_RGB_Backlight/) and [code snippet for the Grove Button](https://wiki.seeedstudio.com/Grove-Button/) can be useful. Also, [this function](https://docs.arduino.cc/language-reference/en/functions/time/millis/) can be useful for time calculation.

### Software Setup
Program	the	microcontroller	by using C programming on Arduino IDE. When	your program runs, it should do	the	following task.

1) It should continue displaying the current time on LCD display in the form of HH:MM:SS. 
2) You should also use a push button in order to change the hour and minute by sending the new 
values by using UART communication. 
3) AVR should listen to UART and get the hour and minute from the user input. 
4) If there is 1 press on the button in 2 seconds, the value sent by the user should set the hour part on 
the clock and LED1 should be on for 1 second. If there are 2 presses on the button in 2 seconds, the 
value sent by the user should set the minute part on the clock and LED2 should be on for 1 second. 
5) Hour values outside of [0,23] and minute values outside of [0,59] should be accepted as invalid, 
and the user should be prompted to enter new values.
