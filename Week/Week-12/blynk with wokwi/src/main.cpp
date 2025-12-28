#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include "DHT.h"

// OLED settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pins from your diagram.json
#define DHTPIN 23         // DHT22 data pin connected to D23
#define BUTTON_PIN 5      // Pushbutton input on D5

// DHT22
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  dht.begin();
  
  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 init failed");
    while (1);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0, 0);
  display.print("System Ready...");
  display.display();
  delay(1000);
}

void loop() {

  // Read DHT22 sensor
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read DHT22");
    return;
  }

  // Read button
  int btnState = digitalRead(BUTTON_PIN);

  // Print on Serial Monitor
  Serial.print("Temp: ");
  Serial.print(t);
  Serial.print(" C  |  Hum: ");
  Serial.print(h);
  Serial.print(" %  | BTN: ");
  Serial.println(btnState == LOW ? "Pressed" : "Not Pressed");

  // Display on OLED
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);

  display.print("Temperature: ");
  display.print(t);
  display.println(" C");

  display.print("Humidity: ");
  display.print(h);
  display.println(" %");

  display.print("Button: ");
  display.println(btnState == LOW ? "Pressed" : "Released");

  display.display();

  delay(1000);   // Read every second
}
