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
int pot2Pin = A1;

int val = 0;
int lastVal = 0;

int currentPlayer = 1;

unsigned long previousMillis = 0;
const long interval = 5000; 

int colorArray[][6] = {    // colors for the color selector
                    {255,255,255,false,false,KEY_F1},  //color1
                    {0,255,255,false,false,KEY_F2},  //color2
                    {127,127,127,false,false,KEY_F3},  //color3
                    {255,157,22,false,false,KEY_F4},  //color4
                    {255,117,15,false,false,KEY_F5},  //color5
                    {255,75,10,false,false,KEY_F6},   //color6
                    {255,0,0,false,false,KEY_F7},    //color7
                    {0,255,0,false,false,KEY_F8},  //color8
                    {0,0,255,false,false,KEY_F9}, //color9
                    
                    {255,37,135,true,false,KEY_F1},   
                    {255,31,163,true,false,KEY_F2},
                    {255,29,192,true,false,KEY_F3},
                    {250,32,253,true,false,KEY_F4},
                    {225,32,252,true,false,KEY_F5},
                    {196,33,253,true,false,KEY_F6},
                    {165,34,253,true,false,KEY_F7},
                    {141,34,253,true,false,KEY_F8},
                    {99,34,254,true,false,KEY_F9},
                    {0,35,252,true,false,KEY_F10},
                    {0,76,253,true,false,KEY_F11},
                    {0,102,253,true,false,KEY_F12},

                    {8,134,254,true,true,KEY_F1},
                    {28,176,253,true,true,KEY_F2},
                    {43,219,255,true,true,KEY_F3},
                    {55,255,255,true,true,KEY_F4},
                    {57,255,218,true,true,KEY_F5},
                    {57,254,178,true,true,KEY_F6},
                    {59,254,147,true,true,KEY_F7},
                    {60,254,120,true,true,KEY_F8},
                    {60,254,94,true,true,KEY_F9},
                    {60,253,39,true,true,KEY_F10},
                    {112,253,39,true,true,KEY_F11},
                    {157,254,39,true,true,KEY_F12},
                    
                    {192,254,40,false,true,KEY_F1},
                    {208,252,39,false,true,KEY_F2},
                    {223,249,39,false,true,KEY_F3}                    
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
  
  Serial.begin(9600);
  Keyboard.begin();

  
  //Serial.begin(9600);
  //Setup Lights
  previousMillis = millis();
  regOne.allOn();
}
 
 void loop()
{
  unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      switchPlayers();
    }

  val = (currentPlayer == 1) ? analogRead(potPin) : analogRead(pot2Pin);
  
  int mappedVal = map(val, 0, 1022, 0, 35);
  
  if (mappedVal == lastVal) return;
  Serial.println("+++++++++++++++++++++");
  Serial.println(val);
  Serial.println(mappedVal);
  lastVal = mappedVal;
  
  if (colorArray[mappedVal][3] == 1){
    Keyboard.press(KEY_LEFT_GUI);
  }
  if (colorArray[mappedVal][4] == 1){
    Keyboard.press(KEY_LEFT_SHIFT);
  }
  Keyboard.press(colorArray[mappedVal][5]);
  
  delay(100);
  Keyboard.releaseAll();
  
  int redValue = colorArray[mappedVal][0];
  int greenValue = colorArray[mappedVal][1];
  int blueValue = colorArray[mappedVal][2];
  
  Serial.print(redValue);
  Serial.print(", ");
  Serial.print(greenValue);
  Serial.print(", ");
  Serial.print(blueValue);

  int currentPlayerPixel =  (currentPlayer == 1) ? 0 : 1;
  pixels.setPixelColor(currentPlayerPixel, pixels.Color(redValue,greenValue,blueValue));
  pixels.show();
  
  updateLight();
}

void switchPlayers(){
  currentPlayer = (currentPlayer == 1) ? 2 : 1;
    if (currentPlayer == 1){
    digitalWrite(RELAY1,LOW);           // Turns ON Relays 1
    digitalWrite(RELAY2,LOW);           // Turns ON Relays 2
    digitalWrite(RELAY3,LOW);           // Turns ON Relays 3
    digitalWrite(RELAY4,LOW);           // Turns ON Relays 4    
  }
  if (currentPlayer == 2){
    digitalWrite(RELAY1,HIGH);          // Turns Relay Off
    digitalWrite(RELAY2,HIGH);          // Turns Relay Off
    digitalWrite(RELAY3,HIGH);          // Turns Relay Off
    digitalWrite(RELAY4,HIGH);          // Turns Relay Off 
  }
        pixels.setPixelColor(0, pixels.Color(0,0,0));
        pixels.setPixelColor(1, pixels.Color(0,0,0));
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
}

