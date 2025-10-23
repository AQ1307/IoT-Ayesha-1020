#include <Arduino.h>

// --- Buzzer configuration ---
#define BUZZER_PIN 27
#define BUZZER_CH  0
#define BUZZER_FREQ 2000
#define BUZZER_RES 10

// --- LED configuration ---
#define LED1_PIN 18
#define LED1_CH  1
#define LED1_FREQ 3000   // LED1 = 5 kHz
#define LED1_RES 8

#define LED2_PIN 19
#define LED2_CH  2
#define LED2_FREQ 3000   // LED2 = 2 kHz
#define LED2_RES 8

void setup() {
  // --- Buzzer setup ---
  ledcSetup(BUZZER_CH, BUZZER_FREQ, BUZZER_RES);
  ledcAttachPin(BUZZER_PIN, BUZZER_CH);

  // --- LED setups with different frequencies ---
  ledcSetup(LED1_CH, LED1_FREQ, LED1_RES);
  ledcAttachPin(LED1_PIN, LED1_CH);

  ledcSetup(LED2_CH, LED2_FREQ, LED2_RES);
  ledcAttachPin(LED2_PIN, LED2_CH);

  // --- Buzzer patterns ---
  for (int i = 0; i < 3; i++) {
    ledcWriteTone(BUZZER_CH, 2000 + i * 400);
    delay(150);
    ledcWrite(BUZZER_CH, 0);
    delay(150);
  }

  for (int f = 400; f <= 3000; f += 100) {
    ledcWriteTone(BUZZER_CH, f);
    delay(20);
  }
  ledcWrite(BUZZER_CH, 0);
  delay(500);

  int melody[] = {262, 294, 330, 349, 392, 440, 494, 523};
  for (int i = 0; i < 8; i++) {
    ledcWriteTone(BUZZER_CH, melody[i]);
    delay(250);
  }
  ledcWrite(BUZZER_CH, 0);
}

void loop() {
  // Both LEDs brighten together (same duty cycle)
  for (int d = 0; d <= 255; d++) {
    ledcWrite(LED1_CH, d);  // Same duty cycle
    ledcWrite(LED2_CH, d);
    delay(10);
  }

  // Both LEDs dim together
  for (int d = 255; d >= 0; d--) {
    ledcWrite(LED1_CH, d);
    ledcWrite(LED2_CH, d);
    delay(10);
  }
}
