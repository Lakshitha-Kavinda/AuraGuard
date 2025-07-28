#include <Arduino.h>
#include <WiFi.h>
 #include <WiFiUdp.h>

 const char* ssid = "Parent";
 const char* password = "1234";

 WiFiUDP udp;
 const int udpPort = 4210;
 IPAddress receiverIP(192, 168, 4, 1); //Default IP address of the child device

 void setup() {

    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    Serial.println("Connecting to Child devce...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");

    }

    Serial.println("\nConnected to child device!");
    Serial.print("Local IP: ");
    Serial.println(WiFi.localIP());

    udp.begin(udpPort); //Starting UDP port


 }

 void loop() {
    //Send UDP packet and measure RSSI
    String msg = "Hello";

    udp.beginPacket(receiverIP, udpPort);
    udp.write((const uint8_t*)msg.c_str(), msg.length());
    udp.endPacket();

    unsigned long timeout = millis() + 500; //define a timeout for receiving the response
    while(!udp.parsePacket()) {
        if (millis() > timeout) {
            Serial.println("Reply timeout");
            return;
        }
    }

    int rssi = WiFi.RSSI();
    Serial.printf("Received RSSI: %d dBm\n",rssi);

    float Measured_Power = -40; // Measured RSSI at 1 m
    float n = -2.0;//Environment factor
    float distance = pow(10, ((Measured_Power - rssi)/(10 * n)));
    Serial.printf("Estimated distance: %.2f \n",distance);

    delay(2000);
 }