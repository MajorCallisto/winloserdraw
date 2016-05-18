/*
 Keyboard Message test

 For the Arduino Leonardo and Micro.

 Sends a text string when a button is pressed.

 The circuit:
 * pushbutton attached from pin 4 to +5V
 * 10-kilohm resistor attached from pin 4 to ground

 created 24 Oct 2011
 modified 27 Mar 2012
 by Tom Igoe
 modified 11 Nov 2013
 by Scott Fitzgerald

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/KeyboardMessage
 */

#include Keyboard.h

#define KEY_F13  0x68
#define KEY_F14 0x69
#define KEY_F15 0x6A

#define RELAY1  6
#define RELAY2  7                        
#define RELAY3  8
#define RELAY4  9

const int buttonPin = 4;          // input pin for pushbutton
int buttonState;
int previousButtonState = HIGH;   // for checking the state of a pushButton

int inputDevice = 0;

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {

  // Initialise the Arduino data pins for OUTPUT
  pinMode(RELAY1, OUTPUT);       
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);
  
  // make the pushButton pin an input:
  pinMode(buttonPin, INPUT_PULLUP);
  // initialize control over the keyboard:
  Keyboard.begin();
}

void loop() {
  // read the pushbutton:
  int buttonReading = digitalRead(buttonPin);

  // If the switch changed, due to noise or pressing:
  if (buttonReading != previousButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (buttonReading != buttonState) {
      buttonState = buttonReading;      

      // only toggle the LED if the new button state is HIGH
      if (buttonState == LOW) {
        Keyboard.press(KEY_LEFT_GUI);
        Keyboard.press(KEY_RIGHT_SHIFT);
        Keyboard.press(KEY_F3);
        delay(100);
        Keyboard.releaseAll();


        if (inputDevice == 0){
          inputDevice = 1;
        } else {
          inputDevice = 0;
        }

        digitalWrite(RELAY1,inputDevice);
        digitalWrite(RELAY2,inputDevice);
        digitalWrite(RELAY3,inputDevice);
        digitalWrite(RELAY4,inputDevice);
        
      }
    }
  }  
  
  previousButtonState = buttonReading;
}

