/*******for ESP8266************/
//#include <ESP8266WiFi.h>
//#include <FirebaseESP8266.h>
/***********END***************/
/*******for ESP32************/
#include <WiFi.h>
#include <FirebaseESP32.h>

/***********END***************/
/************for servo******/
#include <ESP32Servo.h>
/**************************/
/**********DH11************/
#include <DHT.h>
#define DHT11_PIN  21 // ESP32 pin GPIO21 connected to DHT11 sensor
DHT dht11(DHT11_PIN, DHT11);

/**************************/

/****************************windows*******************/
//living window
#define living_room_window_servo_pin  33
Servo living_room_window; 
bool  living_room_window_control =0;   // 0 for closed  
/****************main door*****************/
#define Main_Door_servo_pin  13
Servo Main_Door_servo; 
bool  Mian_Door_control =0;   // 0 for closed door 
/**********************************************/
/****************GARAGE DOOR*******************/
#define GARAGE_Door_servo_pin  16
Servo GARAGE_Door_servo; 
bool  GARAGE_Door_control =0;   // 0 for closed door 
/*********************************************/
/*****************************control light with app*********************/
bool living_Light_Control = 0;
const int living_Room_Light_pin = 12;
const int living_Room_Light_pin_fixed = 14;
int living_Room_Light_intensity = 0;
int living_Room_Light_intensity_pwm=0;
// setting PWM properties
const int freq = 5000;
const int living_Room_Light_Channel = 6;
const int resolution = 8;
//////////////kitchen light/////////////////
const int KITCHEN_Light_pin_fixed = 32;
bool KITCHEN_Light_Control = 0;
//////////////bathroom light/////////////////
const int BATHROOM_Light_pin_fixed = 2;
bool BATHROOM_Light_Control = 0;
//////////////garage light/////////////////
const int GARAGE_Light_pin_fixed = 4;
bool GARAGE_Light_Control = 0;
/************************************************************************/
/******************************************air condition*****************/
/////////////////////////LIVING AIR CONDITION/////////////////
const int living_Room_Air_condition_pin = 25;
int living_Room_Air_condition_control = 0;
/////////////////////////kitchen AIR CONDITION/////////////////
const int kitchen_Air_condition_pin = 15;
int kitchen_Air_condition_control = 0;
/***************************************************************************/
/************************* motion with light system*************************/
// Set GPIOs for LED and PIR Motion Sensor
#define timeSeconds 5

const int living_Room_Light_pir_pin = 26;
const int motionSensor = 27;

// Timer: Auxiliary variables
unsigned long now = millis();
unsigned long lastTrigger = 0;
boolean startTimer = false;
boolean motion = false;

// Checks if motion was detected, sets LED HIGH and starts a timer
void detectsMovement() {
 
  digitalWrite(living_Room_Light_pir_pin, HIGH);
  startTimer = true;
  lastTrigger = millis();
}
/**********************************************************************************************/
/*****************************garage system using ir***************************************************/
const int outside_garage_ir_pin = 35;
const int inside_garage_ir_pin = 34;
bool GARAGE_Door_ir_control =0 ;

void outside_garage_ir_detect()
{
GARAGE_Door_ir_control = 1;
}
void inside_garage_ir_detect()
{
GARAGE_Door_ir_control = 0;
}
/******************************************************************************************************/
/*********flame sensor & Gas sensor*******************************************************************/
const int flame_sensor_pin = 23;
const int gas_sensor_pin = 22;
const int emergency_alarm = 17;
int flame_emergency_alarm = 0;
int gas_emergency_alarm = 0;

void flame_emergency_on() // work at rising edge
{
  flame_emergency_alarm = 1;
  digitalWrite(emergency_alarm,HIGH);
}
void gas_emergency_on() // work at rising edge
{
  gas_emergency_alarm = 1;
  digitalWrite(emergency_alarm,HIGH);
}

/*****************************************************************************************************/
#define FIREBASE_HOST "https://smart-final-a0529-default-rtdb.firebaseio.com/"    // link-firebase 
#define FIREBASE_AUTH "6KZ6aJ30NYMMPn5AOmyrXLgEp49FxNeYOjzTS5En"          
#define WIFI_SSID "Engmo"    //AlteraNet1
#define WIFI_PASSWORD "12345678" //alteRa20t24
  



// Declare the Firebase Data object in the global scope
FirebaseData firebaseData;

FirebaseAuth auth;
FirebaseConfig config;
FirebaseJson json;


