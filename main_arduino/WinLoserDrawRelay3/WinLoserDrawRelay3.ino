#include <Keyboard.h>

//Modified ShiftOutX library
//http://playground.arduino.cc/Main/ShiftOutX#Download
//Remarked out ShiftOutX.h lines 109 and 110

#include <ShiftOutX.h>
#include <ShiftPinNo.h> 
#include <Adafruit_NeoPixel.h>
//
int latchPin = 3;
int dataPin = 11;
int clockPin = 12;

// Basic 4 Realy board connection
// Each relay is turned on for 2 seconds and then off.
// You can here them click as there state changes from off to on and on to
// off.
// You will also see the corresponding Red LED on the 4 Relay board
// light up when the relay is on.
 
 //  define names for the 4 Digital pins On the Arduino 7,8,9,10
 //  These data pins link to 4 Relay board pins IN1, IN2, IN3, IN4
#define RELAY1  6
#define RELAY2  7                        
#define RELAY3  8
#define RELAY4  9

// NeoPixel
int COLOR_DIAL_PIN = 5;
#define NUMPIXELS 2

shiftOutX regOne(latchPin, dataPin, clockPin, MSBFIRST, 5); 

unsigned long previousMillis = 0;
const long interval = 500;
boolean player_00Active = true;
int activeLight = 1;

boolean playerTurnA = false;
int secondsElapsed = 0;

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, COLOR_DIAL_PIN, NEO_GRB + NEO_KHZ800);

int potPin = A0;
int pot2Pin = A5;

int val = 0;
int lastVal = 0;

int colorArray[][6] = {    // colors for the color selector
                    {255,255,255,true,false,KEY_F2},  //color1  // white
                    {128,128,128,false,false,KEY_F3},  //color2       // grey
                    {0,255,0,false,false,KEY_F4},  //color3      // green
                    {0,0,255,false,false,KEY_F5},  //color4       // blue
                    {255,255,0,false,false,KEY_F6},  //color5     // yellow
                    {255,0,255,false,false,KEY_F7},   //color6    // magenta
                    {0,255,255,false,false,KEY_F8},    //color7   // cyan
                    {255,128,0,false,false,KEY_F9},  //color8     // orange
                    {255,0,0,false,false,KEY_F10},   //color9         // red
                    {255,0,0,false,false,KEY_F10}   //color9         // red
                   };
 
void setup()
{
  pixels.begin(); // This initializes the NeoPixel library.
  
  previousMillis = millis();
  // pins for relays to control the Wacom tablets.
  pinMode(RELAY1, OUTPUT);       
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);

  pinMode(potPin, INPUT);
  pinMode(pot2Pin, INPUT);
  
  Serial.begin(9600);
  Keyboard.begin();

  
  //Serial.begin(9600);
  //Setup Lights
  previousMillis = millis();
  regOne.allOn();
  delay(1000);
  regOne.allOff();
  delay(1000);
  regOne.allOn();
  delay(1000);
  regOne.allOff();
  delay(1000);
  regOne.allOn();
}
 
 void loop()
{
  updateLight();
  updateNeoPixel(false);
}
void updateNeoPixel(boolean forceUpdate){
  //set the inactive pixel to "off"
  pixels.setPixelColor((player_00Active == true) ? 0 : 1, pixels.Color(0,0,0 ));
  pixels.show();
  
  val = (player_00Active == true) ? analogRead(potPin) : analogRead(pot2Pin);
  int mappedVal = map(val, 0, 1023, 0, 9);
  
  if (mappedVal == lastVal && forceUpdate == false) return;
  Serial.println("+++++++++++++++++++++");
  Serial.println(val);
  Serial.println(mappedVal);
  lastVal = mappedVal;
  
  if (colorArray[mappedVal][3] == 1){
    Keyboard.press(KEY_LEFT_ALT);
  }//
  if (colorArray[mappedVal][4] == 1){
    Keyboard.press(KEY_LEFT_SHIFT);
  }
  Keyboard.press(colorArray[mappedVal][5]);
  
//  delay(100);
  Keyboard.releaseAll();
  
  int redValue = colorArray[mappedVal][0];
  int greenValue = colorArray[mappedVal][1];
  int blueValue = colorArray[mappedVal][2];
  
  Serial.print(redValue);
  Serial.print(", ");
  Serial.print(greenValue);
  Serial.print(", ");
  Serial.print(blueValue);

  // set the active pixel colour.
  pixels.setPixelColor((player_00Active == true) ? 1 : 0, pixels.Color(redValue,greenValue,blueValue));
  pixels.show();
}
void updateLight(){
  
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (player_00Active){
     regOne.pinOff(activeLight);
    }else{
     regOne.pinOff(activeLight+20);
    }
    activeLight ++;
    if (activeLight == 22){
      changePlayer();
    }
  }
}
void changePlayer(){
      //Update Lights
      activeLight = 1;
      regOne.allOn();
      player_00Active = !player_00Active;

      if (player_00Active == true){
        digitalWrite(RELAY1,LOW);           // Turns ON Relays 1
        digitalWrite(RELAY2,LOW);           // Turns ON Relays 2
        digitalWrite(RELAY3,LOW);           // Turns ON Relays 3
        digitalWrite(RELAY4,LOW);           // Turns ON Relays 4    
      }else{
        digitalWrite(RELAY1,HIGH);          // Turns Relay Off
        digitalWrite(RELAY2,HIGH);          // Turns Relay Off
        digitalWrite(RELAY3,HIGH);          // Turns Relay Off
        digitalWrite(RELAY4,HIGH);          // Turns Relay Off 
      }
      delay(100);
      pixels.setPixelColor(0, pixels.Color(0,0,0)); 
      pixels.setPixelColor(1, pixels.Color(0,0,0));
      pixels.show();
      delay(100);
      updateNeoPixel(true);
      delay(100);
}

