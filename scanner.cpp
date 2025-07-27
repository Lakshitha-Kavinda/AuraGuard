#include <Arduino.h>
#include <BLEDevice.h>

// #define LED_PIN 5


//MAC address of the server
BLEAddress beaconAddress("3C:8A:1F:80:4E:DE");
BLEClient* pClient;

float calculateDistance(int rssi) {
  int measuredPower = -59; //Calibrated RSSI at 1 m.
  float n = 2.0; // Environment factor
  return pow(10.0, (measuredPower - rssi) /(10 * n));

}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // pinMode(LED_PIN, OUTPUT);
  // digitalWrite(LED_PIN, LOW);

  BLEDevice::init("");
  pClient = BLEDevice::createClient();
  Serial.println("BLE client created");
}

void loop() {
  //Establishing the connection to BLE Server and reconnecting
  if(!pClient->isConnected()){
    Serial.println("Connecting to BLE Server...");
    if(!pClient->connect(beaconAddress)){
      Serial.println("Failed to connect, Retrying...");
      delay(2000);
      return;
    }
    Serial.println("Connected to beacon!");
  }

  int rssi = pClient->getRssi();
  float distance = calculateDistance(rssi);

  Serial.print("RSSI: ");
  Serial.print(rssi);
  Serial.print(" Distance: ");
  Serial.print(distance);
  Serial.println("m");

  delay(1000);
}