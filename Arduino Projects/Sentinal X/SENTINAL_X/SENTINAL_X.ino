// Pins
int ldrPin1 = A0;     // LDR for Laser 1
int ldrPin2 = A1;     // LDR for Laser 2
int buzzerPin = 9;    // Buzzer

// Threshold (adjust after reading Serial Monitor)
int threshold = 950;

void setup() {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);

  Serial.println("=== Sentinel-X Diagnostics Mode ===");
  Serial.println("LDR1\tLDR2\tStatus");
}

void loop() {
  int ldrValue1 = analogRead(ldrPin1);
  int ldrValue2 = analogRead(ldrPin2);

  bool beam1OK = ldrValue1 > threshold;
  bool beam2OK = ldrValue2 > threshold;

  // Serial Monitor output
  Serial.print(ldrValue1);
  Serial.print("\t");
  Serial.print(ldrValue2);
  Serial.print("\t");

  if (beam1OK && beam2OK) {
    Serial.println("SECURE");
    noTone(buzzerPin);
  } else {
    Serial.println("INTRUSION");
    tone(buzzerPin, 1000);
  }

  delay(200);
}
