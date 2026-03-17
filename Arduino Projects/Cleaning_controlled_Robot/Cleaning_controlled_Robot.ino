// ===== Cleaning Robot by HC-05 Control =====

#define ENA 5    // Enable pin for left motor
#define IN1 6
#define IN2 7
#define ENB 10   // Enable pin for right motor
#define IN3 8
#define IN4 9

#define RELAY_WATER 3   // Relay 1 for sprinkling water
#define RELAY_BRUSH 4   // Relay 2 for moving brush

char command; // stores incoming Bluetooth data

void setup() {
  Serial.begin(9600); // HC-05 default baud rate
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(RELAY_WATER, OUTPUT);
  pinMode(RELAY_BRUSH, OUTPUT);

  // initialize all off
  stopMotors();
  digitalWrite(RELAY_WATER, HIGH);
  digitalWrite(RELAY_BRUSH, HIGH);

  Serial.println("Cleaning Robot Ready!");
}

void loop() 
{
  if (Serial.available()) {
    command = Serial.read();
    Serial.println(command); // for debugging

    switch (command) {
      case 'F': moveForward(); break;
      case 'B': moveBackward(); break;
      case 'L': turnLeft(); break;
      case 'R': turnRight(); break;
      case 'S': stopMotors(); break;
      case 'W': toggleRelay(RELAY_WATER); break;
      case 'C': toggleRelay(RELAY_BRUSH); break;
    }
  }
}
 

// ===== Motor Functions =====
void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  
}

// ===== Relay Toggle Function =====
void toggleRelay(int pin) {
  digitalWrite(pin, !digitalRead(pin));
}
