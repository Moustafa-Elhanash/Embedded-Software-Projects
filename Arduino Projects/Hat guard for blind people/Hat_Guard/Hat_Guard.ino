// Smart Blind Assist Hat
// Arduino Nano + 4 Ultrasonic Sensors + 4 Buzzers

// Sensor pins (Trigger, Echo, Buzzer)
#define FRONT_TRIG 2
#define FRONT_ECHO 3
#define FRONT_BUZZ 4

#define RIGHT_TRIG 5
#define RIGHT_ECHO 6
#define RIGHT_BUZZ 7

#define BACK_TRIG 8
#define BACK_ECHO 9
#define BACK_BUZZ 10

#define LEFT_TRIG 11
#define LEFT_ECHO 12
#define LEFT_BUZZ 13

// Distance threshold in cm
const int safeDistance = 40;

void setup() {
  Serial.begin(9600);

  // Set pin modes for each sensor
  pinMode(FRONT_TRIG, OUTPUT);
  pinMode(FRONT_ECHO, INPUT);
  pinMode(FRONT_BUZZ, OUTPUT);

  pinMode(RIGHT_TRIG, OUTPUT);
  pinMode(RIGHT_ECHO, INPUT);
  pinMode(RIGHT_BUZZ, OUTPUT);

  pinMode(BACK_TRIG, OUTPUT);
  pinMode(BACK_ECHO, INPUT);
  pinMode(BACK_BUZZ, OUTPUT);

  pinMode(LEFT_TRIG, OUTPUT);
  pinMode(LEFT_ECHO, INPUT);
  pinMode(LEFT_BUZZ, OUTPUT);
}

void loop() {
  long front = getDistance(FRONT_TRIG, FRONT_ECHO);
  long right = getDistance(RIGHT_TRIG, RIGHT_ECHO);
  long back  = getDistance(BACK_TRIG, BACK_ECHO);
  long left  = getDistance(LEFT_TRIG, LEFT_ECHO);

  Serial.print("F: "); Serial.print(front);
  Serial.print(" | R: "); Serial.print(right);
  Serial.print(" | B: "); Serial.print(back);
  Serial.print(" | L: "); Serial.println(left);

  buzzControl(front, FRONT_BUZZ);
  buzzControl(right, RIGHT_BUZZ);
  buzzControl(back, BACK_BUZZ);
  buzzControl(left, LEFT_BUZZ);

  delay(100);
}

// Function to measure distance in cm
long getDistance(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long duration = pulseIn(echo, HIGH);
  long distance = duration * 0.034 / 2; // speed of sound 0.034 cm/µs
  return distance;
}

// Control buzzer based on distance
void buzzControl(long distance, int buzzerPin) {
  if (distance > 0 && distance < safeDistance) {
    // The closer the object, the faster the beep
    int delayTime = map(distance, 5, safeDistance, 50, 400);
    digitalWrite(buzzerPin, HIGH);
    delay(delayTime);
    digitalWrite(buzzerPin, LOW);
    delay(delayTime);
  } else {
    digitalWrite(buzzerPin, LOW);
  }
}
