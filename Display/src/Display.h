#ifndef DISPLAY_H
#define DISPLAY_H
#include <adafruit_SSD1306.h>

extern Adafruit_SSD1306 display;

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3c


void displayText(float TextSize, int x, int y, String text);

#endif


