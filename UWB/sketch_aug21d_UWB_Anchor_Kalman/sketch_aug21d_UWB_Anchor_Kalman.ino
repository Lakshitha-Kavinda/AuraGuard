#include <HardwareSerial.h>

#define TAG_RX 16   // ESP32 RX → BU01 TX
#define TAG_TX 17   // ESP32 TX → BU01 RX
HardwareSerial UWB(2);

// Kalman filter variables
float distance = 0;       // raw distance
float filteredDist = 0;   // Kalman filtered distance
float P = 1, Q = 0.01, R = 0.1, K;

void setup() {
  Serial.begin(115200);
  UWB.begin(115200, SERIAL_8N1, TAG_RX, TAG_TX);
  delay(1000);

  Serial.println("Initializing BU01 Tag...");

  // 1️⃣ Set device as Tag with ID=1
  UWB.println("AT+anchor_tag=0,1");  
  delay(200);

  // 2️⃣ Enable ranging
  UWB.println("AT+switchdis=1");     
  delay(200);

  // 3️⃣ Set ranging interval (example: 20 meters averaging)
  UWB.println("AT+interval=20");     
  delay(200);

  // Optional: query firmware version
  UWB.println("AT+version?");
  delay(200);
}

void loop() {
  // Read distance data from BU01
  while (UWB.available()) {
    String line = UWB.readStringUntil('\n');
    line.trim();
    if (line.length() == 0) continue;

    int colon = line.indexOf(':');
    if (colon > 0) {
      distance = line.substring(colon + 1).toFloat();

      // Kalman filter
      P = P + Q;
      K = P / (P + R);
      filteredDist = filteredDist + K * (distance - filteredDist);
      P = (1 - K) * P;

      // Print raw and filtered distance
      Serial.printf("Anchor %s → Raw: %.2f m, Filtered: %.2f m\n",
                    line.substring(0, colon).c_str(), distance, filteredDist);
    } else {
      // Print other responses from BU01
      Serial.println("[UWB] " + line);
    }
  }
}
