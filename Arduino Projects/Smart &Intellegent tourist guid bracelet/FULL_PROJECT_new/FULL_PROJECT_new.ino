#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <MFRC522.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

// إعدادات OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// إعدادات RFID
#define SS_PIN 10
#define RST_PIN 9
MFRC522 rfid(SS_PIN, RST_PIN);

// إعدادات DFPlayer
SoftwareSerial mySerial(8,7); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

// تعريف الأزرار
#define BUTTON_PLAY_PAUSE_PIN 4  // زر لتشغيل/إيقاف الملف
#define BUTTON_RESTART_PIN 5       // زر لإعادة تشغيل الملف
#define POT_PIN A0                 // دبوس قراءة المقاومة المتغيرة


int selectedFile = 1; // الملف المحدد
int cardType = 0; // نوع البطاقة (1 أو 2)
int volume = 15; // مستوى الصوت (من 0 إلى 30)
bool isPlaying = false; // حالة التشغيل
int language_code = 0;
const int language_pin = 3;
bool language_pin_flag = 0;
bool BUTTON_PLAY_PAUSE_flag =0;
bool BUTTON_RESTART_flag =0;

const byte uid1[] = {0x13, 0x1B, 0xE4, 0x29}; // بطاقة 1
const byte uid2[] = {0xE3, 0xC5, 0xD1, 0x2A}; // بطاقة 2

void setup() {
    Serial.begin(9600);
    mySerial.begin(9600);
    display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
    display.clearDisplay();
  
    // عرض الشعار في البداية
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(45, 0);
    display.print("SZW");
    display.setCursor(50, 20);
    display.print("BY");
    display.setCursor(5, 40);
    display.print("ZENVO TEAM");
    display.display();
    delay(2000); // تأخير لإظهار الشعار

    SPI.begin();
    rfid.PCD_Init();

    if (!myDFPlayer.begin(mySerial)) 
    {
        Serial.println("DFPlayer initialization failed!");
        while (true);
    }

    myDFPlayer.volume(volume); // تعيين مستوى الصوت الابتدائي

    // إعداد الأزرار كمدخلات
    pinMode(BUTTON_PLAY_PAUSE_PIN, INPUT_PULLUP);
    pinMode(BUTTON_RESTART_PIN, INPUT_PULLUP);
    pinMode(language_pin,INPUT_PULLUP); 
   
    }

void loop() {
    // قراءة مستوى الصوت من المقاومة المتغيرة
    int potValue = analogRead(POT_PIN); // قراءة القيمة من المقاومة المتغيرة
    volume = map(potValue, 0, 1023, 0, 30); // تحويل القيمة إلى نطاق مستوى الصوت (0 إلى 30)
    if((digitalRead(language_pin) == LOW) && (language_pin_flag == 0))
    {
      language_pin_flag = 1;
       language_code++;
       
       if(language_code == 8)
        {
          language_code = 0;
        }
      else
          {
    // nothing 
          }
    }
    else if((digitalRead(language_pin) == HIGH) && (language_pin_flag == 1))
    {
      language_pin_flag = 0;
    }
    else
    {
      
      /* nothing */
    }
    // تحديث مستوى الصوت فقط إذا تغير
    static int lastVolume = -1; // تخزين آخر مستوى صوت
    static int lastLanguage_Code = -1;
    if ((volume != lastVolume) || (language_code != lastLanguage_Code)) 
    {
        lastVolume = volume; // تحديث القيمة الأخيرة
        lastLanguage_Code = language_code ;
        myDFPlayer.volume(volume); // تعيين مستوى الصوت

        // عرض مستوى الصوت على الشاشة
        display.clearDisplay();
        display.setCursor(0, 0);
        display.setTextSize(1);
        display.print("Volume: ");
        display.print(volume);
        display.setCursor(0, 20);
        display.print("Language :");
        display.print(language_code);
        display.display();
        
    }
  
      


    // قراءة بيانات RFID
    if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) 
    {
        if (memcmp(rfid.uid.uidByte, uid1, rfid.uid.size) == 0)
         { // بطاقة 1
            cardType = 1; // تعيين نوع البطاقة إلى 1
            selectedFile = 1 + language_code ; // البداية من 1
            myDFPlayer.play(selectedFile); // تشغيل الملف
            isPlaying = true; // تعيين حالة التشغيل
         }
         else if (memcmp(rfid.uid.uidByte, uid2, rfid.uid.size) == 0)
          { // بطاقة 2
            cardType = 2; // تعيين نوع البطاقة إلى 2
            selectedFile = 9 + language_code; // البداية من 9
            myDFPlayer.play(selectedFile); // تشغيل الملف
            isPlaying = true; // تعيين حالة التشغيل
          }

       
        display.clearDisplay();
        display.setCursor(0, 0);
        display.setTextSize(2);
        display.print("Listen");
        display.setCursor(0, 20);
        display.print("please :)"); 
        display.display();
       
        rfid.PICC_HaltA(); // إيقاف بطاقة RFID
    }

    // إذا تم ضغط زر تشغيل/إيقاف الملف
    if ((digitalRead(BUTTON_PLAY_PAUSE_PIN) == LOW) && (BUTTON_PLAY_PAUSE_flag == 0)) 
    {
      BUTTON_PLAY_PAUSE_flag = 1;
        if (isPlaying) 
        {
            myDFPlayer.pause(); // إيقاف التشغيل مؤقتًا
            isPlaying = false; // تحديث الحالة
            display.clearDisplay();
            display.setCursor(0, 0);
            display.setTextSize(1);
            display.print("Paused File: ");
            display.print(selectedFile);
            display.display();
        } 
        else 
        {
            myDFPlayer.start(); // استئناف التشغيل
            isPlaying = true; // تحديث الحالة
            display.clearDisplay();
            display.setCursor(0, 0);
            display.setTextSize(1);
            display.print("Playing File: ");
            display.print(selectedFile);
            display.display();
        }
    }
    else if((digitalRead(BUTTON_PLAY_PAUSE_PIN) == HIGH) && (BUTTON_PLAY_PAUSE_flag == 1))
    {
        BUTTON_PLAY_PAUSE_flag = 0;
    }
    else
    {
      /*nothing*/
    }

    // إذا تم ضغط زر إعادة التشغيل
    if ((digitalRead(BUTTON_RESTART_PIN) == LOW) && (BUTTON_RESTART_flag == 0)) 
    {
        BUTTON_RESTART_flag = 1;
        myDFPlayer.play(selectedFile); // إعادة تشغيل الملف المحدد
        display.clearDisplay();
        display.setCursor(0, 0);
        display.setTextSize(1);
        display.print("Restarting File: ");
        display.print(selectedFile);
        display.display();
    }
    else if((digitalRead(BUTTON_RESTART_PIN) == HIGH) && (BUTTON_RESTART_flag == 1))
    {
       BUTTON_RESTART_flag = 0;
    }
    else
    {
      /*nothing*/
    }

}
