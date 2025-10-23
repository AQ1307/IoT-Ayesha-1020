#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <math.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  // Face outline
  display.drawCircle(64, 32, 20, SSD1306_WHITE);

  // Eyes
  display.fillCircle(56, 26, 3, SSD1306_WHITE); // Left eye
  display.fillCircle(72, 26, 3, SSD1306_WHITE); // Right eye

  // Smile (using points to form a curve)
  for (int i = -10; i <= 10; i++) {
    int x = 64 + i;
    int y = 42 + (int)(0.2 * i * i);  // Parabolic curve for smile
    display.drawPixel(x, y, SSD1306_WHITE);
  }

  display.display();
}
void loop() {
  // nothing here
}
