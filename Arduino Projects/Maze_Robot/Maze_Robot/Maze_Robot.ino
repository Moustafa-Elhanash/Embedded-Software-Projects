#include <Servo.h>

// === Pin Configuration ===
#define TRIG_PIN 11
#define ECHO_PIN 12
#define ENA 5    // Enable pin for Left Motor
#define IN1 6
#define IN2 7
#define ENB 10     // Enable pin for Right Motor
#define IN3 8
#define IN4 9
#define SERVO_PIN 3

// === Constants ===
#define SAFE_DISTANCE 20  // Distance in cm considered safe

Servo servo;

// === Function Prototypes ===
long getDistance();
void moveForward();
void moveBackward();
void turnLeft();
void turnRight();
void stopMoving();

void setup() {
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  servo.attach(SERVO_PIN);
  servo.write(90); // Face forward

  Serial.println("Maze Solver Robot Initialized!");
  delay(1000);
}

void loop() 
{
  /*
   int distanceFront, distanceLeft, distanceRight;

  // --- Check Front ---
  servo.write(90);
  delay(400);
  distanceFront = getDistance();

  // --- Check Left ---
  servo.write(160);
  delay(400);
  distanceLeft = getDistance();

  // --- Check Right ---
  servo.write(20);
  delay(400);
  distanceRight = getDistance();

  // --- Return to Forward ---
  servo.write(90);
  delay(300);

  Serial.print("L: ");
  Serial.print(distanceLeft);
  Serial.print(" | F: ");
  Serial.print(distanceFront);
  Serial.print(" | R: ");
  Serial.println(distanceRight);

  // === Decision Making ===
  if (distanceFront > SAFE_DISTANCE) {
    moveForward();
  } 
  else {
    stopMoving();
    delay(300);
    if (distanceLeft > distanceRight) {
      turnLeft();
    } else {
      turnRight();
    }
  }

  delay(100);
  */
 moveForward();
 delay(1000);
 moveBackward();
  delay(1000);

 turnLeft();
  delay(1000);

 turnRight();
  delay(1000);

}

// === Function Definitions ===

long getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  long distance = duration * 0.034 / 2;
  return distance;
}

void moveForward() {
  analogWrite(ENA, 180);
  analogWrite(ENB, 180);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Moving Forward");
}

void moveBackward() {
  analogWrite(ENA, 180);
  analogWrite(ENB, 180);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Moving Backward");
}

void turnLeft() {
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Turning Left");
  delay(500);
}

void turnRight() {
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Turning Right");
  delay(500);
}

void stopMoving() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  Serial.println("Stopped");
}
