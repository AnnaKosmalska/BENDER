
//Pin connected to ST_CP of 74HC595
int latchPin = 4;
//Pin connected to SH_CP of 74HC595
int clockPin = 2;
////Pin connected to DS of 74HC595
int dataPin = 9;

int buttonPin = 7;

int cc = 1915;
int b = 1700;
int a = 1519;
int g = 1432;
int f = 1275;
int e = 1136;
int d = 1014;
int c = 956;

int p_pin = A0;
byte out[9];

bool light;
bool off;
void setup() {
  noTone(13);
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  pinMode(buttonPin, INPUT);

  light = false;
  off = true;

  out[0] = 0b00000000;
  out[1] = 0b00000001;
  out[2] = 0b00000011;
  out[3] = 0b00000111;
  out[4] = 0b00001111;
  out[5] = 0b00011111;
  out[6] = 0b00111111;
  out[7] = 0b01111111;
  out[8] = 0b11111111;
  digitalWrite(latchPin, LOW);
}

void loop() {

  if(digitalRead(buttonPin) == HIGH) {
    light = !light;
    delay(500);
  }

  if(light) {
  
    int p = analogRead(p_pin);
    Serial.println(p);
  
    int zapal = map(p, 0, 1024, 0, 9);
  
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, out[zapal]);
    digitalWrite(latchPin, HIGH);
    delay(1);
    off = false;

    if(zapal == 8) {
      tone(13,g);
      delay(500);
      tone(13,e);
      delay(500);
      tone(13,e);
      delay(500);
      tone(13,f);
      delay(500);
      tone(13,d);
      delay(500);
      tone(13,d);
      delay(500);
      tone(13,c);
      delay(500);
      tone(13,e);
      delay(500);
      tone(13,g);
      delay(500);
      noTone(13);
      delay(500);
      tone(13,g);
      delay(500);
      tone(13,e);
      delay(500);
      tone(13,e);
      delay(500);
      tone(13,f);
      delay(500);
      tone(13,d);
      delay(500);
      tone(13,d);
      delay(500);
      tone(13,c);
      delay(500);
      tone(13,e);
      delay(500);
      tone(13,c);
      delay(500);
      noTone(13);
      delay(500);
      }
  }
  else if(off == false){
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, out[0]);
    digitalWrite(latchPin, HIGH);
    off = true;
    }
  
  
  
  // count from 0 to 255 and display the number 
  // on the LEDs
  /*for (int numberToDisplay = 0; numberToDisplay < 256; numberToDisplay++) {
    // take the latchPin low so 
    // the LEDs don't change while you're sending in bits:
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    shiftOut(dataPin, clockPin, MSBFIRST, numberToDisplay);  

    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
    // pause before next value:*/
    
}
