#include <Servo.h>

#define MQ2_PIN 5
#define FLAME_PIN 4
#define BUZZER_PIN 2
#define SERVO_PIN 3

Servo gasServo;

int closeAngle = 90;   // زاوية قفل محبس الغاز
int openAngle  = 0;    // زاوية الفتح الطبيعي

void setup() {
  pinMode(MQ2_PIN, INPUT);
  pinMode(FLAME_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  gasServo.attach(SERVO_PIN);
  gasServo.write(openAngle);   // الوضع الطبيعي: الغاز مفتوح

  digitalWrite(BUZZER_PIN, LOW);
}

void loop() {
  int gasState = digitalRead(MQ2_PIN);
  int flameState = digitalRead(FLAME_PIN);

  // Emergency case: Gas or Fire detected
  if (gasState == LOW || flameState == LOW) {  
    digitalWrite(BUZZER_PIN, HIGH); // شغل البزر

    // لو السبب غاز بس → اقفل المحبس
    if (gasState == LOW) {
      gasServo.write(closeAngle);
    }
  }
  else {
    // مفيش خطر
    digitalWrite(BUZZER_PIN, LOW);
    gasServo.write(openAngle);
  }

  delay(200);
}
