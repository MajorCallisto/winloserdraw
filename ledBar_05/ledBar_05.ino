//Modified ShiftOutX library
//http://playground.arduino.cc/Main/ShiftOutX#Download
//Remarked out ShiftOutX.h lines 109 and 110

#include <ShiftOutX.h>
#include <ShiftPinNo.h> 

int latchPin = 3;
int dataPin = 11;
int clockPin = 12;

shiftOutX regOne(latchPin, dataPin, clockPin, MSBFIRST, 5); 

unsigned long previousMillis = 0;
const long interval = 500;

boolean playerTurnA = false;
int secondsElapsed = 0;
void setup() {
  //Serial.begin(9600);
  //Setup Lights
  previousMillis = millis();
  regOne.allOn();
}

boolean player_00Active = true;
int activeLight = 1;
void loop() {
  updateLight();
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

