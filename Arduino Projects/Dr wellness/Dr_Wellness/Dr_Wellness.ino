#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// ====================== PIN ASSIGNMENTS ===========================
#define IR_PIN 12               // Cup detection IR sensor
#define BUTTON_PIN 2          // Push button for heart rate mode
#define RELAY_PIN 13          // Water pump relay
#define BUZZER_PIN 11

// L298N motor driver
#define ENA 5                  // Speed left
#define IN1 6
#define IN2 7
#define ENB 10                // Speed right
#define IN3 8
#define IN4 9

// Heart rate sensor
#define HEART_SENSOR A0

// Servo
#define SERVO_PIN 3          // Medicine dropper

// ====================== OBJECTS ================================
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servoMotor;

// Timers
unsigned long lastMedicineTime = 0;
const unsigned long MEDICINE_INTERVAL = 120000;  // 2 minutes

// ====================== BASIC MOVEMENT ===========================
void moveForward() {
  analogWrite(ENA, 180);
  analogWrite(ENB, 180);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  analogWrite(ENA, 180);
  analogWrite(ENB, 180);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMoving() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// ====================== BUZZER HELPERS ===========================
void beep() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(150);
  digitalWrite(BUZZER_PIN, LOW);
}

// ====================== MEDICINE DROPPER =========================
void dropMedicine() {
  servoMotor.write(0);
  delay(500);
  servoMotor.write(90);
  delay(500);
}

// ====================== HEART RATE READING =======================
int readHeartRate() {
  int sensorValue = analogRead(HEART_SENSOR);
  return sensorValue;   // simplified for HW-487
}

// ====================== SETUP ===============================
void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(IR_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  servoMotor.attach(SERVO_PIN);
  servoMotor.write(90);

  digitalWrite(RELAY_PIN, LOW); // pump off
  digitalWrite(BUZZER_PIN, LOW);

  lcd.setCursor(0, 0);
  lcd.print("Doctor Robot");
  lcd.setCursor(0, 1);
  lcd.print("System Ready");
  delay(2000);
}

// ====================== MAIN LOOP =============================
void loop() {

  // ============================================================
  // 1. CHECK FOR BUTTON PRESS → HEART RATE MODE
  // ============================================================
  if (digitalRead(BUTTON_PIN) == LOW) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Heart Rate Mode");

    beep();
    delay(1000);

    for (int i = 0; i < 10; i++) {
      int hr = readHeartRate();
      lcd.setCursor(0, 1);
      lcd.print("Value: ");
      lcd.print(int(hr/9.6));
      delay(500);
    }

    lcd.clear();
    lcd.print("Done.");
    beep();
    delay(1500);
  }

  // ============================================================
  // 2. EVERY 2 MINUTES → MOVE, DROP MED, WAIT, FILL CUP
  // ============================================================
  if (millis() - lastMedicineTime >= MEDICINE_INTERVAL) {
    lastMedicineTime = millis();

    // Move forward
    lcd.clear();
    lcd.print("Moving to");
    lcd.setCursor(0, 1);
    lcd.print("Patient...");
    moveForward();
    delay(2000);
    stopMoving();

    // Drop medicine
    lcd.clear();
    lcd.print("Dropping Med...");
    beep();
    dropMedicine();
    delay(1000);

    // Wait for cup
    lcd.clear();
    lcd.print("Place Cup...");
    while (digitalRead(IR_PIN) == HIGH) {
      // waiting for cup detected
    }

    // Cup detected → fill water
    lcd.clear();
    lcd.print("Filling Cup...");
    digitalWrite(RELAY_PIN, HIGH);  // pump ON
    beep();
    delay(3000);                    // pump duration
    digitalWrite(RELAY_PIN, LOW);   // pump OFF

    // WAIT FOR CUP REMOVAL
    lcd.clear();
    lcd.print("Take Cup...");
    while (digitalRead(IR_PIN) == LOW) {
      // waiting until cup removed
    }

    // Return home
    lcd.clear();
    lcd.print("Returning...");
    moveBackward();
    delay(2000);
    stopMoving();

    lcd.clear();
    lcd.print("Ready Again");
    delay(1000);
  }
}
