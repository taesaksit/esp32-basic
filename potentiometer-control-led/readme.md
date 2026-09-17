# 🎛️ หรี่ไฟ LED ด้วย Potentiometer แสดงผลบน OLED ด้วย ESP32

## 🔌 การต่อวงจร

| ESP32    | อุปกรณ์                              |
| -------- | ------------------------------------ |
| 3V3      | Pot ขานอกข้างหนึ่ง และ OLED VDD      |
| GND      | Pot ขานอกอีกข้าง, LED ขา − และ OLED GND |
| GPIO 32  | Pot ขากลาง                           |
| GPIO 25  | LED ขา + (ผ่าน R 220Ω)               |
| GPIO 21  | OLED SDA                             |
| GPIO 22  | OLED SCL                             |

```
ESP32
  │
  ├── 3V3 ──────┐
  │             │
  │          [แถว +]
  │             ├── Pot ขานอก
  │             └── OLED VDD
  │
  ├── GND ──────┐
  │             │
  │          [แถว -]
  │             ├── Pot ขานอกอีกข้าง
  │             ├── LED (-)
  │             └── OLED GND
  │
  ├── GPIO 32 ───── Pot ขากลาง
  │
  ├── GPIO 25 ── [220Ω] ── LED (+)
  │
  ├── GPIO 21 ───── OLED SDA
  │
  └── GPIO 22 ───── OLED SCL
```

## ⚙️ หลักการทำงาน

- อ่านค่า ADC 0–4095 จาก Pot ที่ GPIO 32
- แปลงเป็น PWM 0–255 ส่งไปที่ LED GPIO 25 (`ledc`)
- แปลงเป็น 0–100% แสดงกลางจอ OLED 128×32 พร้อมส่งออก Serial

## 📸 ผลลัพธ์

| 0% LED ดับ | 70% LED สว่าง |
| :---------: | :------------: |
| <img src="few-light.png" width="380" alt="จอ OLED แสดง 0% LED ดับ"> | <img src="full-light.png" width="380" alt="จอ OLED แสดง 70% LED สว่าง"> |
