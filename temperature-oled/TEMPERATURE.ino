#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// DHT11
#define DHT_PIN 4
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);

// OLED 0.91" 128x32
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  -1);

// Setting
unsigned long previousMillis = 0;
const unsigned long interval = 3000;  // 3 วินาที

bool showTemperature = true;

void setup() {

  Serial.begin(115200);

  // Start DHT11
  dht.begin();

  // Start OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED FAILED");

    while (true)
      ;
  }

  // เริ่มต้นหน้าจอ
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(34, 12);
  display.print("Starting...");

  display.display();

  delay(2000);
}

void loop() {

  // อ่านค่าจาก DHT11
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // ตรวจสอบค่าที่อ่านได้
  if (isnan(temperature) || isnan(humidity)) {

    Serial.println("DHT11 READ FAILED");


    display.clearDisplay();

    display.setTextSize(2);
    display.setCursor(25, 12);
    display.print("DHT11 ERROR");

    display.display();

    delay(2000);
    return;
  }

  // สลับหน้าจอทุก 3 วินาที

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {

    previousMillis = currentMillis;

    showTemperature = !showTemperature;
  }

  // OLED

  display.clearDisplay();

  // Temperature
  if (showTemperature) {

    // Title
    display.setTextSize(1);
    display.setCursor(38, 0);
    display.print("TEMPERATURE");

    // Value
    display.setTextSize(2);
    display.setCursor(20, 14);

    display.print(temperature, 1);
    display.print(" C");
  }

  // Humidity
  else {

    // Title
    display.setTextSize(1);
    display.setCursor(43, 0);
    display.print("HUMIDITY");

    // Value
    display.setTextSize(2);
    display.setCursor(20, 14);

    display.print(humidity, 1);
    display.print(" %");
  }

  display.display();

  // Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature, 1);
  Serial.print(" C | Humidity: ");
  Serial.print(humidity, 1);
  Serial.println(" %");

  delay(100);
}