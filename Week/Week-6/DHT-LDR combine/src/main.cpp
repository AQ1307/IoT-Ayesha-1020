// Ayesha
// 23-NTU-CS-1020

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// --- Pin configuration ---
#define LDR_PIN 34        // LDR analog input pin
#define DHTPIN 14         // DHT22 data pin
#define DHTTYPE DHT22     // Change to DHT11 if needed
#define SDA_PIN 21        // OLED SDA
#define SCL_PIN 22        // OLED SCL

// --- OLED setup ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// --- DHT sensor setup ---
DHT dht(DHTPIN, DHTTYPE);

// --- Setup ---
void setup() {
  Serial.begin(115200);
  Serial.println("ESP32 Sensor Monitor");

  // Initialize I2C for OLED
  Wire.begin(SDA_PIN, SCL_PIN);
  delay(500);  // give time to OLED to power up

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed!");
    for (;;);
  }

  // Initialize DHT
  dht.begin();

  // Initial OLED message
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Initializing Sensors...");
  display.display();
  delay(1500);
}

// --- Main loop ---
void loop() {
  // Read LDR value
  int adcValue = analogRead(LDR_PIN);
  float voltage = (adcValue / 4095.0) * 3.3;

  // Read DHT22 values
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Check for DHT errors
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Error reading DHT22 sensor!");
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("Sensor Error!");
    display.display();
    delay(2000);
    return;
  }

  // Print values on Serial Monitor
  Serial.println("====================================");
  Serial.printf("LDR ADC: %d  |  Voltage: %.2f V\n", adcValue, voltage);
  Serial.printf("Temp: %.2f °C  |  Humidity: %.2f %%\n", temperature, humidity);

  // Display all readings on OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Hello IoT Monitor");

  display.setCursor(0, 14);
  display.print("Temp: ");
  display.print(temperature, 1);
  display.write(247); // ° symbol
  display.println("C");

  display.setCursor(0, 28);
  display.print("Humidity: ");
  display.print(humidity, 1);
  display.println("%");

  display.setCursor(0, 42);
  display.print("Light: ");
  display.print(voltage, 2);
  display.println(" V");

  display.display();

  delay(2000); // Update every 2 seconds
}
