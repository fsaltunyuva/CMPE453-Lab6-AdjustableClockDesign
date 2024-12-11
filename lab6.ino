// Including necessary libraries
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd; // Declaring the lcd object

// Defining the pins for the button and the LEDs
const int buttonPin = 4;   
const int led1Pin = 2;   
const int led2Pin = 3;    

long previousTime = 0; // Variable to store the previous time
int seconds = 0; // Variable to store the seconds
int minutes = 0; // Variable to store the minutes
int hours = 0; // Variable to store the hours
int previousButtonState = LOW; // Variable to store the previous button state (LOW by default)
long buttonPressTime = 0; // Variable to store the button press time
int pressCount = 0; // Variable to store the press count


void setup() { 
  lcd.begin(16, 2); // Initializing the LCD with 16 columns and 2 rows
  pinMode(buttonPin, INPUT); // Setting the button pin as input   
  pinMode(led1Pin, OUTPUT); // Setting the LED1 pin as output  
  pinMode(led2Pin, OUTPUT); // Setting the LED2 pin as output 
  Serial.begin(9600); // Starting the serial communication   
}

void loop() {
  int currentButtonState = digitalRead(buttonPin); // Reading the current button state
  long currentTime = millis(); // Getting the current time in milliseconds

  if (currentButtonState == HIGH && previousButtonState == LOW) { // Checking if the button is pressed 
    if (pressCount == 0) { // Checking if the button is pressed for the first time
      buttonPressTime = currentTime; // Storing the button press time  
    }
    pressCount++; // Incrementing the press count   
  }

  if (currentTime - buttonPressTime >= 2000) { // Checking if the button is pressed in 2 seconds
    if (pressCount == 1) { // Checking if the button is pressed for the first time
      digitalWrite(led1Pin, HIGH); // Turning on the LED1 (blue )  
      delay(200); // Delay of 200 milliseconds  
      digitalWrite(led1Pin, LOW); // Turning off the LED1 (blue)

      if (Serial.available()) { // Checking if the serial data is available (UART)
        int value = Serial.parseInt(); // Parsing the integer value from the serial data

        if (value >= 0 && value <= 23) { // Checking if the value is between 0 and 23 (hours)
          hours = value;
        } 
        else { // If the value is not between 0 and 23 (if the value is invalid)
          lcd.clear(); // Clearing the LCD
          lcd.print("Invalid hour!"); // Displaying the message "Invalid hour!"
          delay(2000); // Delay of 2 seconds
        }
      }
    } 
    else if (pressCount == 2) { // Checking if the button is pressed for the second time in 2 seconds
      digitalWrite(led2Pin, HIGH); // Turning on the LED2 (yellow)
      delay(200); // Delay of 200 milliseconds
      digitalWrite(led2Pin, LOW); // Turning off the LED2 (yellow)

      if (Serial.available()) { // Checking if the serial data is available (UART)
        int value = Serial.parseInt();  // Parsing the integer value from the serial data 

        if (value >= 0 && value <= 59) { // Checking if the value is between 0 and 59 (minutes)
          minutes = value; // Setting the minutes to the value
        } 
        else { // If the value is not between 0 and 59 (if the value is invalid)
          lcd.clear(); // Clearing the LCD
          lcd.print("Invalid minute!"); // Displaying the message "Invalid minute!"
          delay(2000); // Delay of 2 seconds 
        }
      }
    }

    pressCount = 0; // Resetting the press count for the next button press
  }

  previousButtonState = currentButtonState; // Updating the previous button state

  if (currentTime - previousTime >= 1000) { // Checking if 1 second has passed
    incrementTime(); // Incrementing the time by 1 second   
    previousTime = currentTime; // Updating the previous time
  }

  lcd.clear(); // Clearing the LCD
  lcd.setCursor(0, 0); // Setting the cursor to the first row and first column
  
  if (hours < 10)  // Checking if the hours is less than 10 (single digit)
    lcd.print("0"); // Displaying a leading zero (Like 01, 02, ..., 09)
  lcd.print(hours); // Displaying the hours
  lcd.print(":"); // Displaying the colon (:)

  if (minutes < 10)  // Checking if the minutes is less than 10 (single digit)
    lcd.print("0"); // Displaying a leading zero (Like 01, 02, ..., 09)
  lcd.print(minutes); // Displaying the minutes
  lcd.print(":"); // Displaying the colon (:)

  if (seconds < 10) // Checking if the seconds is less than 10 (single digit)
    lcd.print("0"); // Displaying a leading zero (Like 01, 02, ..., 09)
  lcd.print(seconds); // Displaying the seconds

  delay(100); // Delay of 100 milliseconds between each time update
}

// Function to increment the time by 1 second
void incrementTime() { 
  seconds++; // Incrementing the seconds by 1
  if (seconds >= 60) { // Checking if the seconds is equal to or greater than 60 
    minutes++; // Incrementing the minutes by 1
    seconds = 0; // Resetting the seconds to 0
    if (minutes >= 60) { // Checking if the minutes is equal to or greater than 60
      hours++; // Incrementing the hours by 1
      minutes = 0; // Resetting the minutes to 0
      if (hours >= 24) { // Checking if the hours is equal to or greater than 24
        hours = 0; // Resetting the hours to 0  
      }
    }
  }
}