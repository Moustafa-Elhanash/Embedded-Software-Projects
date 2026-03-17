#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <Servo.h>
#include <LiquidCrystal_I2C.h>   // LCD I2C

// Pick analog outputs, for the UNO these three work well
#define redpin 3
#define greenpin 5
#define bluepin 6
#define SERVO_PIN 3

#define commonAnode true

byte gammatable[256];

Servo servoMotor;
Adafruit_TCS34725 tcs = Adafruit_TCS34725(
  TCS34725_INTEGRATIONTIME_50MS,
  TCS34725_GAIN_4X
);

// LCD I2C (16x2)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
 // Serial.println("Color View Test!");

  servoMotor.attach(SERVO_PIN);
  servoMotor.write(90);

  // LCD init
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Color Sensor");
  lcd.setCursor(0, 1);
  lcd.print("Initializing");

  if (tcs.begin()) {
   // Serial.println("Found sensor");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor Found");
  } else {
    //Serial.println("No TCS34725 found ... check your connections");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error");
    while (1);
  }

#if defined(ARDUINO_ARCH_ESP32)
  ledcAttachPin(redpin, 1);
  ledcSetup(1, 12000, 8);
  ledcAttachPin(greenpin, 2);
  ledcSetup(2, 12000, 8);
  ledcAttachPin(bluepin, 3);
  ledcSetup(3, 12000, 8);
#else
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
#endif

  for (int i = 0; i < 256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;

    if (commonAnode) {
      gammatable[i] = 255 - x;
    } else {
      gammatable[i] = x;
    }
  }
   lcd.setCursor(0, 0);
   lcd.print("Color Sorting System");\
   delay(2000);
   lcd.clear();
}

void loop() {
  float red, green, blue;

  tcs.setInterrupt(false);
  delay(60);
  tcs.getRGB(&red, &green, &blue);
  tcs.setInterrupt(true);

  //Serial.print("R:\t"); Serial.print(int(red));
  //Serial.print("\tG:\t"); Serial.print(int(green));
  //Serial.print("\tB:\t"); Serial.println(int(blue));

  // -------- LCD Display --------
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("R:");
  lcd.print((int)red);
  lcd.print(" G:");
  lcd.print((int)green);

  lcd.setCursor(0, 1);
  lcd.print("B:");
  lcd.print((int)blue);
  lcd.print(" ");

  if ((int(red) >= 85)) {
    lcd.print("RED");
    servoMotor.write(155);
    delay(2000);
    servoMotor.write(90);
  }
  else if ((int(green) >= 105)) {
    lcd.print("GREEN");
    servoMotor.write(30);
    delay(2000);
    servoMotor.write(90);
  }
  else {
    lcd.print("OTHER");
   // servoMotor.write(90);
  }

#if defined(ARDUINO_ARCH_ESP32)
  ledcWrite(1, gammatable[(int)red]);
  ledcWrite(2, gammatable[(int)green]);
  ledcWrite(3, gammatable[(int)blue]);
#else
  analogWrite(redpin, gammatable[(int)red]);
  analogWrite(greenpin, gammatable[(int)green]);
  analogWrite(bluepin, gammatable[(int)blue]);
#endif
}
