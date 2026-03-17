/*******for ESP8266************/
//#include <ESP8266WiFi.h>
//#include <FirebaseESP8266.h>
/***********END***************/
/*******for ESP32************/
#include <WiFi.h>
#include <FirebaseESP32.h>
/***********END***************/

/*****software serial*********/
#include<SoftwareSerial.h>
SoftwareSerial Atmega32(D3,D2);



#define FIREBASE_HOST "newone-ffd79-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "ZLuMo5NVZ5jc4S5g6SGyuNpqJt1WwnRKP4aRzsdy"
#define WIFI_SSID "iphone"
#define WIFI_PASSWORD "mh123456789"
  


// Declare the Firebase Data object in the global scope
FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;
FirebaseJson json;


void setup()
{

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
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");

 
  

  Serial.println("------------------------------------");
  Serial.println("Connected...");
  
}

void loop()
{ int val=0;
int fire;
if(WiFi.status()!= WL_CONNECTED)
{
 ESP.restart();
 Serial.println("trying to connect to WiFi");
 }
 else{
   Serial.println("WiFi - OK");
 }
   /**
    * 
    Vrdata = analogRead(Vresistor);
 int Sdata = map(Vrdata,0,4095,0,1000);
 Serial.println(Sdata); 
delay(100); 
  json.set("/data", Sdata);
    Firebase.updateNode(firebaseData,"/Sensor",json);

  */for(val=0;val<=100;val++){
  Firebase.setInt(firebaseData, "/Car/Moves/Forward", val);
  Firebase.setInt(firebaseData, "/Car/Moves/Backward", val);
  Firebase.setInt(firebaseData, "/Car/Moves/Left", val);
  Firebase.setInt(firebaseData, "/Car/Moves/Right", val);

  Firebase.setInt(firebaseData, "/Car/ARM/POS-1", val);
  Firebase.setInt(firebaseData, "/Car/ARM/POS-2", val);
  Firebase.setInt(firebaseData, "/Car/ARM/POS-3", val);
  Firebase.setInt(firebaseData, "/Car/ARM/POS-4", val);
  Firebase.setInt(firebaseData, "/Car/ARM/POS-5", val); 

  Firebase.setInt(firebaseData, "/Greenhouse/Tempreture/LM35-1", val); 
  Firebase.setInt(firebaseData, "/Greenhouse/Tempreture/LM35-2", val); 
  
  Firebase.setInt(firebaseData, "/Greenhouse/Planets/Planet-1", val); 
  Firebase.setInt(firebaseData, "/Greenhouse/Planets/Planet-2", val); 
  Firebase.setInt(firebaseData, "/Greenhouse/Planets/Planet-3", val); 
  Firebase.setInt(firebaseData, "/Greenhouse/Planets/Planet-4", val); 
  Firebase.setInt(firebaseData, "/Greenhouse/Planets/Planet-5", val); 
  Firebase.setInt(firebaseData, "/Greenhouse/Planets/Planet-6", val);

 
  Firebase.setInt(firebaseData, "/Greenhouse/Gas", val);
  Firebase.setInt(firebaseData, "/Greenhouse/Flame", val);

  Firebase.setInt(firebaseData, "/Greenhouse-Car", val);

  


  
  delay(200);
  }
 if(Firebase.get(firebaseData, "/fire1"))
  {
     Serial.print("Int Number 1 = ");
      Serial.println(firebaseData.intData());

  }
  if(Firebase.get(firebaseData, "/fire2"))
  {
     Serial.print("Int Number 2 = ");
      Serial.println(firebaseData.intData());

  }
 
}
