# 🌡️ วัดอุณหภูมิ–ความชื้น แสดงผลบน OLED ด้วย ESP32

## 🔌 การต่อวงจร

| ESP32    | อุปกรณ์        |
| -------- | -------------- |
| 3V3      | DHT11 ขา + และ OLED VDD |
| GND      | DHT11 ขา − และ OLED GND |
| GPIO 4   | DHT11 ขา S     |
| GPIO 21  | OLED SDA       |
| GPIO 22  | OLED SCL       |

```
ESP32
  │
  ├── 3V3 ──────┐
  │             │
  │          [แถว +]
  │             ├── DHT11 +
  │             └── OLED VDD
  │
  ├── GND ──────┐
  │             │
  │          [แถว -]
  │             ├── DHT11 -
  │             └── OLED GND
  │
  ├── GPIO 4 ─────── DHT11 S
  │
  ├── GPIO 21 ────── OLED SDA
  │
  └── GPIO 22 ────── OLED SCL
```



## 📸 ผลลัพธ์

| 🌡️ อุณหภูมิ | 💧 ความชื้น |
| :----------: | :---------: |
| <img src="temp.png" width="380" alt="จอ OLED แสดงอุณหภูมิ 23.0 C"> | <img src="hum.png" width="380" alt="จอ OLED แสดงความชื้น 60.0 %"> |
