#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define LED_PIN 25

#define OLED_RESET -1
#define OLED_ADDRESS 0x3C

#define POT_PIN 32

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET);

void setup() {
  Serial.begin(115200);

  Wire.begin(21, 22);
  // PWM
  ledcAttach(LED_PIN, 5000, 8);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println("OLED failed");
    while (true)
      ;
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.display();
}

void loop() {

  // อ่าน Potentiometer
  int adcValue = analogRead(POT_PIN);

  // แปลง ADC 0-4095 → PWM 0-255
  int pwmValue = map(adcValue, 0, 4095, 0, 255);
  int percent = map(adcValue, 0, 4095, 0, 100);

  // ส่ง PWM ไป LED
  ledcWrite(LED_PIN, pwmValue);

  // แสดงบน Serial
  Serial.print("Percent: ");
  Serial.print(percent);
  Serial.println("%");

  // OLED
  display.clearDisplay();

  display.setTextSize(3);

  String text = String(percent) + "%";

  int16_t x1, y1;
  uint16_t w, h;

  display.getTextBounds(
    text,
    0,
    0,
    &x1,
    &y1,
    &w,
    &h);

  // จัดให้อยู่กึ่งกลาง
  int x = (SCREEN_WIDTH - w) / 2;
  int y = (SCREEN_HEIGHT - h) / 2;

  display.setCursor(x, y);
  display.print(text);

  display.display();

  delay(100);
}