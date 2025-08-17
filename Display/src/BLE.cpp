#include "BLE.h"
#include "main.h"
#include <Arduino.h>
#include "Display.h"
#include <BLEDevice.h>

// BLEAddress child_device("3C:8A:1F:80:4E:DE");
BLEAddress child_device("F4:65:0B:4A:7E:4A");
BLEClient* pClient;

bool is_Connected ;
float Measured_distance;

void connector () {
  Serial.begin(115200);

  BLEDevice::init("");
  pClient = BLEDevice::createClient();
  Serial.println("Created a BLE client");

  is_Connected = pClient->isConnected();

  while(!is_Connected) {
  displayText(2, 7, 23, "Connecting");
  delay(500);
  while (!is_Connected) {
    Serial.println("Conncting to child device");
    for (int i =0; i < 3; i++) {
      displayText(2,50+i*10,35,".");
      delay(100);
    }

    if (pClient->connect(child_device)) {
      is_Connected = 1;
      break;
    }

    display.fillRect(0, 40, SCREEN_WIDTH, 10, SSD1306_BLACK);
    display.display();

  }
}
  display.clearDisplay();
  displayText(2, 10, 23, "Connected");
  delay(2000);
}

//function to reconnect
void reconnector() {
  if (!pClient->isConnected()) {
    display.clearDisplay();
    digitalWrite(Vibration_motor,LOW);
    is_Connected = false;
    Serial.println("Reconnecting");
    displayText(2, 7, 23, "Connecting");
    delay(500);

    while(!is_Connected) {
      for (int i =0; i < 3; i++) {
        displayText(2,50+i*10,35,".");
        delay(100);
      }
      if(pClient->connect(child_device)) {
        is_Connected = true;
        display.clearDisplay();
        displayText(2, 10, 23, "Connected");
        delay(1000);
        display.clearDisplay();
        break;
      }
    }
  }

}
