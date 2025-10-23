#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // I2C address for OLED
  display.clearDisplay();

  // Draw outer rounded rectangle (YouTube style)
  display.fillRoundRect(24, 16, 80, 40, 8, SSD1306_WHITE);

  // Draw inner triangle (Play icon)
  display.fillTriangle(
    50, 24,   // top point
    50, 48,   // bottom point
    80, 36,   // right point
    SSD1306_BLACK   // color: black (so it appears as cutout)
  );

  // Optional text
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(40, 4);
  display.print("YouTube");

  display.display();
}

void loop() {
  // nothing here
}
