// ----------- L298N Motor Driver Pins -----------
int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;


// ----------- Other Pins -----------
int buzzerPin = 3;
int touchPin  = 2;

// Traffic Light LEDs (OUTPUT now)

int greenLedPin = 11;

// ----------- Traffic Light Timing -----------
unsigned long previousMillis = 0;
const unsigned long lightInterval = 7000; // 7 seconds
bool greenLightState = true;

// Robot state
bool robotMoving = false;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  

  pinMode(buzzerPin, OUTPUT);
  pinMode(touchPin, INPUT);

  
  pinMode(greenLedPin, OUTPUT);

  // Start with GREEN
  digitalWrite(greenLedPin, HIGH);
 
  stopRobot();
}

void loop() {

  updateTrafficLight();   // change LEDs every 7 sec

  int touchDetected = digitalRead(touchPin);

  if (touchDetected == HIGH) {

    if (greenLightState) {
      // ✅ Green light → Move
      if (!robotMoving) {
        moveRobot();
        movementSound();
      }
    } 
    else {
      // ⛔ Red light → Stop
      if (robotMoving) {
        stopRobot();
        waitSound();
      }
    }
  } 
  else {
    // Touch not pressed → stop robot
    if (robotMoving) {
      stopRobot();
      stopSound();
    }
  }
}

// ---------------- TRAFFIC LIGHT FUNCTION ---------------- //

void updateTrafficLight() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= lightInterval) {
    previousMillis = currentMillis;

    greenLightState = !greenLightState;

    if (greenLightState) {
      digitalWrite(greenLedPin, HIGH);
     
    } else {
      digitalWrite(greenLedPin, LOW);
      
    }
  }
}

// ---------------- ROBOT MOVEMENT FUNCTIONS ---------------- //

void moveRobot() {
  robotMoving = true;

 

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stopRobot() {
  robotMoving = false;

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// ---------------- BUZZER SOUNDS ---------------- //

void waitSound() {
  tone(buzzerPin, 400, 200);
  delay(200);
  tone(buzzerPin, 300, 200);
  delay(200);
}

void movementSound() {
  tone(buzzerPin, 900, 150);
  delay(200);
}

void stopSound() {
  tone(buzzerPin, 500, 200);
  delay(200);
}
