#include <Adafruit_NeoPixel.h>

#define PIN 13
#define LICZBADIOD 60

float kat = 0.0;
float kat2 = 0.3;
float kat3 = 0.8;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(LICZBADIOD, PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  pixels.begin(); // Inicjalizacja biblioteki
  Serial.begin(9600);

  for (int i = 0; i < LICZBADIOD; i++)
  {
    pixels.setPixelColor(i, 0,0,0); // Dioda "i" oraz skladowe R=255 G=0 B=0
  }
  //pixels.setPixelColor(59, 255,0,0); 
  pixels.show(); // Wysylamy dane do lancucha
}

void loop()
{
   for (int i = 0; i < LICZBADIOD; i++)
  {
    pixels.setPixelColor(i, 255,255,255); // Dioda "i" oraz skladowe R=255 G=0 B=0
  }
  //pixels.setPixelColor(59, 255,0,0); 
  pixels.show(); // Wysylamy dane do lancucha

  delay(500);

}



