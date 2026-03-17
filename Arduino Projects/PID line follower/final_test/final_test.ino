#include <QTRSensors.h>

// --- QTR-8RC Sensor Configuration ---
#define NUM_SENSORS 8
#define TIMEOUT 2500
#define EMITTER_PIN 7

QTRSensors qtrrc;
unsigned int sensorValues[NUM_SENSORS];

// --- Motor Driver Pins (TB6612FNG) ---
#define AIN1 9
#define AIN2 8
#define BIN1 11
#define BIN2 12
#define STBY 10
#define PWMA 5   // Right motor speed
#define PWMB 6   // Left motor speed
#define Cal_Led A0

// --- PID Control ---
float Kp = 0.05;
float Kd = 0.25;
int baseSpeed = 150;
int maxSpeed = 200;
int lastError = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Calibrating sensors...");

  // --- Set sensor pins ---
  qtrrc.setSensorPins((const uint8_t[]){2, 3, 4, A1, A2, A3, A4, A5}, NUM_SENSORS);
  qtrrc.setEmitterPin(EMITTER_PIN);

  // --- Motor pins setup ---
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(STBY, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(Cal_Led, OUTPUT);

  // --- Calibration Process with LED indicator ---
  for (uint16_t i = 0; i < 250; i++) {
    qtrrc.calibrate();
    digitalWrite(Cal_Led, (i % 2)); // Blink LED during calibration
    delay(20);
  }
  digitalWrite(Cal_Led, HIGH); // Keep LED ON when done
  Serial.println("Calibration done!");
  delay(1000);

  digitalWrite(STBY, HIGH); // Enable driver
}

// ======== Motor Movement Functions ========

void moveForward(int speedVal = 200) {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMA, speedVal);
  analogWrite(PWMB, speedVal);
}

void moveBackward(int speedVal = 200) {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWMA, speedVal);
  analogWrite(PWMB, speedVal);
}

void turnLeft(int speedVal = 200) {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMA, speedVal);
  analogWrite(PWMB, speedVal);
}

void turnRight(int speedVal = 200) {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWMA, speedVal);
  analogWrite(PWMB, speedVal);
}

void stopMotors() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
}

// ======== Line Following Logic ========

void loop() {
  unsigned int position = qtrrc.readLineBlack(sensorValues);
  int error = position - 3500; // Center is around 3500 for 8 sensors

  // --- PID Calculation ---
  int motorSpeedChange = Kp * error + Kd * (error - lastError);
  lastError = error;

  int leftMotorSpeed = baseSpeed + motorSpeedChange;
  int rightMotorSpeed = baseSpeed - motorSpeedChange;

  leftMotorSpeed = constrain(leftMotorSpeed, 0, maxSpeed);
  rightMotorSpeed = constrain(rightMotorSpeed, 0, maxSpeed);

  // --- Apply movement based on PID ---
  if (abs(error) < 200) {
    moveForward(baseSpeed);
  } else if (error > 0) {
    turnRight(map(abs(error), 0, 3500, baseSpeed, maxSpeed));
  } else {
    turnLeft(map(abs(error), 0, 3500, baseSpeed, maxSpeed));
  }

  // Debugging info
  Serial.print("Position: ");
  Serial.print(position);
  Serial.print(" | Error: ");
  Serial.println(error);

  delay(10);
}
