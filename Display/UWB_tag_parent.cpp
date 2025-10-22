// #include <HardwareSerial.h> //allows you to create serial communication objects for the ESP32’s UART ports
// #define TAG_RX 16
// #define TAG_TX 17
// HardwareSerial TagUWB(2);

// void setup() {
//   Serial.begin(115200);
//   TagUWB.begin(115200, SERIAL_8N1, TAG_RX, TAG_TX);
//   delay(1000);

//   // Configure BU01 Tag
//   TagUWB.println("AT+anchor_tag=0,1");  // Tag mode
//   delay(200);
//   TagUWB.println("AT+switchdis=1");     // Enable ranging
//   delay(200);
//   TagUWB.println("AT+interval=10");     // Optional
// }

// void loop() {
//   while (TagUWB.available()) {
//     String line = TagUWB.readStringUntil('\n');
//     line.trim();
//     if (line.length() > 0) {
//       Serial.println("[Distance] " + line);  // Example: 0:2.45
//       int colon = line.indexOf(':');
//       if (colon > 0) {
//         int anchorID = line.substring(0, colon).toInt();
//         float distance = line.substring(colon + 1).toFloat();
//         Serial.printf("Anchor %d → %.2f m\n", anchorID, distance);
//       }
//     }
//   }
// }
