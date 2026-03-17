#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <RTClib.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
RTC_DS3231 rtc;

// متغيرات لاسم المريض ورقم الـ ID ورقم الهاتف
String patientName = "Mohamed Ali";
unsigned long patientID = 30005555555;
String phoneNumber = "0102846872";
unsigned long previousMillis = 0;
const long interval = 15000; // تحديث بيانات المريض كل 15 ثانية
const long reminderDuration = 5000; // مدة ظهور رسالة التذكير بالدواء (5 ثوانٍ)

void setup() {
  Serial.begin(9600);
  
  // بدء التواصل مع RTC
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  // بدء التواصل مع الشاشة OLED
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // تغيير العنوان إذا لزم الأمر
  display.display();
  delay(2000);

  // مسح البيانات السابقة من الشاشة
  display.clearDisplay();

  // ضبط حجم النص ولونه وموضعه
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  // طباعة رسالة البداية
  display.println("Initializing...");
  display.display();
  delay(2000);
}

void loop() {
  // الحصول على الوقت الحالي من RTC
  DateTime now = rtc.now();

  // تحقق من مرور الوقت لعرض رسالة التذكير بالدواء
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis <= reminderDuration) {
    // مسح البيانات السابقة من الشاشة
    display.clearDisplay();

    // طباعة رسالة "you need to take med"
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("you need to take med");
    
    // عرض البيانات على الشاشة
    display.display();
  } else {
    // طباعة اسم المريض
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("Patient: ");
    display.println(patientName);
    
    display.setCursor(0, 10); // إضافة مسافة بين السطور
    display.print("Phone: ");
    display.println(phoneNumber);
    
    display.setCursor(0, 20); // إضافة مسافة بين السطور
    // طباعة رقم الـ ID
    display.print("ID: ");
    display.println(patientID);
    
    display.setCursor(0, 30); // إضافة مسافة بين السطور
    // طباعة الوقت الحالي
    display.setTextSize(2);
    display.print(now.hour(), DEC);
    display.print(':');
    if (now.minute() < 10) {
      display.print('0');
    }
    display.print(now.minute(), DEC);
    display.print(':');
    if (now.second() < 10) {
      display.print('0');
    }
    display.println(now.second(), DEC);
    
    // عرض البيانات على الشاشة
    display.display();
  }

  // تحديث الوقت السابق لظهور رسالة التذكير بالدواء
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
  }
  
  // انتظار ثانية قبل تحديث الشاشة مرة أخرى
  delay(1000);
}
