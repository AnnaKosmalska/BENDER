#include <TimerOne.h>

int TIMER_DELAY = 300;
int ticker = 0;

//Pin connected to ST_CP of 74HC595
int latchPin = 10;
//Pin connected to SH_CP of 74HC595
int clockPin = 13;
////Pin connected to DS of 74HC595
int dataPin = 11;

int player1_pin = 8;
int player2_pin = 7;

int latchPinPORTB = latchPin - 8;

int pwmPins[8];
int leds[] = {1,2,4,8,16,32,64,128};

//--- Direct port access latching
void latchOn(){
 bitSet(PORTB,latchPinPORTB);
}
void latchOff(){
 bitClear(PORTB,latchPinPORTB);
}

void setupSPI() {
  byte clr;  
  SPCR |= ( (1<<SPE) | (1<<MSTR) ); // enable SPI as master
  SPCR &= ~( (1<<SPR1) | (1<<SPR0) ); // clear prescaler bits
  clr=SPSR; // clear SPI status reg
  clr=SPDR; // clear SPI data reg
  SPSR |= (1<<SPI2X); // set prescaler bits
  delay(10);
  }

//--- The really fast SPI version of shiftOut
byte spi_transfer(byte data)
{
 SPDR = data;                    // Start the transmission
 loop_until_bit_is_set(SPSR, SPIF);
 return SPDR;                    // return the received byte, we don't need that
}

void iProcess() {
  ticker++;
  if(ticker>30) ticker = 0;
  int value = map(ticker, 0, 30, 0, 255);
  int toWrite = 0;
  for(int i=0; i<8; i++) {
    if(value < pwmPins[i]) toWrite += leds[i];
    }
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST,toWrite);
  digitalWrite(latchPin, HIGH);
  //latchOn();

    
  }

void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  digitalWrite(latchPin, LOW);
  digitalWrite(dataPin, LOW);
  digitalWrite(clockPin, LOW);

  //setupSPI();

  Timer1.initialize(300);
  Timer1.attachInterrupt(iProcess);

  Serial.begin(9600);
}
int sincounter = 0;


void loop() {

  sincounter = (sincounter+1)%360;

  
  double angle = sincounter*2*3.14/360;
  double sinval = sin(angle);
  int val = (sinval+1)/2*255;
  Serial.println(val);

  for(int j=0; j<8; j++) {
    val = (sin(angle+j*3.14/4)+1)/2*255;
    pwmPins[j] = val;
    }
/*
  
  for(int i=0; i<256; i+=10) {
    for(int j=0; j<8; j++) {
      pwmPins[j] = i;
      }
      delay(10);
    }

  for(int i=255; i>=0; i-=10) {
    for(int j=0; j<8; j++) {
      pwmPins[j] = i;
      }
      delay(10);
    }*/
    delay(5);
}
