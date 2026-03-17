#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// --- Sensor & Actuator Pins ---
#define DHTPIN 2
#define DHTTYPE DHT11
#define MOISTURE_PIN A0
#define RELAY_PIN 6
#define RAIN_SENSOR_PIN 4
#define SERVO_PIN 3
#define TANK_LEVEL_PIN A1

// --- Components ---
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address might be 0x3F on some modules
Servo tankServo;

// --- Thresholds ---
int moistureThreshold = 500;  // Adjust based on testing (lower = wetter)
int tankFullThreshold = 600;  // Adjust based on testing

void setup() {
  Serial.begin(9600);

  dht.begin();
  lcd.init();
 // lcd.begin(16, 2);
  lcd.backlight();

  pinMode(MOISTURE_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(RAIN_SENSOR_PIN, INPUT);
  pinMode(TANK_LEVEL_PIN, INPUT);

  digitalWrite(RELAY_PIN, LOW); // Ensure pump is off initially
  tankServo.attach(SERVO_PIN);
  tankServo.write(0); // Lid closed

  lcd.setCursor(0, 0);
  lcd.print("Smart Irrigation");
  delay(2000);
  lcd.clear();
}

void loop() {
  // --- Read sensors ---
  float humidity = dht.readHumidity();
  float temp = dht.readTemperature();
  int moisture = analogRead(MOISTURE_PIN);
  int rain = digitalRead(RAIN_SENSOR_PIN); // 0 = rain detected on some modules
  int tankLevel = analogRead(TANK_LEVEL_PIN);

  // --- Display temperature and humidity ---
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temp);
  lcd.print("C H:");
  lcd.print(humidity);
  lcd.print("%");
  
  delay(1000);
 lcd.clear();

  // --- Soil Moisture Logic ---
  if (moisture > moistureThreshold) {
    // Soil is dry
    lcd.clear();
    digitalWrite(RELAY_PIN, HIGH); // Turn on pump
    lcd.setCursor(0, 1);
    lcd.print("Sprinkler: ON  ");
  } else {
    digitalWrite(RELAY_PIN, LOW); // Turn off pump
  }

  // --- Rain Detection Logic ---
  if (rain == LOW) { // Adjust if your module gives HIGH for rain
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Rain Detected  ");
    tankServo.write(90); // Open lid
  }
  else
  {
    tankServo.write(0); 
  }

  // --- Tank Level Logic ---
  if (tankLevel > tankFullThreshold) {
    tankServo.write(0); // Close lid when tank is full
  }

  //delay(2000);
}