void setup()
{

  /*******************motion with light system*******************************************/
  pinMode(motionSensor, INPUT);
  // Set motionSensor pin as interrupt, assign interrupt function and set RISING mode
  attachInterrupt(digitalPinToInterrupt(motionSensor), detectsMovement, RISING);
 /***************************************************************************************/
 /*****************************garage system using ir***************************************************/
 pinMode(outside_garage_ir_pin, INPUT);
 pinMode(inside_garage_ir_pin, INPUT);
 attachInterrupt(digitalPinToInterrupt(outside_garage_ir_pin), outside_garage_ir_detect, RISING);
 attachInterrupt(digitalPinToInterrupt(inside_garage_ir_pin), inside_garage_ir_detect, RISING);
 /******************************************************************************************************/
 /*********flame sensor & Gas sensor*******************************************************************/
 pinMode(flame_sensor_pin, INPUT);
 pinMode(gas_sensor_pin, INPUT);

 attachInterrupt(digitalPinToInterrupt(flame_sensor_pin), flame_emergency_on, RISING);
 attachInterrupt(digitalPinToInterrupt(gas_sensor_pin), gas_emergency_on, RISING);

 /*****************************************************************************************************/
  // Set LED to LOW
  pinMode(living_Room_Light_pir_pin, OUTPUT);
  pinMode(living_Room_Light_pin, OUTPUT);
  pinMode(living_Room_Light_pin_fixed, OUTPUT);
  pinMode(living_Room_Air_condition_pin, OUTPUT);
  pinMode(KITCHEN_Light_pin_fixed, OUTPUT);
  pinMode(BATHROOM_Light_pin_fixed, OUTPUT);
  pinMode(GARAGE_Light_pin_fixed, OUTPUT);
  pinMode(kitchen_Air_condition_pin, OUTPUT);
  pinMode(emergency_alarm,OUTPUT);
  
  /************DH11******************/
  dht11.begin(); // initialize the DHT11 sensor
  /*********************************/
  
  // configure LED PWM functionalitites
  ledcSetup(living_Room_Light_Channel, freq, resolution);
   // attach the channel to the GPIO to be controlled
   ledcAttachPin(living_Room_Light_pin, living_Room_Light_Channel);
  digitalWrite(living_Room_Light_pir_pin, LOW);
  /****************************/
/***************main door************/
 Main_Door_servo.attach(Main_Door_servo_pin);
/*******************************/
/******************windows***************/
living_room_window.attach(living_room_window_servo_pin);
/****************************************/
/******************GARAGE DOOR**************/
GARAGE_Door_servo.attach(GARAGE_Door_servo_pin);
/*******************************************/
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
 
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  
  config.database_url = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;
  Firebase.begin(&config, &auth);

  Firebase.reconnectWiFi(true);

  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
  Serial.println("------------------------------------");
  Serial.println("Connected...");
  
}

