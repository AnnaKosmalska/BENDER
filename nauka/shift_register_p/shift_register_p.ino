
//Pin connected to ST_CP of 74HC595
int latchPin = 4;
//Pin connected to SH_CP of 74HC595
int clockPin = 2;
////Pin connected to DS of 74HC595
int dataPin = 9;

int p_pin = A0;
byte out[9];

void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  out[0] = 0b00000000;
  out[1] = 0b00000001;
  out[2] = 0b00000011;
  out[3] = 0b00000111;
  out[4] = 0b00001111;
  out[5] = 0b00011111;
  out[6] = 0b00111111;
  out[7] = 0b01111111;
  out[8] = 0b11111111;
  digitalWrite(latchPin, HIGH);
}

void loop() {

  int p = analogRead(p_pin);
  Serial.println(p);

  int zapal = map(p, 0, 1024, 0, 9);

  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, out[zapal]);
  digitalWrite(latchPin, HIGH);
  delay(10);
  
  
  
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
