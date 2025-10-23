#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET   -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  int cx = SCREEN_WIDTH / 2;   // center X
  int cy = SCREEN_HEIGHT / 2;  // center Y

  // Head (small circle)
  int headRadius = 10;
  display.drawCircle(cx, cy - 12, headRadius, SSD1306_WHITE);

  // Body/shoulders (rounded base)
  int bodyWidth = 40;
  int bodyHeight = 20;
  int bodyTop = cy + 2;

  // Draw shoulder arc
  display.drawRoundRect(cx - bodyWidth / 2, bodyTop, bodyWidth, bodyHeight, 10, SSD1306_WHITE);

  display.display();
}
void loop() {}
