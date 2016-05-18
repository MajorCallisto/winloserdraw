#include "Keyboard.h"

int redPin = 9;
int greenPin = 10;
int bluePin = 11;
int potPin = A0;
int val = 0;
int lastVal = 0;
int colorArray[][6] = {
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
                    {223,249,39,false,true,KEY_F3},
                   };

                   
void setup()
{
pinMode(redPin, OUTPUT);
pinMode(greenPin, OUTPUT);
pinMode(bluePin, OUTPUT);
Serial.begin(9600);
Keyboard.begin();
}
void loop()
{
//Read the potentiometer (color wheel).
val = analogRead(potPin);
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

analogWrite(redPin, redValue);
analogWrite(greenPin, greenValue);
analogWrite(bluePin, blueValue);
//delay(200);
}
