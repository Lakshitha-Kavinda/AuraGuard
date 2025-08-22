#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLEAdvertising.h>

BLEServer *pServer;
BLEService *pService;
BLECharacteristic *pCharacteristic;

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    Serial.println("Parent connected");
  }

  void onDisconnect(BLEServer* pServer) {
    Serial.println("Parent disconnected, restarting advertising...");
    BLEDevice::startAdvertising();  // crucial to allow reconnection
  }
};

void setup() {
    Serial.begin(115200);

    BLEDevice::init("ChildBeacon");
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());

    // Create a service
    pService = pServer->createService(SERVICE_UUID);

    // Create a characteristic
    pCharacteristic = pService->createCharacteristic(
                        CHARACTERISTIC_UUID,
                        BLECharacteristic::PROPERTY_READ |
                        BLECharacteristic::PROPERTY_WRITE
                      );

    pCharacteristic->setValue("Hello Parent!");

    // Start the service
    pService->start();

    // Start advertising
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06);
    pAdvertising->setMinPreferred(0x12);
    BLEDevice::startAdvertising();

    Serial.println("Child device ready, waiting for parent to connect...");
}

void loop() {
    // you can update characteristic value here
}
