#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <TimerOne.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int ir1_pin = 2;
const int ir2_pin = 3;

const int green_led = 10;
const int red_led = 9;
volatile int Timer_interrupt_counter =0;
int token_time = 0;
float time_sec = 0;
float speed = 0;
bool start_measure =0;
void timerIsr() 
{
  // This function will be called every time the timer elapses
  Timer_interrupt_counter++;
}
void ir1_detect()
{
  Timer_interrupt_counter=0;
  start_measure = 0;
  digitalWrite(green_led,LOW);
  digitalWrite(red_led,LOW);
}
void ir2_detect()
{

  token_time = Timer_interrupt_counter;
  start_measure = 1;
}
void setup() 
{
  Serial.begin(9600);
  // Initialize Timer1
  Timer1.initialize(10000); // Set a timer of length 10000 microseconds (or .01 sec)
  // Attach a function to be called whenever the timer elapses
  Timer1.attachInterrupt(timerIsr);
  pinMode(ir1_pin,INPUT);
  pinMode(ir2_pin,INPUT);
  pinMode(green_led,OUTPUT);
  pinMode(red_led,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(ir1_pin),ir1_detect,RISING);
  attachInterrupt(digitalPinToInterrupt(ir2_pin),ir2_detect,RISING);
  lcd.init();
  lcd.backlight();
  SPI.begin(); 
  
}
void loop() 
{


if(start_measure == 1)
  {
     time_sec = (token_time / 100);
     speed = (.35/time_sec) * 3.6;
     if(speed > 50.000)
  {
    lcd.setCursor(0, 0);
    lcd.print("Speed Exceeded!");
    lcd.setCursor(0, 1);
    lcd.print("                ");
   /*
    lcd.setCursor(0, 1);
    lcd.print("speed:   ");
    lcd.setCursor(6,1);
    lcd.print(speed);
     lcd.setCursor(12,1);
    lcd.print("KM/H");
   */
    digitalWrite(red_led,HIGH);
    digitalWrite(green_led,LOW);
  }
  else
  {
    lcd.setCursor(0, 0);
    lcd.print("Normal Speed    ");
    lcd.setCursor(0, 1);
    lcd.print("speed:");
    lcd.setCursor(6,1);
    lcd.print(speed);
    lcd.setCursor(12,1);
    lcd.print("KM/H");
    digitalWrite(green_led,HIGH);
    digitalWrite(red_led,LOW);
  }
 
  }
else
  {
    /*nothing*/
  }
 

 

}
