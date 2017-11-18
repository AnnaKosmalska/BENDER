// connect motor controller pins to Arduino digital pins
// motor one

int in1 = 9;
int in2 = 8;
// motor two

int in3 = 7;
int in4 = 6;

int in5 = 2;
int in6 = 3;
// motor two

int in7 = 4;
int in8 = 5;

void setup()
{
  // set all the motor control pins to outputs
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(in5, OUTPUT);
  pinMode(in6, OUTPUT);
  pinMode(in7, OUTPUT);
  pinMode(in8, OUTPUT);
}
void demoOne()
{
  // this function will run the motors in both directions at a fixed speed
  // turn on motor A
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  // turn on motor B
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  digitalWrite(in5, HIGH);
  digitalWrite(in6, LOW);

  // turn on motor B
  digitalWrite(in7, HIGH);
  digitalWrite(in8, LOW);

  delay(2000);
   digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  digitalWrite(in5, LOW);
  digitalWrite(in6, LOW);  
  digitalWrite(in7, LOW);
  digitalWrite(in8, LOW);
  delay(1000);
  // now change motor directions
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
  digitalWrite(in5, LOW);
  digitalWrite(in6, HIGH);  
  digitalWrite(in7, LOW);
  digitalWrite(in8, HIGH); 
  delay(2000);
  // now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  digitalWrite(in5, LOW);
  digitalWrite(in6, LOW);  
  digitalWrite(in7, LOW);
  digitalWrite(in8, LOW);
}

void loop()
{
  demoOne();
  delay(1000);
}
