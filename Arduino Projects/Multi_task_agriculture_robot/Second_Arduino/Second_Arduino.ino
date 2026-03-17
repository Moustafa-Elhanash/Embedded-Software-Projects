#include <SimpleDHT.h>
#include <Wire.h> 
#include <LiquidCrystal.h>
#define Relay 9
#define Mode A0


int pinDHT11 = 10;
SimpleDHT11 dht11(pinDHT11);
 const int rs = 12, en = 11, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
 LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void setup() {
  pinMode(Relay,OUTPUT);  
  pinMode(Mode,INPUT);
  lcd.begin(16, 2);
  Serial.begin(115200);
}

void loop() {
  // start working...
  Serial.println("=================================");
  Serial.println("Sample DHT11...");
  
  // read without samples.
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }
  

    //lcd.begin();

  // Turn on the blacklight and print a message.
  //lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("tempature  "); lcd.print((int)temperature);
  lcd.setCursor(0, 1);
  lcd.print("humidity  ");
  lcd.print((int)humidity);

  if ((int)temperature>=30)
  {
    digitalWrite(Relay,LOW);        
  
  }    
  else
  {
    digitalWrite(Relay,HIGH);    
  }     

  delay(1000);
}
