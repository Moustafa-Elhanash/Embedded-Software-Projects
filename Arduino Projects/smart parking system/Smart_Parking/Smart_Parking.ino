#include <Servo.h>
#include <LiquidCrystal_I2C.h>

#define GATE_IN 2
#define GATE_OUT 5
#define PARKING_1 4
#define PARKING_2 6
#define ServoPin 3
#define LED_P1 11
#define LED_P2 12

Servo servo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

bool Complete_flag = 0 ;
bool P1_flag = 0;
bool P2_flag = 0;

void setup() 
{
  Serial.begin(9600);
  pinMode(GATE_IN , INPUT);
  pinMode(GATE_OUT , INPUT);
  pinMode(PARKING_1 , INPUT);
  pinMode(PARKING_2 , INPUT);

  pinMode(LED_P1 , OUTPUT);
  pinMode(LED_P2 , OUTPUT);
  lcd.init();
  lcd.backlight();
  servo.attach(ServoPin);
  lcd.setCursor(0, 0);
  lcd.print("Smart Parking");
  delay(2000);
  lcd.clear();

}

void loop() 
{

if(digitalRead(PARKING_1) == LOW)
{
  digitalWrite(LED_P1,HIGH);
  P1_flag = 1;
}
else
{
  digitalWrite(LED_P1,LOW);
  P1_flag = 0;
}

if(digitalRead(PARKING_2) == LOW)
{
  digitalWrite(LED_P2,HIGH);
  P2_flag = 1;
}
else
{
  digitalWrite(LED_P2,LOW);
  P2_flag = 0;
}

if((P1_flag +  P2_flag) == 2)
{
  Complete_flag =1;
}
else
{
  Complete_flag =0;
}


//the status of the main gate 
if(((digitalRead(GATE_IN) == LOW) && (Complete_flag ==0)) || (digitalRead(GATE_OUT) == LOW))
{
  servo.write(90); // Gate opens 
}
else if(((digitalRead(GATE_IN) == LOW) && (Complete_flag ==1) && (digitalRead(GATE_OUT) == HIGH)))
{
  servo.write(0); // Gate closes 
  
  lcd.setCursor(0, 0);
  lcd.print("Places are Full!");
}
else 
{
  servo.write(0); // Gate closes 
  lcd.setCursor(0, 0);
  lcd.print("Available places");
  lcd.setCursor(0, 4); 
  lcd.print(2-(P1_flag+P2_flag));

}


}
