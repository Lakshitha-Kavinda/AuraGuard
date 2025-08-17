#include "Display.h"
#include <Wire.h>
#include <adafruit_GFX.h>


// #define SCREEN_WIDTH 128



Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void displayText(float TextSize, int x, int y, String text) {

  display.setTextSize(TextSize);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(x,y);
  display.println(text);
  display.display();
}