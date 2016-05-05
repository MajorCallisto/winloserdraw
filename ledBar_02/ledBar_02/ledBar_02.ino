int latchPin = 8;
int dataPin = 11;
int clockPin = 12;
 
byte leds = 0;

int ledState[40];

void setup() 
{
  int i;
  for (i = 0; i < sizeof(ledState); i = i + 1) {
    ledState[i] = 0;
  }
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  led_off_all();
}
void loop() 
{
  int i; 
  /*
  led_on_all();
  led_update();
  delay(1000);
  led_off_all();
  led_update();
  delay(1000);
   
    led_on(7);
    led_update();
    delay(100);  
    led_off(7);
    led_update();
    delay(100);
    led_on(7);
    led_update();
    delay(100);  
    led_off(7);
    led_update();
    delay(100);
    
  for (i = 0; i < 9; i++){  
    led_on(i);
    led_update();
    delay(500);  
    led_off(i);
    led_update();
    delay(500);
  }

  led_on_all();
    led_update();
    delay(1000);
 */
  for (i = 0; i < 40; i++){  
    led_on(i);
    led_update();
    delay(100);
    led_off(i);
    led_update();
    delay(100);
  }
  /**/
  //fill_up(9);
  /*
  led_on(0);
  led_update();
  delay(1000);
  led_off_all();
  led_update();
*/
}
void fill_up(int number){
  int i;
  for (i = number-1; i > -1; i--){
    led_on(i);
    led_update();
    delay(25);
  }
}
void led_on (int ledIndex){
    ledState[ledIndex] = 1;
}
void led_off (int ledIndex){
    ledState[ledIndex] = 0;
}
void led_on_all(){
  int i;
  for (i = 0; i < sizeof(ledState); i = i + 1) {
    ledState[i] = 1;
  }
}
void led_off_all(){
  int i;
  for (i = 0; i < sizeof(ledState); i = i + 1) {
    ledState[i] = 0;
  }
}
void led_update(){
  leds = 0;
  int i;
  for (i = 0; i < sizeof(ledState); i = i + 1) {
    if (ledState[i] == 1){
      bitSet(leds, i);
    }
  }
  updateShiftRegister();
}
void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   digitalWrite(latchPin, HIGH);
}
