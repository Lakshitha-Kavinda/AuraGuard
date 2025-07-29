#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>

// WiFi credentials of parent device
const char* ssid = "Parent";
const char* password = "1234";

WiFiUDP udp;
const int localPort = 4210;

void setup() {
    Serial.begin(115200);

    //Create an WiFi access point
    WiFi.softAP(ssid, password);
    IPAddress IP = WiFi.softAPIP();
    Serial.print("IP address: ");
    Serial.println(IP);

    //UDP server
    udp.begin(localPort);
    Serial.printf("UDP Server listening on port %d\n", localPort);
}

void loop() {
    int packetSize = udp.parsePacket();
    if (packetSize) {
        char incoming[255];
        int len = udp.read(incoming,255);
        if (len > 0) {
            incoming[len] = '\0';
        }

        //Echo the message back
        udp.beginPacket(udp.remoteIP(), udp.remotePort());
        udp.write((const uint8_t*)incoming, strlen(incoming));
        udp.endPacket();
    }

}