void loop()
{ 

/*
if(WiFi.status()!= WL_CONNECTED)
{
 ESP.restart();
 Serial.println("trying to connect to WiFi");
 }
 else{
   Serial.println("WiFi - OK");
 }

*/
/*********flame sensor & Gas sensor*******************************************************************/
Firebase.setInt(firebaseData,"/Home_control/Flame_Alarm", flame_emergency_alarm); //send data
Firebase.setInt(firebaseData,"/Home_control/gas_Alarm", gas_emergency_alarm); //send data
if((digitalRead(flame_sensor_pin) == HIGH) && (digitalRead(gas_sensor_pin) == HIGH))
{
  gas_emergency_alarm = 0;
  flame_emergency_alarm = 0;
  digitalWrite(emergency_alarm,LOW);
}
else if((digitalRead(flame_sensor_pin) == HIGH) && (digitalRead(gas_sensor_pin) == LOW))
{
 flame_emergency_alarm = 0;
}
else if((digitalRead(flame_sensor_pin) == LOW) && (digitalRead(gas_sensor_pin) == HIGH))
{
 gas_emergency_alarm = 0;
}
else
{
  /* nothing */
}
/*******************************************************************************************************/
/*****************DH11****************/
// read humidity
  float humi  = dht11.readHumidity();
  // read temperature in Celsius
  float tempC = dht11.readTemperature();
// send data to living room 
  Firebase.setFloat(firebaseData,"/ESP/LIVING ROOM/Temperature", tempC); //send data
  Firebase.setFloat(firebaseData,"/ESP/LIVING ROOM/Humidity", humi); //send data  
// send data to kitchen
  Firebase.setFloat(firebaseData,"/ESP/KITCHEN/Temperature", tempC); //send data
  Firebase.setFloat(firebaseData,"/ESP/KITCHEN/Humidity", humi); //send data  
  // send data to bathroom
  Firebase.setFloat(firebaseData,"/ESP/BATHROOM/Temperature", tempC); //send data
  Firebase.setFloat(firebaseData,"/ESP/BATHROOM/Humidity", humi); //send data  
  // send data to garage
  Firebase.setFloat(firebaseData,"/ESP/GARAGE/Temperature", tempC); //send data
  Firebase.setFloat(firebaseData,"/ESP/GARAGE/Humidity", humi); //send data  

/************************************/

 /*******************get the main door status from app******************************/
 
  if(Firebase.get(firebaseData, "/Home_control/Mian_Door_Control"))  //check the change
  {
     if(Mian_Door_control == firebaseData.intData())
     {
      /* nothing */
     }
     else
     {
      Mian_Door_control=firebaseData.intData();
     }
      //Mian_Door_control=firebaseData.intData();
    //  Serial.print(" Mian_Door_control = ");
    //  Serial.println(firebaseData.intData());//printing the received data 

  }
/*******************get the GARAGE door status from app******************************/
 
  if(Firebase.get(firebaseData, "/ESP/GARAGE/window"))  //check the change
  {
     if(GARAGE_Door_control == firebaseData.intData())
     {
      /* nothing */
     }
     else
     {
      GARAGE_Door_control=firebaseData.intData();
     }
    
  }

/*******************************************************************************/

/*******************get the living air condition status from app******************************/
  if(Firebase.get(firebaseData, "/ESP/LIVING ROOM/AirConditioning"))  //check the change
  {
     if(living_Room_Air_condition_control == firebaseData.intData())
     {
      /* nothing */
     }
     else
     {
      living_Room_Air_condition_control=firebaseData.intData();
     }
    
  }
/*******************get the kitchen air condition status from app******************************/
  if(Firebase.get(firebaseData, "/ESP/KITCHEN/AirConditioning"))  //check the change
  {
     if(kitchen_Air_condition_control == firebaseData.intData())
     {
      /* nothing */
     }
     else
     {
      kitchen_Air_condition_control=firebaseData.intData();
     }
    
  }  
  

/*******************************************************************************/
/*******************get the kitchen light status ***************************/
 if(Firebase.get(firebaseData, "/ESP/KITCHEN/Light"))  //check the change
  {
     if(KITCHEN_Light_Control == firebaseData.intData())
     {
      // nothing 
     }
     else
     {
      KITCHEN_Light_Control=firebaseData.intData();
     }
    
  }
/********************************************************************************/
/*******************get the BATHROOM light status ***************************/
 if(Firebase.get(firebaseData, "/ESP/BATHROOM/Light"))  //check the change
  {
     if(BATHROOM_Light_Control == firebaseData.intData())
     {
      // nothing 
     }
     else
     {
      BATHROOM_Light_Control=firebaseData.intData();
     }
    
  }
/********************************************************************************/
/*******************get the GARAGE light status ***************************/
 if(Firebase.get(firebaseData, "/ESP/GARAGE/Light"))  //check the change
  {
     if(GARAGE_Light_Control == firebaseData.intData())
     {
      // nothing 
     }
     else
     {
      GARAGE_Light_Control=firebaseData.intData();
     }
    
  }
/********************************************************************************/
/*******************get the living room light status ***************************/
 if(Firebase.get(firebaseData, "/ESP/LIVING ROOM/Light"))  //check the change
  {
     if(living_Light_Control == firebaseData.intData())
     {
      // nothing 
     }
     else
     {
      living_Light_Control=firebaseData.intData();
     }
     // living_Light_Control=firebaseData.intData();
     
     // Serial.print(" living_Light_Control = ");
     // Serial.println(living_Light_Control);//printing the received data 

  }

 /****************************get living room light intensity**************/
  if(Firebase.get(firebaseData, "/ESP/LIVING ROOM/Intensity"))  //check the change
  {
     if(living_Room_Light_intensity == firebaseData.intData())
     {
      /* nothing */
     }
     else
     {
      living_Room_Light_intensity=firebaseData.intData();
     }
     // living_Room_Light_intensity=firebaseData.intData();
     //  Serial.print(" living_Room_Light_intensity = ");
     // Serial.println(living_Room_Light_intensity);//printing the received data 
  }
  /***************************get living room window status*********************/
  if(Firebase.get(firebaseData, "/ESP/LIVING ROOM/window"))  //check the change
  {
     if(living_room_window_control == firebaseData.intData())
     {
      /* nothing */
     }
     else
     {
      living_room_window_control=firebaseData.intData();
     }
    
  }
  /*****************************************************************************/

living_Room_Light_intensity_pwm = ((living_Room_Light_intensity * 255)/(100));
 ledcWrite(living_Room_Light_Channel, living_Room_Light_intensity_pwm);
//Serial.print(" living_Room_Light_intensity = ");
//Serial.println(living_Room_Light_intensity_pwm);//printing the received data 

  /***************************************************************************/
 
/******************************control living room light***************/
 
 if( living_Light_Control == 1)
 {
   digitalWrite(living_Room_Light_pin_fixed,HIGH);
 }
 else if(living_Light_Control == 0)
 {
   digitalWrite(living_Room_Light_pin_fixed,LOW);
 }
 else
 {
  //nothing
 }

/******************************control KITCHEN_Light***************/
 
 if( KITCHEN_Light_Control == 1)
 {
   digitalWrite(KITCHEN_Light_pin_fixed,HIGH);
 }
 else if(KITCHEN_Light_Control == 0)
 {
   digitalWrite(KITCHEN_Light_pin_fixed,LOW);
 }
 else
 {
  //nothing
 }

 /******************************control BATHROOM_Light***************/
 
 if( BATHROOM_Light_Control == 1)
 {
   digitalWrite(BATHROOM_Light_pin_fixed,HIGH);
 }
 else if(BATHROOM_Light_Control == 0)
 {
   digitalWrite(BATHROOM_Light_pin_fixed,LOW);
 }
 else
 {
  //nothing
 }
/******************************control GARAGE_Light***************/
 
 if( GARAGE_Light_Control == 1)
 {
   digitalWrite(GARAGE_Light_pin_fixed,HIGH);
 }
 else if(GARAGE_Light_Control == 0)
 {
   digitalWrite(GARAGE_Light_pin_fixed,LOW);
 }
 else
 {
  //nothing
 }
 

/******************************control living room air condition***************/
 
 if( living_Room_Air_condition_control == 1)
 {
   digitalWrite(living_Room_Air_condition_pin,HIGH);
 }
 else if(living_Room_Air_condition_control == 0)
 {
   digitalWrite(living_Room_Air_condition_pin,LOW);
 }
 else
 {
  //nothing
 }

/******************************control kitchen air condition***************/
 
 if( kitchen_Air_condition_control == 1)
 {
   digitalWrite(kitchen_Air_condition_pin,HIGH);
 }
 else if(kitchen_Air_condition_control == 0)
 {
   digitalWrite(kitchen_Air_condition_pin,LOW);
 }
 else
 {
  //nothing
 }
 
 
 /******************************control main door*************************/
  if( Mian_Door_control ==1)
 {
  Main_Door_servo.write(0);
  
 }
 else if(Mian_Door_control ==0)
 {
  Main_Door_servo.write(90);
 
 }
 else
 {
  /* nothing */
 }

/*******************************************************************************/
/******************************control GARAGE door*************************/
  if( (GARAGE_Door_control == 1) || (GARAGE_Door_ir_control == 1))
 {
  GARAGE_Door_servo.write(90);
  
 }
 else if((GARAGE_Door_control == 0) && (GARAGE_Door_ir_control == 0))
 {
  GARAGE_Door_servo.write(0);
 
 }
 else
 {
  /* nothing */
 }
//Serial.println(GARAGE_Door_ir_control);
/*******************************************************************************/
/**********************control living_room_window********************/
 if( living_room_window_control ==1)
 {
  living_room_window.write(90);
  
 }
 else if(living_room_window_control ==0)
 {
  living_room_window.write(0);
 
 }
 else
 {
  /* nothing */
 }
/********************************************************************/
 /*motion with light system*/
 // Current time
  now = millis();


 if((digitalRead(living_Room_Light_pir_pin) == HIGH) && (motion == false)) {
   // Serial.println("MOTION DETECTED!!!");
    motion = true;
  }

 
  // Turn off the LED after the number of seconds defined in the timeSeconds variable
  if(startTimer && ((now - lastTrigger > (timeSeconds*1000)))) 
  {
    //Serial.println("Motion stopped...");
    digitalWrite(living_Room_Light_pir_pin, LOW);
   
    startTimer = false;
    motion = false;
  }
}
/*******************************************************************/