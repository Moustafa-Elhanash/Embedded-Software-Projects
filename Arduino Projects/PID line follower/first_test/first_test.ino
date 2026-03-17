#include <QTRSensors.h>

// --- QTR-8RC settings ---
#define NUM_SENSORS 8
#define TIMEOUT 2500
#define EMITTER_PIN 7

QTRSensors qtrrc;
unsigned int sensorValues[NUM_SENSORS];

// --- Motor driver pins (TB6612FNG) ---
#define STBY 10
#define PWMA 5   // Right motor speed
#define AIN1 9
#define AIN2 8
#define PWMB 6   // Left motor speed
#define BIN1 11
#define BIN2 12
#define Cal_Led A0

// --- PID constants ---
float Kp = 0.05;
float Kd = 0.25;
int maxSpeed = 200;
int baseSpeed = 150;

int lastError = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Calibrating sensors...");

  // Set up QTR pins
  qtrrc.setSensorPins((const uint8_t[]){2, 3, 4, A1, A2, A3, A4, A5}, NUM_SENSORS);
  qtrrc.setEmitterPin(EMITTER_PIN);

  // --- Motor pins setup ---
  pinMode(STBY, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(Cal_Led, OUTPUT);

  

  // --- Calibrate sensors ---
  for (uint16_t i = 0; i < 250; i++) {
    qtrrc.calibrate();
    digitalWrite(Cal_Led, (i % 2));
    delay(20);
  }
  digitalWrite(Cal_Led, HIGH);
  Serial.println("Calibration done!");
  delay(1000);
}

// --- Motor control functions ---
void moveMotors(int leftSpeed, int rightSpeed) {
  digitalWrite(STBY, HIGH);

  // Right motor
  if (rightSpeed >= 0) {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
  } else {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    rightSpeed = -rightSpeed;
  }

  // Left motor
  if (leftSpeed >= 0) {
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
  } else {
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    leftSpeed = -leftSpeed;
  }

  analogWrite(PWMA, constrain(rightSpeed, 0, 255));
  analogWrite(PWMB, constrain(leftSpeed, 0, 255));
}

void loop() {
  unsigned int position = qtrrc.readLineBlack(sensorValues);
  int error = position - 3500; // For 8 sensors (range 0–7000)

  // --- PID control ---
  int motorSpeedChange = Kp * error + Kd * (error - lastError);
  lastError = error;

  int leftMotorSpeed = baseSpeed + motorSpeedChange;
  int rightMotorSpeed = baseSpeed - motorSpeedChange;

  leftMotorSpeed = constrain(leftMotorSpeed, 0, maxSpeed);
  rightMotorSpeed = constrain(rightMotorSpeed, 0, maxSpeed);

  moveMotors(leftMotorSpeed, rightMotorSpeed);

  // Optional for debugging:
  Serial.print("Position: ");
  Serial.print(position);
  Serial.print(" | Error: ");
  Serial.println(error);
}
