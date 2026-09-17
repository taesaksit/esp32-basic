# 🖥️ แสดงข้อความบนจอ OLED ด้วย ESP32


## 🔌 การต่อวงจร

| ESP32    | OLED      |
| -------- | --------- |
| 3V3      | VCC / VDD |
| GND      | GND       |
| GPIO 21  | SDA       |
| GPIO 22  | SCL       |

```
ESP32
  │
  ├── 3V3 ───────── OLED VCC / VDD
  │
  ├── GND ───────── OLED GND
  │
  ├── GPIO 21 ───── OLED SDA
  │
  └── GPIO 22 ───── OLED SCL
```

## 📸 ผลลัพธ์

<p>
  <img src="oled.png" width="600" alt="จอ OLED แสดงข้อความ HELLO">
</p>
