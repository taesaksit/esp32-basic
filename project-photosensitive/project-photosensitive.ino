#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ==================== DHT11 ====================

#define DHT_PIN 4
#define DHT_TYPE DHT11
DHT dht(DHT_PIN, DHT_TYPE);


// ==================== OLED ====================

// OLED ขนาด 128x32
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

// OLED Address
#define OLED_ADDR 0x3C

// ไม่มี Reset แยก
#define OLED_RESET -1

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET);


// ==================== Photosensitive ====================

// ใช้ AO ของ Photosensitive
// AO ต่อกับ GPIO34
#define LIGHT_PIN 34

// กำหนดค่า Threshold สำหรับตรวจสอบความมืด
// ต้องทดลองปรับค่าตามสภาพแสงจริง
#define DARK_THRESHOLD 3500


// ==================== RGB LED ====================

#define RED_PIN 32
#define GREEN_PIN 33
#define BLUE_PIN 25


// ==================== OLED Timer ====================

// กำหนดเวลาสลับหน้าจอ 2 วินาที
unsigned long previousMillis = 0;

const unsigned long DISPLAY_INTERVAL = 2000;

// 0 = Temperature
// 1 = Humidity
int displayMode = 0;


void setup() {

  // เปิด Serial Monitor
  Serial.begin(115200);

  // เริ่มต้น DHT11
  dht.begin();

  // AO เป็น Analog Input
  pinMode(LIGHT_PIN, INPUT);

  // RGB LED เป็น Output
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // เริ่มต้น I2C
  // SDA = GPIO21
  // SCL = GPIO22
  Wire.begin(21, 22);

  // เริ่มต้น OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {

    Serial.println("OLED FAILED");

    while (true)
      ;
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
}


void loop() {

  // ==================== อ่าน DHT11 ====================
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // ==================== อ่าน Photosensitive ====================
  // อ่านค่าความสว่างจาก AO
  // ESP32 ADC 0 - 4095
  int lightValue = analogRead(LIGHT_PIN);

  // ==================== ควบคุม RGB LED ====================
  // ถ้าค่ามากกว่า Threshold ให้ถือว่ามืด
  if (lightValue > DARK_THRESHOLD) {

    // มืด → เปิด RGB เป็นสีขาว
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(BLUE_PIN, HIGH);

  } else {

    // สว่าง → ปิด RGB
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW);
  }


  // ==================== สลับหน้าจอ OLED ====================
  // ตรวจสอบเวลาว่าครบ 2 วินาทีหรือยัง
  if (millis() - previousMillis >= DISPLAY_INTERVAL) {

    // บันทึกเวลาปัจจุบัน
    previousMillis = millis();

    // เปลี่ยนหน้าจอ
    if (displayMode == 0) {
      displayMode = 1;
    } else {
      displayMode = 0;
    }
  }


  // ==================== แสดงผล OLED ====================
  display.clearDisplay();

  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);


  // ==================== Temperature ====================

  if (displayMode == 0) {

    // ตรวจสอบว่า DHT11 อ่านค่าได้หรือไม่
    if (isnan(temperature)) {

      display.setCursor(20, 5);
      display.print("--");

    } else {

      // แสดงอุณหภูมิ
      display.setCursor(10, 5);
      display.print(temperature, 1);
      display.print((char)247);
      display.print("C");
    }
  }


  // ==================== Humidity ====================

  else {

    // ตรวจสอบว่า DHT11 อ่านค่าได้หรือไม่
    if (isnan(humidity)) {

      display.setCursor(20, 5);
      display.print("--");

    } else {

      // แสดงความชื้น
      display.setCursor(10, 5);
      display.print(humidity, 1);

      // แสดง %
      display.print("%");
    }
  }


  // ส่งข้อมูลไป OLED
  display.display();


  // ==================== Serial Monitor ====================

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Light AO: ");
  Serial.println(lightValue);

  Serial.println();
}