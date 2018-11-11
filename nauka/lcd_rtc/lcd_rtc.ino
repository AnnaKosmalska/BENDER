// include the library code:
#include <LiquidCrystal.h>
#include <Wire.h>
#include "RTClib.h"
#include <Adafruit_NeoPixel.h>

RTC_DS1307 RTC;

const int rs = 6, en = 7, d4 = 2, d5 = 3, d6 = 4, d7 = 5, power = 8, led = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int trwanie = 20;
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
float kat = 0.0;
float kat2 = 0.3;
float kat3 = 0.8;

bool ok = false;

int gasEkran = 0;

void setup() {
  // set up the LCD's number of columns and rows:
  leds.begin();
  lcd.begin(16, 2);
  lcd.clear();
  delay(100);

  Wire.begin();
  RTC.begin();

  /*if (! RTC.isrunning())*/ {
    Serial.println("RTC is NOT running!");
    // This will reflect the time that your sketch was compiled

// Hej, jol: chcesz uaktualnic date i godzine to odkomentuj linijke ponizej.
    
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

  gasEkran = 5*10;

}

int wait = 0;
int mod = 0;
int GodzinaBudzika = 7;
int MinutaBudzika = 20;
int AlarmState = 0;

void loop() {
  DateTime now = RTC.now();
  //digitalWrite(power, HIGH);

  print_lcd(now);
  int a = CheckButton();
  Menu(a);

  if (Alarm.value == 1)
  {
    CheckAlarm(now.hour(), now.minute(), now.second());
  }
  else AlarmState = 0;

  if (Alarm.value == 3)
  {
    Wonsz();
  }
    if (Alarm.value == 2)
  {
    Atmosfera();
  }

  if (AlarmState == 1 || AlarmState == 2)
  {
    AlarmRing (now.minute(), now.second());
  }
  delay(100);

  gasEkran = gasEkran<=0 ? 0 : gasEkran - 1;
  if(gasEkran == 1)
  {
    mod = 0;
    digitalWrite(power, LOW);
    lcd.clear();
  }
  
  if(gasEkran >1 ) digitalWrite(power, HIGH);


}

void print_lcd(DateTime now)
{
  if (mod == 0)
  {
    if (wait == 0)
    {
      //Serial.println(now.dayOfWeek()); //wyświetla na podglądzie (serial monitor)
      lcd.setCursor(0, 0);
      if (now.day() < 10)
      {
        String h = String(now.day());
        lcd.print("0" + h);
      }
      else lcd.print(now.day());
      lcd.print(".");
      if (now.month() < 10)
      {
        String h = String(now.month());
        lcd.print("0" + h);
      }
      else lcd.print(now.month());
      lcd.print(".");
      lcd.print(now.year());

      lcd.setCursor(12, 0);
      lcd.print("    ");
      lcd.setCursor(11, 0);
      lcd.print("(");
      switch (now.dayOfWeek())
      {
        case 0:
          lcd.print("nd");
          break;
        case 1:
          lcd.print("pon");
          break;
        case 2:
          lcd.print("wto");
          break;
        case 3:
          lcd.print("sr");
          break;
        case 4:
          lcd.print("czw");
          break;
        case 5:
          lcd.print("pt");
          break;
        case 6:
          lcd.print("sob");
          break;

      }
      lcd.print(")");

      lcd.setCursor(0, 1);
      if (now.hour() < 10)
      {
        String h = String(now.hour());
        lcd.print("0" + h);
      }
      else lcd.print(now.hour());
      lcd.print(":");
      if (now.minute() < 10)
      {
        String h = String(now.minute());
        lcd.print("0" + h);
      }
      else lcd.print(now.minute());
      lcd.print(":");

      if (now.second() < 10)
      {
        String h = String(now.second());
        lcd.print("0" + h);
      }
      else lcd.print(now.second());
    }

  }
  if (mod == 1)
  {
    lcd.setCursor(0, 0);
    lcd.print("USTAW BUDZIK");
    lcd.setCursor(0, 1);
    if (wait < 5)
    {
      if (GodzinaBudzika < 10)
      {
        lcd.print("0");
      }

      lcd.print(GodzinaBudzika);
    }
    else lcd.print("  ");
    lcd.print(":");
    if (MinutaBudzika < 10)
    {
      lcd.print("0");
    }
    lcd.print(MinutaBudzika);

  }

  if (mod == 2)
  {
    lcd.setCursor(0, 0);
    lcd.print("USTAW BUDZIK");
    lcd.setCursor(0, 1);

    if (GodzinaBudzika < 10)
    {
      lcd.print("0");
    }
    lcd.print(GodzinaBudzika);
    lcd.print(":");

    if (wait < 5)
    {
      if (MinutaBudzika < 10)
      {
        lcd.print("0");
      }
      lcd.print(MinutaBudzika);
    }
    else lcd.print("  ");

  }
  wait++;
  if (wait == 10) wait = 0;
}
void CheckAlarm(int godzinaTeraz, int minutaTeraz, int sekundaTeraz)
{
  int minutaLokalna = MinutaBudzika;
  int godzinaLokalna = GodzinaBudzika;
  if (MinutaBudzika < trwanie)
  {
    minutaLokalna = 60 - trwanie + MinutaBudzika;
    godzinaLokalna--;
  }
  else minutaLokalna = MinutaBudzika - trwanie;
  if (godzinaLokalna == godzinaTeraz && minutaLokalna == minutaTeraz && sekundaTeraz < 10)
  {
    AlarmState = 1;
  }
}
void AlarmRing(int minutaTeraz, int sekundaTeraz)
{
  RGB kolor;
  int zostalo = -1;
  if (AlarmState == 1)
  {
    zostalo = MinutaBudzika * 60 - (minutaTeraz * 60 + sekundaTeraz);
    if (zostalo < 0)
    {
      zostalo = zostalo + (60 * 60);
    }
  }

  kolor = Dejkolor(zostalo);
  Serial.print(kolor.R);
  Serial.print(",");
  Serial.print(kolor.G);
  Serial.print(",");
  Serial.println(kolor.B);

  for (int i = 0; i < liczbadiod; i++) {
    leds.setPixelColor(i, kolor.R, kolor.G, kolor.B);
  }
  leds.show();
  if (zostalo == 0) AlarmState = 2;


}
int CheckButton()
{
  int lastStateA = Alarm.lastState;
  int lastStateC = Control.lastState;
  int lastStateP = Plus.lastState;
  int lastStateM = Minus.lastState;
  int stateA = digitalRead(Alarm.pin);
  int stateC = digitalRead(Control.pin);
  int stateP = digitalRead(Plus.pin);
  int stateM = digitalRead(Minus.pin);
  Alarm.lastState = stateA;
  Control.lastState = stateC;
  Plus.lastState = stateP;
  Minus.lastState = stateM;

  if (lastStateA == HIGH && stateA == LOW)
  {
    return 1;
  }

  if (lastStateC == HIGH && stateC == LOW)
  {
    return 2;
  }

  if (lastStateP == HIGH && stateP == LOW)
  {
    return 3;
  }

  if (lastStateM == HIGH && stateM == LOW)
  {
    return 4;
  }
  return 0;
}

void Menu (int Button)
{
  if(Button != 0) gasEkran = 5*10;
  
  if (Button == 1)
  {
    if (AlarmState == 1 || AlarmState == 2)
    {
      AlarmState = 0;
      for (int i = 0; i < liczbadiod; i++) {
        leds.setPixelColor(i, 0, 0, 0);
      }
      leds.show();
    }
    else
    {
      Alarm.value = ++Alarm.value;
      if (Alarm.value == 3)
      {
        delay (250);
      }
    }
    if (Alarm.value == 4) {
      Alarm.value = 0;
      for (int i = 0; i < liczbadiod; i++) {
        leds.setPixelColor(i, 0, 0, 0);
      }
      leds.show();
    }
  }

  if (Alarm.value == 1 && mod == 0)
  {
    lcd.setCursor(9, 1);
    lcd.print("(A)");
  }
  else if (Alarm.value == 2 && mod == 0)
  {
    lcd.setCursor(9, 1);
    lcd.print("(S)");
  }
  else if (Alarm.value == 3 && mod == 0)
  {
    lcd.setCursor(9, 1);
    lcd.print("(P)");
  }
  else if (Alarm.value == 0 && mod == 0)
  {
    lcd.setCursor(9, 1);
    lcd.print("     ");
  }

  if (Button == 2)
  {
    if (mod == 2)
    {
      mod = 0;
      Alarm.value = 1;
      lcd.clear();
    }
    else if (mod == 1)
    {
      mod = 2;
    }
    else if (mod == 0)
    {
      mod = 1;
      lcd.clear();
    }
  }
  if (Button == 3 && mod == 1)
  {
    GodzinaBudzika++;
    if (GodzinaBudzika > 23)
    {
      GodzinaBudzika = 0;
    }
  }
  if (Button == 3 && mod == 2)
  {
    MinutaBudzika++;
    if (MinutaBudzika > 59)
    {
      MinutaBudzika = 0;
      GodzinaBudzika++;
      if (GodzinaBudzika > 23)
      {
        GodzinaBudzika = 0;
      }
    }
  }
  if (Button == 4 && mod == 1)
  {
    GodzinaBudzika--;
    if (GodzinaBudzika < 0)
    {
      GodzinaBudzika = 23;
    }
  }
  if (Button == 4 && mod == 2)
  {
    MinutaBudzika--;
    if (MinutaBudzika < 0)
    {
      MinutaBudzika = 59;
      GodzinaBudzika--;
      if (GodzinaBudzika < 0)
      {
        GodzinaBudzika = 23;
      }

    }
  }
}
RGB Dejkolor(int zostalo)
{
  int liczbaPoziomow = 8;
  int granice [liczbaPoziomow + 1][3] = {
    {255, 255, 255},
    {255, 200, 150},
    {255, 120, 50},
    {255, 70, 10},
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

  R = R > 255.0 ? 255.0 : R;
  R = R < 0.0 ? 0.0 : R;

  G = G > 255.0 ? 255.0 : G;
  G = G < 0.0 ? 0.0 : G;

  B = B > 255.0 ? 255.0 : B;
  B = B < 0.0 ? 0.0 : B;


  kolor = {int(R), int(G), int(B)};




  return kolor;
}

void Wonsz ()
{
  kat = kat + 2 * 3.14 / 32;
  if (kat > 2 * 3.14)
  {
    kat = 0;
  }
  kat2 = kat2 + 2 * 3.14 / 40;
  if (kat2 > 2 * 3.14)
  {
    kat2 = kat2 - 2 * 3.14;
  }

  kat3 = kat3 + 2 * 3.14 / 48;
  if (kat3 > 2 * 3.14)
  {
    kat3 = kat3 - 2 * 3.14;
  }

  for (int i = 0; i < liczbadiod; ++i)
  {

    int R = (sin(kat + 0.1 * i) + 1.0) / 2.0 * 255.0;
    int G = (sin(kat2 + 0.1 * i) + 1.0) / 2.0 * 255.0;
    int B = (sin(kat3 + 0.1 * i) + 1.0) / 2.0 * 255.0;
    leds.setPixelColor(i, R, G, B); // Dioda "i" oraz skladowe R=255 G=0 B=0
  }
  leds.show(); // Wysylamy dane do lancucha
}

void Atmosfera()
{
    for (int i = 0; i < liczbadiod; ++i)
  {
    int R = 255;
    int G = 40;
    int B = 10;
    leds.setPixelColor(i, R, G, B); // Dioda "i" oraz skladowe R=255 G=0 B=0
  }
  leds.show(); // Wysylamy dane do lancucha
}






