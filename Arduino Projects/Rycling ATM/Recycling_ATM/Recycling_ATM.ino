#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <NewPing.h>  // لو عايز تستخدم Ultrasonic

// LCD I2C
LiquidCrystal_I2C lcd(0x27, 16, 2); // عنوان 0x27، 16x2 شاشة

// Servo
Servo coinServo;
int servoPin = 9;

// Ultrasonic Sensor 1
#define TRIG_PIN1 2
#define ECHO_PIN1 3
#define MAX_DISTANCE 650  // سم
NewPing ultrasonic1(TRIG_PIN1, ECHO_PIN1, MAX_DISTANCE);


// أو لو ultrasonic:
 #define TRIG_PIN2 5
 #define ECHO_PIN2 6

NewPing ultrasonic2(TRIG_PIN2, ECHO_PIN2, MAX_DISTANCE);

void setup() 
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Insert Bottle");
  
  coinServo.attach(servoPin);
  coinServo.write(0); // وضع البداية للجنيه
}
void loop() 
{
  // قراءة Ultrasonic 1
  delay(50);
  unsigned int distance1 = ultrasonic1.ping_cm();
  unsigned int distance2 = ultrasonic2.ping_cm();

  
  if((distance1 < 10 ) && (distance2 > 10) && (distance1 != 0) && (distance2 != 0))
  { // لو فيه علبة
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Bottle Detected");
  }
  else if((distance2 < 10)&& (distance2 != 0))
  {
     lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Bottle Collected");
    // تحريك السيرفو لإخراج الجنيه
    coinServo.write(90);  // حرّك السيرفو
    delay(1000);           // وقت خروج الجنيه
    coinServo.write(7);   // ارجع السيرفو لوضع البداية
    
    lcd.setCursor(0,1);
    lcd.print("Coin Released");
    delay(2000);

  }
  else
  {
  
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Insert Bottle");
  }
Serial.print("Distance 1: ");
  Serial.print(distance1);
  Serial.print(" cm    ");

  Serial.print("Distance 2: ");
  Serial.print(distance2);
  Serial.println(" cm");
}  

  

    
    
  
  

