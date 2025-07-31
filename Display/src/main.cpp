#include <Arduino.h>
#include <Wire.h>
#include <adafruit_GFX.h>
#include <adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3c

//global variables
bool isConnected = false;
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
  displayText(2, 10,23, "AuraGuard");
  delay(2000);


  display.clearDisplay();

}

void loop() {
  // put your main code here, to run repeatedly:
  display.clearDisplay();
  delay(2000);
  displayText(2, 7, 23, "Connecting");
  delay(2000);
  while (!isConnected) {
    delay(1000);
    for (int i =0; i < 3; i++) {
      displayText(2,50+i*10,35,".");
      delay(500);
    }
    display.fillRect(0, 40, SCREEN_WIDTH, 10, SSD1306_BLACK);
    display.display();
    
  }
}

void displayText(float TextSize, int x, int y, String text) {

  display.setTextSize(TextSize);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(x,y);
  display.println(text);
  display.display();
}



