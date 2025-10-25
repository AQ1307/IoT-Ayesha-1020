# ESP32 LED Control System with OLED

---

## **Overview**
ESP32-based LED control system with **2 LEDs, 2 buttons, a buzzer, and an OLED display**.  
Control LEDs in multiple modes and see the current mode on the OLED.

---

## **Features**
- **LED Modes:**  
  1. Both OFF  
  2. Alternate Blink  
  3. Both ON  
  4. PWM Fade  
- **Button 1** → Cycle modes  
- **Button 2** → Reset to OFF  
- **Buzzer** feedback  
- **OLED Display** shows current mode  
- Non-blocking timing using `millis()`  

---

## **Hardware**
- ESP32 Development Board  
- 2 LEDs  
- 2 Push Buttons  
- 1 Buzzer  
- 128x64 OLED (I2C)  
- Breadboard & jumper wires  

---

## **Pin Configuration**

| Component | Pin |
|-----------|-----|
| LED1      | 5   |
| LED2      | 4   |
| Button1   | 32  |
| Button2   | 33  |
| Buzzer    | 26  |
| OLED SDA  | 21  |
| OLED SCL  | 22  |

---

## **Libraries**
- `Arduino.h` – basic Arduino functions  
- `Wire.h` – I2C communication  
- `Adafruit_GFX.h` – graphics for OLED  
- `Adafruit_SSD1306.h` – OLED control  

---

## **Usage**
1. Install the required libraries in Arduino IDE.  
2. Connect components according to the pin table.  
3. Upload the code to the ESP32.  
4. Press **Button 1** to cycle LED modes.  
5. Press **Button 2** to reset LEDs to OFF.  

---

## **Wokwi Link**
Task A:   https://wokwi.com/projects/445625588391625729
Task B:   https://wokwi.com/projects/445499738958735361

<img width="481" height="391" alt="TASK A" src="https://github.com/user-attachments/assets/1e7d03a9-fc28-4871-b9d0-312910c1a3fe" />
<img width="480" height="339" alt="TASK B" src="https://github.com/user-attachments/assets/dfb982df-e808-4709-b87b-2d2f4394975a" />


