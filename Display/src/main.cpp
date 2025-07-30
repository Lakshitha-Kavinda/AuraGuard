#include <Arduino.h>
#include <Wire.h>
#include <adafruit_GFX.h>
#include <adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3c

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void displayText(float TextSize, int x, int y, String text);

void setup() {
  Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("SSD1306 allocation failed");
    for(;;);
  }
  //turn on OLED display
  display.display();
  delay(2000);

  //clear OLED display
  display.clearDisplay();

  //display the AuraGuard
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10,23);
  display.println(F("AuraGuard"));
  display.display();
  delay(2000);

  display.clearDisplay();

}

void loop() {
  // put your main code here, to run repeatedly:
  display.clearDisplay();
  delay(2000);
  displayText(1.5, 10, 23, "Connecting...");
  delay(2000);
  display.clearDisplay();
}

void displayText(float TextSize, int x, int y, String text) {

  display.setTextSize(TextSize);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(x,y);
  display.println(text);
  display.display();
}

