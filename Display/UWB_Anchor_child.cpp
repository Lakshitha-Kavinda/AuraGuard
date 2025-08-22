#include <HardwareSerial.h>

#define ANCHOR_RX 16   // ESP32 RX -> BU01 TX
#define ANCHOR_TX 17   // ESP32 TX -> BU01 RX

HardwareSerial AnchorUWB(2);

void setup() {
  Serial.begin(115200);
  AnchorUWB.begin(115200, SERIAL_8N1, ANCHOR_RX, ANCHOR_TX);
  delay(1000);

  Serial.println("ESP32 controlling BU01 Anchor starting...");

  // Set BU01 as Anchor, ID=0
  AnchorUWB.println("AT+anchor_tag=1,0"); 
  delay(200);

  // Optional: reset to factory settings
  // AnchorUWB.println("AT+FACTORY"); 
  // delay(200);
}

void loop() {
  // Print any messages from BU01 Anchor
  while (AnchorUWB.available()) {
    String line = AnchorUWB.readStringUntil('\n');
    line.trim();
    if (line.length() > 0) {
      Serial.println("[Anchor BU01] " + line);
    }
  }

  // Nothing else needed — Anchor passively responds to Tag
  delay(10);
}
