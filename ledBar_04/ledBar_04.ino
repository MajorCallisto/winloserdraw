//Modified ShiftOutX library
//http://playground.arduino.cc/Main/ShiftOutX#Download
//Remarked out ShiftOutX.h lines 109 and 110

#include <ShiftOutX.h>
#include <ShiftPinNo.h> 

int latchPin = 8;
int dataPin = 11;
int clockPin = 12;

shiftOutX regOne(latchPin, dataPin, clockPin, MSBFIRST, 5); 

unsigned long previousMillis = 0;
const long interval = 500;

boolean playerTurnA = false;
int secondsElapsed = 0;
void setup() {
  Serial.begin(9600);
  previousMillis = millis();
   regOne.allOn();
}

boolean player_00Active = true;
int activeLight = 1;
void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (player_00Active){
        regOne.pinOff(activeLight);
    }else{
     regOne.pinOff(activeLight+20);
    }
    activeLight ++;
    if (activeLight == 21){
      activeLight = 1;
      regOne.allOn();
      player_00Active = !player_00Active;
    }
    Serial.println(activeLight);
  }
  return;
regOne.allOff();
for (int i = 1; i <41; i++){
        //if (random(2) <1){
            regOne.pinOn(i);
         //}
         delay(50);
}
delay(100);
for (int i = 41; i >0; i--){
        //if (random(2) <1){
            regOne.pinOff(i);
         //}
         delay(50);
}
 delay(50);
return;
/*
for (int i = 20; i >0; i--){
        regOne.pinOff(i);
        delay(20);
}
for (int i = 20; i >0; i--){
        regOne.pinOff(i);
        delay(20);
}
for (int i = 1; i <21; i++){
        regOne.pinOn(i);
        delay(20);
}
return;
*/

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (playerTurnA == true){
      regOne.pinOff(20-secondsElapsed);
    }else{
      regOne.pinOff(40-secondsElapsed);
    }
    if (secondsElapsed >20){
      secondsElapsed = 0;
      regOne.allOff();
      playerTurnA *= -1;
      changePlayer();
      for (int i=0; i<20; i++){
        if (playerTurnA){
          regOne.pinOn(i);
        }else{
          regOne.pinOn(i+20);
        }
      }
    }else{
      secondsElapsed --;
    } 
  }
}
void changePlayer(){
//Add functionality for shortcut keys

}

