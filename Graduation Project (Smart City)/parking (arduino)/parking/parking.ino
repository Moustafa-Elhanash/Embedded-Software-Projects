/*
*********************************************************************************************
       @file        : parking
       @author      : Moustafa El-Hanash
       @breif       : Smart parking
       @last update : 6/11/2023
*********************************************************************************************
*/

#include <LiquidCrystal_I2C.h> 
#include <Servo.h>
/* Ultrasonic p1 */
#define trig_p1 2
#define echo_p1 3
/* Ultrasonic p2 */
#define trig_p2 4
#define echo_p2 5
/* Ultrasonic p3 */
#define trig_p3 6
#define echo_p3 7
/* Ultrasonic gate */
#define trig_G 8
#define echo_G 9
/* servo pin */
#define servo 10
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27  scl--->A5  sda-->A4
long duration_p1, distance_p1, duration_p2, distance_p2, duration_p3, distance_p3, duration_G, distance_G;
int flag_p1=0,flag_p2=0,flag_p3=0,flag_complete=0,places=0;
Servo my_servo;
//int position = 0;
void setup()
{
  my_servo.attach(servo);                  /*my_servo.write(position) */
  lcd.init();                     
                    
  pinMode(trig_p1, OUTPUT);
  pinMode(echo_p1, INPUT);

  pinMode(trig_p2, OUTPUT);
  pinMode(echo_p2, INPUT);

  pinMode(trig_p3, OUTPUT);
  pinMode(echo_p3, INPUT);

  pinMode(trig_G, OUTPUT);
  pinMode(echo_G, INPUT);

  Serial.begin(9600);
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Smart Parking");
  delay (2000);
  lcd.clear();


}

void loop()
{
   Ultrasonic_p1();
   Ultrasonic_p2();
   Ultrasonic_p3();
   
   /* place 1 check */
   if(distance_p1 < 10)
   {
     flag_p1=1; // the place is reserved
   }
   else
   {
    flag_p1=0;  // the place is empty
   }
   
    /* place 2 check */
   if(distance_p2 < 10)
   {
     flag_p2=1; // the place is reserved
   }
   else
   {
    flag_p2=0;  // the place is empty
   }
   
    /* place 3 check  (undesired)*/
   if(distance_p3 < 10)
   {
     flag_p3=1; // the place is reserved
   }
   else
   {
    flag_p3=0;  // the place is empty
   }
   /* overall check */
   if((flag_p1==1) && (flag_p2==1) && (flag_p3==1))
   {
     flag_complete=1; // complete places
   }
   else
   {
    flag_complete=0;  // the place is not complete
   }

   Ultrasonic_G();
   if((distance_G < 10) && (flag_complete==0))
   {
    /* servo (gate) on */
    my_servo.write(90);
    
   }
   else if((distance_G > 10) && (flag_complete==0))
   {
    /* servo (gate) off */
     my_servo.write(0);
     places=flag_p1+flag_p2+flag_p3;
   lcd.setCursor(0,0);
   lcd.print("Available places");
   lcd.setCursor(0,1);
   lcd.print(3-places);
  

   }
   else if((distance_G < 10) && (flag_complete==1))
   {
    /* servo (gate) off */
     my_servo.write(0);
     lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("complete !!!");
    //  delay(2000);
      
   }
   else
   {
      my_servo.write(0);
     places=flag_p1+flag_p2+flag_p3;
   lcd.setCursor(0,0);
   lcd.print("Available places");
   lcd.setCursor(0,1);
   lcd.print(3-places);

   }
Serial.println(distance_p1);
Serial.println(distance_p2);
Serial.println(distance_p3);
Serial.println(distance_G);

}

void Ultrasonic_p1()
{
 
  digitalWrite(trig_p1, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_p1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_p1, LOW);
  duration_p1 = pulseIn(echo_p1, HIGH);
  distance_p1 = (duration_p1 / 2) * 0.0343;

}

void Ultrasonic_p2()
{
 
  digitalWrite(trig_p2, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_p2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_p2, LOW);
  duration_p2 = pulseIn(echo_p2, HIGH);
  distance_p2 = (duration_p2 / 2) * 0.0343;

}

void Ultrasonic_p3()
{
 
  digitalWrite(trig_p3, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_p3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_p3, LOW);
  duration_p3 = pulseIn(echo_p3, HIGH);
  distance_p3 = (duration_p3 / 2) * 0.0343;

}

void Ultrasonic_G()
{
 
  digitalWrite(trig_G, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_G, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_G, LOW);
  duration_G = pulseIn(echo_G, HIGH);
  distance_G = (duration_G / 2) * 0.0343;

}
