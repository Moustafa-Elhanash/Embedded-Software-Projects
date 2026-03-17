
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// --- Sensor & Actuator Pins ---
#define DHTPIN 2
#define DHTTYPE DHT11
#define RAIN_SENSOR_PIN 4
#define SERVO_Tank_PIN 3
#define SERVO_OUT_PIN 5
#define TANK_LEVEL_PIN A1

// --- Components ---
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address might be 0x3F on some modules
Servo tankServo;
Servo ServoOUT;
// --- Thresholds ---

int tankFullThreshold = 600;  // Adjust based on testing

void setup() {
  Serial.begin(9600);

  dht.begin();
  lcd.init();
 // lcd.begin(16, 2);
  lcd.backlight();  
  pinMode(RAIN_SENSOR_PIN, INPUT);
  pinMode(TANK_LEVEL_PIN, INPUT);


  tankServo.attach(SERVO_Tank_PIN);
  ServoOUT.attach(SERVO_OUT_PIN);
  tankServo.write(0); // Lid closed
  ServoOUT.write(0); // Lid closed
  
  lcd.setCursor(0, 0);
  lcd.print("Welcome :)");
  delay(2000);
  lcd.clear();
}

void loop() {
  // --- Read sensors ---
  float humidity = dht.readHumidity();
  float temp = dht.readTemperature();
  int rain = digitalRead(RAIN_SENSOR_PIN); // 0 = rain detected on some modules
  int tankLevel = analogRead(TANK_LEVEL_PIN);

  // --- Display temperature and humidity ---
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temp+21);
  lcd.print("C H:");
  lcd.print(humidity);
  lcd.print("%");
  


  // --- Rain Detection Logic ---
  if ((rain == LOW ) && (tankLevel <= tankFullThreshold)) { // Adjust if your module gives HIGH for rain
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Rain detected");
    tankServo.write(90); // Open lid
    ServoOUT.write(0);
  }
  else if((rain == LOW ) && (tankLevel > tankFullThreshold))
  {
     lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Tank is Full");
    tankServo.write(0); 
    ServoOUT.write(90);
  }
  else
  {
    tankServo.write(0); 
    ServoOUT.write(0);
   // lcd.print("Rain stoped");
  }
 
}



