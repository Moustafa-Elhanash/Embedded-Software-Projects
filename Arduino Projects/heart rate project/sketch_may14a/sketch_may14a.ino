#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Check your LCD address if needed

const int pulsePin = A0; // Sensor connected to A0
int threshold = 550;     // Threshold for beat detection

void setup() {
  pinMode(pulsePin, INPUT);
  lcd.begin(16, 2);
  lcd.backlight();
  Serial.begin(9600);

  lcd.setCursor(0, 0);
  lcd.print("Place your finger");
  delay(2000);
  lcd.clear();
  lcd.print("Measuring...");
  delay(1000);
}

void loop() {
  int beatCount = 0;
  unsigned long startTime = millis();

  bool beatDetected = false;

  while (millis() - startTime < 15000) { // Measure for 15 seconds
    int signal = analogRead(pulsePin);
      Serial.println(signal);
    
    if (signal > threshold && !beatDetected) {
      beatCount++;
      beatDetected = true;
      lcd.clear();
  lcd.print("Measuring...");
  delay(1000);
    }
    if (signal < threshold) {
      beatDetected = false;
    }

    delay(10); // Sampling delay
  }

  int bpm = beatCount * 4;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Heart Rate: ");
  lcd.print(bpm);
  lcd.print(" BPM");

  lcd.setCursor(0, 1);
  if (bpm >= 60 && bpm <= 100) {
    lcd.print("Status: Normal");
  } else {
    lcd.print("Status: Abnormal");
  }

  // Optional: print on serial monitor
  Serial.print("BPM: ");
  Serial.println(bpm);
  


  // Wait before restarting
  delay(10000); // Wait 10s
  lcd.clear();
  lcd.print("Place your finger");
  delay(2000);
  
}