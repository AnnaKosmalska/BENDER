// include the library code:
#include <LiquidCrystal.h>
#include <Wire.h>
#include "RTClib.h"
#include <Adafruit_NeoPixel.h>

RTC_DS1307 RTC;

const int rs = 6, en = 7, d4 = 2, d5 = 3, d6 = 4, d7 = 5, power = 8, led = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


int liczbadiod = 60;
Adafruit_NeoPixel leds = Adafruit_NeoPixel(liczbadiod, led, NEO_GRB + NEO_KHZ800);

struct my_button
{
  int value;
  int lastState;
  int pin;
};
struct RGB
{
  int R;
  int G;
  int B;
};


my_button Alarm = {0, HIGH, 9};
my_button Control = {0, HIGH, 10};
my_button Plus = {0, HIGH, 11};
my_button Minus = {0, HIGH, 12};

bool ok = false;

int GodzinaBudzika = 21;
int MinutaBudzika = 39;

void setup() {
  // set up the LCD's number of columns and rows:
  leds.begin();
  lcd.begin(16, 2);
  lcd.clear();
  delay(10);

  Wire.begin();
  RTC.begin();

  /*if (! RTC.isrunning())*/ {
    Serial.println("RTC is NOT running!");
    // This will reflect the time that your sketch was compiled
    //RTC.adjust(DateTime(__DATE__, __TIME__)); //arduino = komp + 56s
  }

  Serial.begin(9600);
  pinMode(power, OUTPUT);

  pinMode(Alarm.pin, INPUT_PULLUP);
  pinMode(Control.pin, INPUT_PULLUP);
  pinMode(Plus.pin, INPUT_PULLUP);
  pinMode(Minus.pin, INPUT_PULLUP);

  digitalWrite(power, HIGH);

  for (int i = 0; i < liczbadiod; i++) {
    leds.setPixelColor(i, 0, 0, 0);
  }
  leds.show();
  delay(250);

}

int wait = 0;
int mod = 0;

int AlarmState = 0;
int z = 20*60;
int trwanie = 20;
void loop() {
  
    
    
    AlarmRing (z);
    delay(1000);
    z = z - 1;
    if(z < 0) z = 0;

}


void AlarmRing(int zostalo)
{
  RGB kolor;

  kolor = Dejkolor(zostalo);
  Serial.print(kolor.B);
  Serial.print(",");
  Serial.print(kolor.R);
  Serial.print(",");
  Serial.println(kolor.G);

  for (int i = 0; i < liczbadiod; i++) {
    leds.setPixelColor(i, kolor.R, kolor.G, kolor.B);
  }
  leds.show();
  if (zostalo == 0) AlarmState = 2;


}

RGB Dejkolor(int zostalo)
{
  int liczbaPoziomow = 8;
  int granice [liczbaPoziomow + 1][3] = {
    {255,255,255},
    {255,200,150},
    {255,120,50},
    {255,70,10},
    {255, 60, 0},
    {255, 40, 10},
    {50, 0, 0},
    {25, 0, 0},
    {0, 0, 0}
  };
  RGB kolor = {granice [0][0], granice [0][1], granice [0][2]};
  if (zostalo < 0) return kolor;
  //DEFINIUJ R
  int aktualnyPoziom = int(float(zostalo * liczbaPoziomow) / float(trwanie) / 60.0);
  if (aktualnyPoziom == liczbaPoziomow) {
    aktualnyPoziom = aktualnyPoziom - 1;
  }

  float R1 = float(granice [aktualnyPoziom][0]);
  float R2 = float(granice [aktualnyPoziom + 1][0]);
  float z1 = float(aktualnyPoziom * trwanie) * 60.0 / float(liczbaPoziomow);
  float z2 = float((aktualnyPoziom + 1) * trwanie) * 60.0 / float(liczbaPoziomow);
  float zostalo_float = float(zostalo) - z1;
  z2 = z2 - z1;
  z1 = 0.0;

  float R = (R2 - R1) / (z2 - z1) * zostalo_float + R1;
  //DEFINIUJ G
  float G1 = float(granice [aktualnyPoziom][1]);
  float G2 = float(granice [aktualnyPoziom + 1][1]);

  float G = (G2 - G1) / (z2 - z1) * zostalo_float + G1;

  //DEFINIUJ B
  float Blue1 = float(granice [aktualnyPoziom][2]);
  float Blue2 = float(granice [aktualnyPoziom + 1][2]);

  float B = (Blue2 - Blue1) / (z2 - z1) * zostalo_float + Blue1;

  R = R>255.0 ? 255.0 : R;
  R = R<0.0 ? 0.0 : R;

  G = G>255.0 ? 255.0 : G;
  G = G<0.0 ? 0.0 : G;

  B = B>255.0 ? 255.0 : B;
  B = B<0.0 ? 0.0 : B;

  
  kolor = {int(R), int(G), int(B)};




  return kolor;
}





