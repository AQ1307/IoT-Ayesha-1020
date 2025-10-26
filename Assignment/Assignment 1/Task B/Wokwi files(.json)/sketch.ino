// Title: Button-Controlled LED and Buzzer Interaction
// Ayesha 
// 23-NTU-CS-1020

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define BUTTON 4
#define LED 2
#define BUZZER 5

Adafruit_SSD1306 display(128, 64, &Wire, -1);

unsigned long pressTime = 0;
bool buttonState = false;
bool lastButtonState = false;
bool ledState = false;

void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Ready...");
  display.display();
}

void loop() {
  buttonState = digitalRead(BUTTON) == LOW;
  if (buttonState && !lastButtonState) {
    pressTime = millis(); // button just pressed
  }
  // when button released
  if (!buttonState && lastButtonState) {
    unsigned long pressDuration = millis() - pressTime;

    display.clearDisplay();
    display.setCursor(0, 0);

    if (pressDuration < 1500) {
      // short press → toggle LED
      ledState = !ledState;
      digitalWrite(LED, ledState);
      display.println("Short Press");
      display.println("LED Toggled");
    } 
    else {
      // long press → buzzer tone
      display.println("Long Press");
      display.println("Buzzer ON");
      tone(BUZZER, 1000, 500); // 1kHz tone for 0.5s
    }

    display.display();
  }

  lastButtonState = buttonState;
}
