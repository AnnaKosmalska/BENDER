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
    pixels.setPixelColor(i, 255,100,0); // Dioda "i" oraz skladowe R=255 G=0 B=0
  }
  //pixels.setPixelColor(59, 255,0,0); 
  pixels.show(); // Wysylamy dane do lancucha
}

void loop()
{
  kat = kat + 2 * 3.14 / 20;
  if (kat > 2 * 3.14)
  {
    kat = 0;
  }
  kat2 = kat2 + 2 * 3.14 / 24;
  if (kat2 > 2 * 3.14)
  {
    kat2 = kat2 - 2 * 3.14;
  }

  kat3 = kat3 + 2 * 3.14 / 16;
  if (kat3 > 2 * 3.14)
  {
    kat3 = kat3 - 2 * 3.14;
  }

//for (int i = 0; i < LICZBADIOD; i++)
  {
    //pixels.setPixelColor(i, 255,100,0); // Dioda "i" oraz skladowe R=255 G=0 B=0
  }//
  //pixels.setPixelColor(59, 255,0,0); 
  //pixels.show(); // Wysylamy dane do lancucha
  //delay(500);

  int R = (sin(kat) + 1.0) / 2.0 * 255.0;
  int G = (sin(kat2) + 1.0) / 2.0 * 255.0;
  int B = (sin(kat3) + 1.0) / 2.0 * 255.0;

  Serial.print(B);      //the first variable for plotting
  Serial.print(" ");              //seperator
  Serial.print(G);
  Serial.print(" ");
  Serial.println(R);

  for (int i = 0; i < LICZBADIOD; ++i)
  {
    //R = 255;
    //G = 0;
    //B = 0;
    int R = (sin(kat+0.1*i) + 1.0) / 2.0 * 255.0;
    int G = (sin(kat2+0.1*i) + 1.0) / 2.0 * 255.0;
    int B = (sin(kat3+0.1*i) + 1.0) / 2.0 * 255.0;
    pixels.setPixelColor(i, R, G, B); // Dioda "i" oraz skladowe R=255 G=0 B=0
  }
  pixels.show(); // Wysylamy dane do lancucha
  delay(100);
  //


  // for (int R=0;R<255;R=R+10)
  // {
  //   for (int G=0;G<255;G=G+10)
  //   {
  //    for (int B=0;B<255;B=B+10)
  //    {
  //          pixels.setPixelColor(0, R, G, B); // Dioda "i" oraz skladowe R=255 G=0 B=0
  //          pixels.show(); // Wysylamy dane do lancucha
  //          delay(10);
  //    }
  //   }
  // }


}



