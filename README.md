# Embedded IoT Work – Ayesha (23-NTU-CS-1020)

This repository contains my weekly lab tasks and assignments for the **Embedded IoT** course.  
Each week focuses on practical experiments using **ESP32**, **OLED display**, **LEDs**, **Buzzers**, and various **sensors**.

---

## Folder Structure

### Assignment
Contains the written assignment file.
- **Ayesha(1020).docx**

---

### Embedded IoT Project
Focus: **Complete Project Demonstration**

Includes:
- `Project Video` – Demonstrates the working of the Embedded IoT project  
- `Documentation` – Screenshots of working system, architecture diagram, flowchart, and project explanation  
- `Project PPT` – Describes code functionality and working logic  

---

###  Week 4
Focus: **OLED Display Programming**

Includes:
- `oled_demo.ino` – Basic OLED setup and display demo  
- `avatar_display.ino` – Displaying a custom avatar  
- `logo_display.ino` – Showing logo or bitmap  
- `smiley_display.ino` – OLED smiley face design  
- `name_id_display.ino` – Displaying Name and ID on screen  

---

###  Week 5
Focus: **LED and Buzzer Control with PWM**

Includes:
- Experiments using **different frequencies** and **same frequencies** for multiple LEDs  
- Tasks to demonstrate **duty cycle variations** (same and different duty cycles)  
- Source code files for LED blinking and buzzer tone generation  

---

###  Week 6
Focus: **Sensors Integration (DHT & LDR)**

Includes:
- `dht_sensor.ino` – Reading temperature & humidity using DHT22  
- `ldr_sensor.ino` – Reading light intensity  
- `combined_dht_ldr.ino` – Displaying both sensor readings on OLED  

---

### Week 9
Focus: **ESP32 WiFi & Web Server**

Includes:
- `wifi_connection.ino` – Connecting ESP32 to WiFi and displaying IP address  
- `wifi_scan.ino` – Scanning and listing available WiFi networks  
- `esp32_webserver_led.ino` – Creating a web server to control built-in LED using a browser  

---

### Week 10
Focus: **DHT11 Sensor with OLED & Web Server**

Includes:
- `dht11_oled_button.ino` – Reading temperature and humidity from DHT11 using a push button and displaying values on OLED  
- `dht11_webserver.ino` – Displaying DHT11 temperature and humidity on both OLED and a web page using ESP32 web server  

---

### Week 12
Focus: **Blynk Simulation with Wokwi**

Includes:
- `blynk_wokwi_dht11.ino` – Reading temperature and humidity from DHT11, monitoring button state, and displaying values on OLED and blynk  

---

### Week 13
Focus: **MQTT Communication (Publisher & Subscriber)**

Includes:
- `mqtt_publisher_dht11.ino` – Publishing DHT11 temperature and humidity data to MQTT broker topics using ESP32  
- `mqtt_subscriber_oled.ino` – Subscribing to MQTT temperature topic and displaying received data on OLED  

---

### Week 14
Focus: **MQTT One Publisher – Multiple Subscribers**

Includes:
- `mqtt_publisher.ino` – Publishing sensor data to MQTT broker from a single ESP32 publisher  
- `mqtt_subscriber_1.ino` – First subscriber receiving and displaying published data  
- `mqtt_subscriber_2.ino` – Second subscriber receiving the same data from the publisher  

---

### Week 15
Focus: **Node-RED Dashboard with MQTT**

Includes:
- MQTT integration between ESP32 publisher and subscriber nodes in Node-RED  
- Visualization of sensor data on a Node-RED dashboard using MQTT topics  
- Real-time monitoring of published data through Node-RED UI  

---

##  Hardware Used
- ESP32 Development Board  
- OLED Display (SSD1306)  
- DHT11 Temperature & Humidity Sensor  
- LDR (Light Dependent Resistor)  
- LED & Buzzer Modules  

---

##  Learning Outcomes
- Interfacing sensors and actuators with ESP32  
- Using PWM signals for LED and buzzer control  
- Displaying data on OLED using I2C communication  
- Writing clean, modular Arduino code  

---

## Author
**Ayesha (23-NTU-CS-1020)**  
BS Computer Science – National Textile University, Faisalabad  
