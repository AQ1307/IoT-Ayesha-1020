// Title: Mode-Controlled LED System with OLED
// Ayesha 
// 23-NTU-CS-1020

#include <Arduino.h>
#include <Wire.h>
// .... Graphics library...
#include <Adafruit_GFX.h>
// .... Graphics Driver to show graphics on oled
#include <Adafruit_SSD1306.h>

// ... Pin configuration of button,LED
#define BUTTON1_PIN 33    
#define BUTTON2_PIN 35    
#define LED1_PIN 2       
#define LED2_PIN 4       

#define SDA_PIN 21        // Data Pin
#define SCL_PIN 22        // Clock pin

// ... OLED setup...
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ... variable declarations
int currentMode = 0;      
// 0=OFF, 1=Alternate, 2=ON, 3=PWM
const int totalModes = 4;

unsigned long previousMillis = 0;
//.... led Blink interval ....
const long interval = 500;  

bool led1State = false;
bool led2State = false;

int pwmValue = 0;
bool pwmDirection = true;

//.... Button states .....
int button1State = 0;
int lastButton1State = 0;
int button2State = 0;
int lastButton2State = 0;
unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;
// debounce delay 50ms
const unsigned long debounceDelay = 50;

//.... names of mode....
const char* modeNames[] = {
  "BOTH OFF",
  "ALTERNATE BLINK",
  "BOTH ON",
  "PWM FADE"
};
// different functions...
void cycleMode();
void resetToOff();
void handleAlternateBlink();
void handlePWMFade();
void updateDisplay();

void setup() {
  Serial.begin(115200);

  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);

  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);

  // LEDC Setup for PWM fade....
  ledcSetup(0, 4000, 10);
  ledcAttachPin(LED1_PIN, 0);

  ledcSetup(1, 4000, 10);
  ledcAttachPin(LED2_PIN, 1);

  Wire.begin(SDA_PIN, SCL_PIN);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    while (1);
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
    case 0:   // Both OFF
      ledcDetachPin(LED1_PIN);
      ledcDetachPin(LED2_PIN);
      digitalWrite(LED1_PIN, LOW);
      digitalWrite(LED2_PIN, LOW);
      break;

    case 1:   // Alternate blink
      ledcDetachPin(LED1_PIN);
      ledcDetachPin(LED2_PIN);
      handleAlternateBlink();
      break;

    case 2:   // Both ON
      ledcDetachPin(LED1_PIN);
      ledcDetachPin(LED2_PIN);
      digitalWrite(LED1_PIN, HIGH);
      digitalWrite(LED2_PIN, HIGH);
      break;

    case 3:   // PWM Fade
      ledcAttachPin(LED1_PIN, 0);
      ledcAttachPin(LED2_PIN, 1);
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

    ledcWrite(0, pwmValue);
    ledcWrite(1, pwmValue);
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
