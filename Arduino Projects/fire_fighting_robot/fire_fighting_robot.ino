
#define in1 5
#define in2 6
#define in3 7
#define in4 8
#define EN_A 9
#define EN_B 10

const int flameSensorR = 2;
const int flameSensorL = 3;
const int pumpRelay = 4;
//const int Buzz = 9;
char command; // stores incoming Bluetooth data
void setup() {
  Serial.begin(9600);
  pinMode(flameSensorR, INPUT);
  pinMode(flameSensorL, INPUT);
 
  pinMode(pumpRelay, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(EN_A, OUTPUT);
  pinMode(EN_B, OUTPUT);
//  pinMode(Buzz, OUTPUT);
 
}

void loop() {

if (Serial.available()) {
    command = Serial.read();
    Serial.println(command); // for debugging

    switch (command)
     {
      case 'F': forward(); break;
      case 'B': Backward(); break;
      case 'L': Left(); break;
      case 'R': Right(); break;
      case 'S': stopp(); break;

    }
  }
  if((digitalRead(flameSensorR) == LOW) || (digitalRead(flameSensorL) == LOW))
  {
    digitalWrite(pumpRelay,HIGH);
  }
  else
  {
    digitalWrite(pumpRelay,LOW);

  }

  

}


void Backward()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);  /*pwm 0--->255*/
  digitalWrite(in4, HIGH);
  analogWrite(EN_A, 160);
  analogWrite(EN_B, 160);
}
void forward()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(EN_A,160);
  analogWrite(EN_B,160);
}

void Left()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(EN_A, 160);
  analogWrite(EN_B, 160);
}
void Right()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(EN_A, 160);
  analogWrite(EN_B, 160);
}

void stopp()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}