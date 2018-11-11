#include <TimerOne.h>

int latchPin = 3;
int clockPin = 4;
int dataPin = 2;

int clk = 0;
int pwmResolution = 10;
int shiftBits[] = {1,2,4,8,16,32,64,128};
int motorCommands[4]; // left - right - bleft - bright
int timerTime = 2000; //microsec
int maxSpeed = 10;

#define LEFT 160
#define RIGHT 10
#define B_LEFT 80
#define B_RIGHT 5
#define STOP 0


void pwmTimerF() {
  Serial.println(motorCommands[0]);
  clk++;
  if(clk > pwmResolution) clk =  0;
  int v = map(clk, 0, pwmResolution, 0, maxSpeed);
  
  int shiftValues = 0;
  for(int i=0; i<4; ++i) {
    if(v < motorCommands[i]) {
      if(i==0) {
        shiftValues += LEFT;
        Serial.println("left");
      }
      else if(i==1) {
        shiftValues += RIGHT;
        Serial.println("right");
      }
      else if(i==2) {
        shiftValues += B_LEFT;
        Serial.println("b left");
      }
      else if(i==3) {
        shiftValues += B_RIGHT;
        Serial.println("b right");
      }
      }
    }
  
  
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, shiftValues);
  
  digitalWrite(latchPin, HIGH);
  }

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  digitalWrite(latchPin, LOW);
  digitalWrite(dataPin, LOW);
  digitalWrite(clockPin, LOW);

  Timer1.initialize(timerTime);
  Timer1.attachInterrupt(pwmTimerF);

  Serial.begin(9600);
}

/*void forward(int speed_val) {
  motorCommands[0] = speed_val;
  motorCommands[1] = speed_val;
  motorCommands[2] = 0;
  motorCommands[3] = 0;
  }

void backwards(int speed_val) {
  motorCommands[0] = 0;
  motorCommands[1] = 0;
  motorCommands[2] = speed_val;
  motorCommands[3] = speed_val;
  }

void stop_all() {
  motorCommands[0] = 0;
  motorCommands[1] = 0;
  motorCommands[2] = 0;
  motorCommands[3] = 0;
  }*/

void loop() {
  Serial.println("            LOOOOOOOOOP          ");
  /*for(int s=0; s<maxSpeed; ++s) {
    forward(s);
    delay(100);
    }
  delay(1000);
  for(int s=maxSpeed; s>=0; --s) {
    forward(s);
    delay(100);
    }
  delay(1000);

  for(int s=0; s<maxSpeed; ++s) {
    backwards(s);
    delay(100);
    }
  delay(1000);
  for(int s=maxSpeed; s>=0; --s) {
    backwards(s);
    delay(100);
    }
  delay(1000);*/
  motorCommands[0] = 10;
  motorCommands[1] = 10;
  motorCommands[2] = 0;
  motorCommands[3] = 0;  
  delay(1000);
  motorCommands[0] = 7;
  motorCommands[1] = 0;
  motorCommands[2] = 0;
  motorCommands[3] = 0;
  delay(1000);
  /*backwards(maxSpeed/2);
  delay(1000);*/
  /*stop_all();
  delay(1000);*/
}
