// PWM – LED Brightness Fade
/*
#include <Arduino.h>
#define LED_PIN 18
#define PWM_CH 0
#define FREQ 5000
#define RES 8
void setup() {
  ledcSetup(PWM_CH, FREQ, RES);
  ledcAttachPin(LED_PIN, PWM_CH);
}
void loop() {
  for (int d=0; d<=255; d++) { 
ledcWrite(PWM_CH, d); delay(10); }
  for (int d=255; d>=0; d--) { 
ledcWrite(PWM_CH, d); delay(10); }
}
*/

//.....................................................

// Buzzer_Pin
/*
#include <Arduino.h>

#define BUZZER_PIN  27     // GPIO connected to buzzer
#define PWM_CH      0      // PWM channel (0–15)
#define FREQ        2000   // Default frequency (Hz)
#define RESOLUTION  10     // 10-bit resolution (0–1023)

void setup() {
  // Setup PWM channel
  ledcSetup(PWM_CH, FREQ, RESOLUTION);
  ledcAttachPin(BUZZER_PIN, PWM_CH);

  // --- 1. Simple beep pattern ---
  for (int i = 0; i < 3; i++) {
    ledcWriteTone(PWM_CH, 2000 + i * 400); // change tone
    delay(150);
    ledcWrite(PWM_CH, 0);                  // stop tone
    delay(150);
  }

  // --- 2. Frequency sweep (400Hz → 3kHz) ---
  for (int f = 400; f <= 3000; f += 100) {
    ledcWriteTone(PWM_CH, f);
    delay(20);
  }
  ledcWrite(PWM_CH, 0);
  delay(500);

  // --- 3. Short melody ---
  int melody[] = {262, 294, 330, 349, 392, 440, 494, 523};
  for (int i = 0; i < 8; i++) {
    ledcWriteTone(PWM_CH, melody[i]);
    delay(250);
  }
  ledcWrite(PWM_CH, 0); // stop buzzer
}

void loop() {
  // Nothing here
}
*/




//...................................................

//Both_Led_and_Buzzer:
/*
#include <Arduino.h>

// --- Buzzer setup ---
#define BUZZER_PIN 27
#define BUZZER_CH  0
#define BUZZER_FREQ 2000
#define BUZZER_RES 10

// --- LED setup ---
#define LED_PIN 18
#define LED_CH  1
#define LED_FREQ 5000
#define LED_RES 8

void setup() {
  // --- Setup for buzzer ---
  ledcSetup(BUZZER_CH, BUZZER_FREQ, BUZZER_RES);
  ledcAttachPin(BUZZER_PIN, BUZZER_CH);

  // --- Setup for LED ---
  ledcSetup(LED_CH, LED_FREQ, LED_RES);
  ledcAttachPin(LED_PIN, LED_CH);

  // --- 1. Simple beep pattern with LED fade ---
  for (int i = 0; i < 3; i++) {
    ledcWriteTone(BUZZER_CH, 2000 + i * 400);
    for (int d = 0; d <= 255; d++) {
      ledcWrite(LED_CH, d);
      delay(3);
    }
    ledcWrite(BUZZER_CH, 0);
    for (int d = 255; d >= 0; d--) {
      ledcWrite(LED_CH, d);
      delay(3);
    }
  }

  delay(300);

  // --- 2. Frequency sweep (400Hz → 3kHz) with LED breathing ---
  for (int f = 400; f <= 3000; f += 100) {
    ledcWriteTone(BUZZER_CH, f);
    ledcWrite(LED_CH, (f / 12) % 256); // vary LED brightness with frequency
    delay(20);
  }
  ledcWrite(BUZZER_CH, 0);
  delay(500);

  // --- 3. Short melody with LED blinking ---
  int melody[] = {262, 294, 330, 349, 392, 440, 494, 523};
  for (int i = 0; i < 8; i++) {
    ledcWriteTone(BUZZER_CH, melody[i]);
    ledcWrite(LED_CH, 255);
    delay(250);
    ledcWrite(LED_CH, 0);
    delay(100);
  }

  ledcWrite(BUZZER_CH, 0); // stop buzzer
  ledcWrite(LED_CH, 0);    // turn off LED
}

void loop() {
  // Optional continuous LED fade effect after buzzer finishes
  for (int d = 0; d <= 255; d++) {
    ledcWrite(LED_CH, d);
    delay(5);
  }  
  for (int d = 255; d >= 0; d--) {
    ledcWrite(LED_CH, d);
    delay(5);
  }
}
*/