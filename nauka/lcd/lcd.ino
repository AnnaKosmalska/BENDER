// include the library code:
#include <LiquidCrystal.h>


// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.clear();
  delay(10);
  // Print a message to the LCD.
  lcd.print("sex dzisiaj?");
  
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  int t = 10-(millis() / 1000);
  if(t>0){
  lcd.setCursor(0, 1);
  lcd.print("za");
  // print the number of seconds since reset:
  lcd.setCursor(3, 1);
  
  if(t == 999) {
    lcd.setCursor(6, 1);
    lcd.print(" ");
    }
  if(t == 99) {
    lcd.setCursor(5, 1);
    lcd.print(" ");
    }
  if(t == 9) {
    lcd.setCursor(4, 1);
    lcd.print(" ");
    }
  lcd.setCursor(3, 1);
  lcd.print(t);
  }
  else{
   lcd.setCursor(0, 1);
   lcd.print("TERAZ!!");
   delay(500);
   lcd.setCursor(0, 1);
   lcd.print("        ");
   delay(500);
  }
  // lcd.setCursor(8, 1);
  //lcd.print("sekund");
  
}
