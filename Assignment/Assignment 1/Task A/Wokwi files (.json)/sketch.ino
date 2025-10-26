// Title: Mode-Controlled LED System with OLED
// Ayesha 
// 23-NTU-CS-1020
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// --- Pin configuration ---
#define BUTTON1_PIN 32    // Mode cycle button
#define BUTTON2_PIN 33    // Reset button
#define LED1_PIN 5       // First LED
#define LED2_PIN 4       // Second LED

#define SDA_PIN 21        // I2C SDA
#define SCL_PIN 22        // I2C SCL

// --- OLED setup ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// --- Program variables ---
int currentMode = 0;      // 0=OFF, 1=Alternate, 2=ON, 3=PWM
const int totalModes = 4;
unsigned long previousMillis = 0;
const long interval = 500;  // Blink interval
bool led1State = false;
bool led2State = false;
int pwmValue = 0;
bool pwmDirection = true;  // true = increasing, false = decreasing

// Button debouncing variables
int button1State = 0;
int lastButton1State = 0;
int button2State = 0;
int lastButton2State = 0;
unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;
const unsigned long debounceDelay = 50;

// --- Mode names for display ---
const char* modeNames[] = {
  "BOTH OFF",
  "ALTERNATE BLINK",
  "BOTH ON",
  "PWM FADE"
};

void setup() {
  Serial.begin(115200);
  
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  
  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);
  
  Wire.begin(SDA_PIN, SCL_PIN);
  
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    for (;;);
  }
  
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  
  updateDisplay();
}

void loop() {
  int reading1 = digitalRead(BUTTON1_PIN);
  int reading2 = digitalRead(BUTTON2_PIN);
  
  if (reading1 != lastButton1State) {
    lastDebounceTime1 = millis();
  }
  if ((millis() - lastDebounceTime1) > debounceDelay) {
    if (reading1 != button1State) {
      button1State = reading1;
      if (button1State == LOW) {
        cycleMode();
      }
    }
  }
  if (reading2 != lastButton2State) {
    lastDebounceTime2 = millis();
  }
  if ((millis() - lastDebounceTime2) > debounceDelay) {
    if (reading2 != button2State) {
      button2State = reading2;
      if (button2State == LOW) {
        resetToOff();
      }
    }
  }
  lastButton1State = reading1;
  lastButton2State = reading2;
  
  switch(currentMode) {
    case 0:
      digitalWrite(LED1_PIN, LOW);
      digitalWrite(LED2_PIN, LOW);
      break;
      
    case 1:
      handleAlternateBlink();
      break;
      
    case 2:
      digitalWrite(LED1_PIN, HIGH);
      digitalWrite(LED2_PIN, HIGH);
      break;
      
    case 3:
      handlePWMFade();
      break;
  }
}
void cycleMode() {
  currentMode = (currentMode + 1) % totalModes;
  updateDisplay();
}

void resetToOff() {
  currentMode = 0;

  // Force LEDs OFF instantly
  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);

  updateDisplay();
}
void handleAlternateBlink() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    led1State = !led1State;
    led2State = !led1State;
    
    digitalWrite(LED1_PIN, led1State);
    digitalWrite(LED2_PIN, led2State);
  }
}
void handlePWMFade() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= 20) {
    previousMillis = currentMillis;
    
    if (pwmDirection) {
      pwmValue += 5;
      if (pwmValue >= 255) {
        pwmValue = 255;
        pwmDirection = false;
      }
    } else {
      pwmValue -= 5;
      if (pwmValue <= 0) {
        pwmValue = 0;
        pwmDirection = true;
      }
    }
    
    analogWrite(LED1_PIN, pwmValue);
    analogWrite(LED2_PIN, pwmValue);
  }
}
void updateDisplay() {
  display.clearDisplay();
  display.setTextSize(1);
  
  display.setCursor(0, 0);
  display.println("LED CONTROL SYSTEM");
  display.drawLine(0, 10, 127, 10, SSD1306_WHITE);
  
  display.setCursor(0, 15);
  display.print("MODE: ");
  
  display.setTextSize(2);
  display.setCursor(0, 25);
  display.println(modeNames[currentMode]);
  
  display.display();
}