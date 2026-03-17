#define in1 13
#define in2 12
#define in3 11
#define in4 10
#define EN_A 9
#define EN_B 3


#define trig_A 2
#define echo_A 4

#define trig_B 5
#define echo_B 6



#define Relay 8
#define Buzzer 7
long duration_A, distance_A, duration_B, distance_B;
char mode;
//char mov;
bool cut_flag = 0;
bool free_mov_flag = 0;

void setup()
{
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(EN_A, OUTPUT);
  pinMode(EN_B, OUTPUT);


  pinMode(trig_A, OUTPUT);
  pinMode(echo_A, INPUT);
  pinMode(trig_B, OUTPUT);
  pinMode(echo_B, INPUT);


  pinMode(Relay, OUTPUT);
  pinMode(Buzzer, OUTPUT);

  pinMode(A0, OUTPUT);  

  Serial.begin(9600);
  digitalWrite(Relay, HIGH);
}

void Backward()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);  /*pwm 0--->255*/
  digitalWrite(in4, LOW);
  analogWrite(EN_A, 150);
  analogWrite(EN_B, 150);


  /*digitalWrite(Relay,HIGH);
    digitalWrite(Buzzer,LOW); */

}
void forward()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(EN_A, 150);
  analogWrite(EN_B, 150);

  /*  digitalWrite(Relay,LOW);
    digitalWrite(Buzzer,LOW); */

}

void Left()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(EN_A, 150);
  analogWrite(EN_B, 150);

  /* digitalWrite(Relay,HIGH);
    digitalWrite(Buzzer,LOW);*/

}
void Right()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(EN_A, 150);
  analogWrite(EN_B, 150);

  /*  digitalWrite(Relay,HIGH);
    digitalWrite(Buzzer,LOW);*/

}

void stopp()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  /* digitalWrite(Relay,LOW);
    digitalWrite(Buzzer,HIGH); */
}
void Ultrasonic_B()
{
  /*ultrasonic (B)*/
  digitalWrite(trig_B, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_B, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_B, LOW);
  duration_B = pulseIn(echo_B, HIGH);
  distance_B = (duration_B / 2) * 0.0343;
}
void Ultrasonic_A()
{
  /*ultrasonic (A)*/
  digitalWrite(trig_A, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_A, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_A, LOW);
  duration_A = pulseIn(echo_A, HIGH);
  distance_A = (duration_A / 2) * 0.0343;

}
void cutter()
{
  //digitalWrite(A0,LOW);  
  Ultrasonic_A();
  Ultrasonic_B();  
 
if (distance_A>=35 && distance_B<=15 )         
     
  {
    forward();
  digitalWrite(Relay,LOW);
  digitalWrite(Buzzer,LOW);  
  }
  else
  {
    stopp();
  /*digitalWrite(Relay,LOW);
  digitalWrite(Buzzer,HIGH);
    delay(200);*/
    Right();
 /* digitalWrite(Relay,LOW);
  digitalWrite(Buzzer,LOW);*/
    }
   
/*Serial.println(distance_A);
delay(1000);
Serial.println(distance_B);
delay(1000);  */
}
void loop()
{
    
  if (Serial.available() > 0)
  {
    mode = Serial.read();
    switch (mode)
    {
      case 'c':
        cut_flag = 1;
        free_mov_flag = 0;
        break;
      case 'f':
        cut_flag = 0;
        free_mov_flag = 1;
      default:
        cut_flag = 0;
        // free_mov_flag=0;

    }
  }
  if (cut_flag == 1)
  {      
    
    cutter();
  }
  if ((Serial.available() > 0) && free_mov_flag == 1) 
  {
   // digitalWrite(A0,HIGH);  
    stopp();
    mode = Serial.read();
    switch (mode) {
      case 'A':
        forward();
        digitalWrite(Relay, HIGH);
        break;
      case 'b':
        Backward();
        digitalWrite(Relay, HIGH);
        break;
      case 'r':
        Right();
        digitalWrite(Relay, HIGH);
        break;
      case 'l':
        Left();
        digitalWrite(Relay, HIGH);
        break;
      case 's':
        stopp();
        digitalWrite(Relay, HIGH);
        break;
    }
  }
}
