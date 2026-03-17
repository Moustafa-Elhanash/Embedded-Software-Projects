#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ---------- LCD ----------
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ---------- Motor (L298N) ----------
const int IN1 = 5;
const int IN2 = 6;
const int ENA = 10;

// ---------- IR Sensors ----------
int ir1 = 2;   // Floor 1
int ir2 = 3;   // Floor 2
int ir3 = 4;   // Floor 3

// ---------- State ----------
int currentFloor = 0;
int targetFloor  = 0;

void setup() {
  Serial.begin(9600);   // HC-05 default baud rate

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Bluetooth Lift");
  lcd.setCursor(0, 1);
  lcd.print("Waiting...");
}

void loop() {
  readCurrentFloor();

  // ---------- Bluetooth Command ----------
  if (Serial.available()) {
    char cmd = Serial.read();

    if (cmd == '1' || cmd == '2' || cmd == '3') {
      targetFloor = cmd - '0';

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Target Floor:");
      lcd.setCursor(0, 1);
      lcd.print(targetFloor);
    }
  }

  // ---------- Movement Logic ----------
  if (targetFloor != 0 && currentFloor != 0) {

    if (targetFloor > currentFloor) {
      moveUp();
    }
    else if (targetFloor < currentFloor) {
      moveDown();
    }
    else {
      stopMotor();
      targetFloor = 0;

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Arrived at");
      lcd.setCursor(0, 1);
      lcd.print("Floor ");
      lcd.print(currentFloor);
    }
  }
}

// ================= FUNCTIONS =================

void readCurrentFloor() {
  if (digitalRead(ir1) == LOW) currentFloor = 1;
  else if (digitalRead(ir2) == LOW) currentFloor = 2;
  else if (digitalRead(ir3) == LOW) currentFloor = 3;

  lcd.setCursor(0, 0);
  lcd.print("Current Floor:");
  lcd.setCursor(0, 1);
  lcd.print(currentFloor);
  lcd.print("   ");
}

void moveUp() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA,90);
  lcd.setCursor(0, 0);
  lcd.print("Moving UP      ");
}

void moveDown() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA,90);


  lcd.setCursor(0, 0);
  lcd.print("Moving DOWN    ");
}

void stopMotor() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}
