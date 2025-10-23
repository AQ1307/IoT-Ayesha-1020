// OLED example: Adafruit SSD1306 + Adafruit_GFX
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char* name = "Ayesha";
const char* id   = "23-NTU-CS-1020";

void setup() {
  Serial.begin(115200);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 init failed");
    while (1);
  }
  display.clearDisplay();

  // Choose text properties
  display.setTextSize(2);            // scale (1..)
  display.setTextColor(SSD1306_WHITE);

  // Measure name text
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(name, 0, 0, &x1, &y1, &w, &h);

  // We'll place name at (x,y) centered horizontally
  int16_t xName = (SCREEN_WIDTH - w) / 2;
  int16_t yName = 8;

  // Draw name
  display.setCursor(xName, yName);
  display.print(name);

  // Measure ID text (smaller)
  display.setTextSize(1);
  display.getTextBounds(id, 0, 0, &x1, &y1, &w, &h);
  int16_t xId = (SCREEN_WIDTH - w) / 2;
  int16_t yId = yName + 22; // gap under name

  display.setCursor(xId, yId);
  display.print(id);

  // Compute bounding rectangle that covers both texts
  // Recompute bounds for name and id with their actual sizes & positions
  display.setTextSize(2);
  display.getTextBounds(name, xName, yName, &x1, &y1, &w, &h);
  int16_t left = x1;
  int16_t top  = y1;
  int16_t right = x1 + w;
  int16_t bottom = y1 + h;

  display.setTextSize(1);
  display.getTextBounds(id, xId, yId, &x1, &y1, &w, &h);

// Cast to int for consistent type comparison
  left   = min((int)left,   (int)x1);
  top    = min((int)top,    (int)y1);
  right  = max((int)right,  (int)(x1 + w));
  bottom = max((int)bottom, (int)(y1 + h));


  // add small padding
  int pad = 4;
  left = max(0, left - pad);
  top  = max(0, top - pad);
  right = min(SCREEN_WIDTH - 1, right + pad);
  bottom = min(SCREEN_HEIGHT - 1, bottom + pad);

  // Draw rectangle
  display.drawRect(left, top, right - left + 1, bottom - top + 1, SSD1306_WHITE);

  display.display();
}

void loop() {
  // nothing to do
}
