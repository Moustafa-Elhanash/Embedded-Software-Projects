
#define in1 8
#define in2 10
#define in3 12
#define in4 13
#define EN_A 11
#define EN_B 5

#define Right_IR 4
#define Left_IR 6
#define Box_IR 2
#define Station_IR 9

bool FLAG = 0;

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(EN_A, OUTPUT);
  pinMode(EN_B, OUTPUT);

  pinMode(Right_IR, INPUT);
  pinMode(Left_IR, INPUT);
  pinMode(Box_IR, INPUT);
  pinMode(Station_IR, INPUT);

}

void loop()
 {
  if( (digitalRead(Box_IR) == LOW) && (digitalRead(Station_IR) == HIGH) )
  {
    FLAG = 1;
  }
  else if ((digitalRead(Box_IR) == HIGH) && (digitalRead(Station_IR) == HIGH))
  {
    FLAG = 0;
  }
  else
  {
    /*nothing*/
  }

  if(((digitalRead(Box_IR) == HIGH) && (digitalRead(Station_IR) == HIGH) && (FLAG == 0)) 
    || ((digitalRead(Box_IR) == LOW) && (digitalRead(Station_IR) == LOW) && (FLAG == 0))
    || ((digitalRead(Box_IR) == HIGH) && (digitalRead(Station_IR) == LOW) && (FLAG == 1))
    || ((digitalRead(Box_IR) == LOW) && (digitalRead(Station_IR) == HIGH) && (FLAG == 1))
     )
  {
    Move();
  }
  else if (((digitalRead(Box_IR) == HIGH) && (digitalRead(Station_IR) == LOW) && (FLAG == 0))
          ||((digitalRead(Box_IR) == LOW) && (digitalRead(Station_IR) == LOW) && (FLAG == 1)))
  {
    stopp();
  }
  else
  {
    /*nothing*/
  }
}

void Move()
{
    if((digitalRead(Right_IR) == LOW ) && (digitalRead(Left_IR) == LOW))
  {
     Backward();
  }
  else if((digitalRead(Right_IR) == LOW ) && (digitalRead(Left_IR) == HIGH))
  {
    Left();
  }
  else if((digitalRead(Right_IR) == HIGH ) && (digitalRead(Left_IR) == LOW))
  { 
    Right();
  }
  else
  {
    stopp();
  }
}


void Backward()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);  /*pwm 0--->255*/
  digitalWrite(in4, HIGH);
  analogWrite(EN_A, 90);
  analogWrite(EN_B, 90);
}
void forward()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(EN_A,90);
  analogWrite(EN_B,90);
}

void Left()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(EN_A, 90);
  analogWrite(EN_B, 90);
}
void Right()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(EN_A, 90);
  analogWrite(EN_B, 90);
}

void stopp()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

