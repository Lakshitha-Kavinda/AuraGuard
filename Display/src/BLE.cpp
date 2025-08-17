#include "BLE.h"
#include "main.h"
#include <Arduino.h>
#include "Display.h"
#include <BLEDevice.h>

BLEAddress child_device("3C:8A:1F:80:4E:DE");
// BLEAddress child_device("F4:65:0B:4A:7E:4A");
BLEClient* pClient;

bool is_Connected = false ;
float Measured_distance;
unsigned long lastUpdate = 0;
int dotCount = 0;

void connector () {

  if(!is_Connected) {
  displayText(2, 7, 23, "Connecting");
  delay(200);
  while (!is_Connected) {
    Serial.println("Conncting to child device");
    for (int i =0; i < 3; i++) {
      displayText(2,50+i*10,35,".");
      delay(200);
    }


    if (pClient->connect(child_device)) {
      is_Connected = true;
      break;
    }

    display.fillRect(0, 40, SCREEN_WIDTH, 10, SSD1306_BLACK);
    display.display();
    // delay(100);

   }
}
  display.clearDisplay();
  displayText(2, 10, 23, "Connected");
  delay(2000);
}

