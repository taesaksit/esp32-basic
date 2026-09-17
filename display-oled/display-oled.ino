#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_ADDR 0x3C
#define OLED_RESET -1
#define LED_PIN 2

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

void setup() {

  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  // I2C: SDA = GPIO 21, SCL = GPIO 22
  Wire.begin(21, 22);

  // เริ่มต้น OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("OLED FAILED");
    while (true);
  }

  Serial.println("OLED OK");

  // ล้างหน้าจอ
  display.clearDisplay();

  // ตั้งค่าข้อความ
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  // ตำแหน่งข้อความ
  display.setCursor(10, 8);

  // แสดงข้อความ
  display.println("HELLO");

  // แสดงผลบน OLED
  display.display();
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(1000);

  digitalWrite(LED_PIN, LOW);
  delay(1000);

}