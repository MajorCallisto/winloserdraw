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
const long interval = 1000;

boolean playerTurnA = false;
int secondsElapsed = 0;
void setup() {
//Serial.begin(9600);
}

void loop() {
  /*
regOne.allOff();
for (int i = 0; i <21; i++){
        if (random(2) <1){
            regOne.pinOn(i);
         }
}
 delay(50);
return;
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
  unsigned long currentMillis = millis();

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

