/*
1----> 0xB6, 0xF5, 0x25, 0x8A --->the song 
2----> 0x34, 0x9, 0x1, 0xA3   --->
3----> 0xD0, 0xBB, 0x93, 0x8A
4----> 0xFF, 0xB1, 0x93, 0x8A
5----> 0xB7, 0x79, 0x25, 0x8A
6----> 0xAD, 0x1B, 0xE0, 0x21
*/
#include <SPI.h>
#include <MFRC522.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

// ---------- RFID ----------
#define SS_PIN 10
#define RST_PIN 9
MFRC522 rfid(SS_PIN, RST_PIN);

// ---------- DFPlayer ----------
SoftwareSerial mySerial(8, 7); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

// ---------- CARD UIDs (REPLACE THESE WITH YOUR REAL ONES) ----------
const byte cardABC[]      = {0xB6, 0xF5, 0x25, 0x8A}; // Alphabet
const byte cardNUMBERS[]  = {0x34, 0x9, 0x1, 0xA3}; // Numbers
const byte cardANIMALS[]  = {0xD0, 0xBB, 0x93, 0x8A}; // Animals
const byte cardFRUITS[]   = {0xFF, 0xB1, 0x93, 0x8A}; // Fruits
const byte cardCOLORS[]   = {0xB7, 0x79, 0x25, 0x8A}; // Colors
const byte cardHELLO[]    = {0xAD, 0x1B, 0xE0, 0x21}; // Greetings

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  SPI.begin();
  rfid.PCD_Init();

  if (!myDFPlayer.begin(mySerial)) {
    Serial.println("DFPlayer Error");
    while (true);
  }

  myDFPlayer.volume(30); // Fixed volume (0 to 30)
  Serial.println("Teachy Ready - Scan a card");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  if (compareUID(rfid.uid.uidByte, cardABC)) {
    Serial.println("Alphabet");
    myDFPlayer.play(1); // 0001.mp3
  }
  else if (compareUID(rfid.uid.uidByte, cardNUMBERS)) {
    Serial.println("Numbers");
    myDFPlayer.play(2); // 0002.mp3
  }
  else if (compareUID(rfid.uid.uidByte, cardANIMALS)) {
    Serial.println("Animals");
    myDFPlayer.play(3); // 0003.mp3
  }
  else if (compareUID(rfid.uid.uidByte, cardFRUITS)) {
    Serial.println("Fruits");
    myDFPlayer.play(4); // 0004.mp3
  }
  else if (compareUID(rfid.uid.uidByte, cardCOLORS)) {
    Serial.println("Colors");
    myDFPlayer.play(5); // 0005.mp3
  }
  else if (compareUID(rfid.uid.uidByte, cardHELLO)) {
    Serial.println("Greetings");
    myDFPlayer.play(6); // 0006.mp3
  }
  else {
    Serial.println("Unknown Card");
  }

  rfid.PICC_HaltA();
  delay(1500); // prevent double reading
}

// ---------- UID Compare Function ----------
bool compareUID(byte *uid, const byte *knownUID) {
  for (byte i = 0; i < 4; i++) {
    if (uid[i] != knownUID[i]) return false;
  }
  return true;
}
