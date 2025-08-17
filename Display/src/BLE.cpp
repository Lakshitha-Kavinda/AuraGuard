#include "BLE.h"
#include "main.h"
#include "menu.h"
#include <Arduino.h>
#include "Display.h"
#include <BLEDevice.h>

BLEAddress child_device("3C:8A:1F:80:4E:DE");
// BLEAddress child_device("F4:65:0B:4A:7E:4A");
BLEClient* pClient;

bool is_Connected = false ;
float Measured_distance;
int max_attempts;

void connector () {

  if(!is_Connected) {
  displayText(2, 7, 23, "Connecting");
  delay(200);
  while (!is_Connected && max_attempts > 0) {
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
    max_attempts--;

   }
}
  display.clearDisplay();

  if (is_Connected) {
    displayText(2, 10, 23, "Connected");
    delay(2000);

  }else {
    Serial.println("Failed to connect. Going to deep sleep...");
    displayText(2, 35, 23, "Failed");
    displayText(1, 32, 45, "Sleep mode On");

    delay(2000);
    display.clearDisplay();

    // EXT0 wake-up on OK button, wake on LOW
    esp_sleep_enable_ext0_wakeup((gpio_num_t)OK_button, 0);
    esp_deep_sleep_start(); // Enter deep sleep
  }

  
  
}

