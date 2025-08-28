#include <HardwareSerial.h> 
#include <UWB_PARENT.h>
#include "Display.h"
#include "BLE.h"
#include "Menu.h"


HardwareSerial TagUWB(2);

int anchorID = 0;
int received_ID = -1;
bool validID = false;
bool ranging = false;
bool tagConnected = false;
// String tagResponse;
// String rangingResponse;
bool connected = false;


void initialize () {
  TagUWB.begin(115200, SERIAL_8N1, TAG_RX, TAG_TX);
  if((!tagConnected && !ranging) || !connected) {
  displayText(2, 7, 23, "Connecting");
  delay(200);
  while (max_attempts > 0) {
    Serial.println("Conncting to child device");
    for (int i =0; i < 3; i++) {
      displayText(2,50+i*10,35,".");
      delay(200);
    }

    if(!tagConnected && !ranging) {
        delay(200);
        TagUWB.println("AT+anchor_tag=0,1"); //tag mode
        delay(500);
        // // tagResponse = readLine();
        // Serial.println(tagResponse + "Hello");

        // if (tagResponse == "OK" ) {
        //   Serial.println("Tag connected");
        tagConnected = true;
        // }

        
        TagUWB.println("AT+switchdis=1"); // enable ranging
        delay(500);
        // rangingResponse = readLine();
        // Serial.println(rangingResponse);

        // if (rangingResponse == "OK" ) {
        //   Serial.println("Ranging enabled");
            ranging = true;
        // }

        delay(1000);
    }

    received_ID = getID();
    Serial.println(received_ID);
    delay(200);
    Serial.println(anchorID);

    Serial.println("receivedID:" + String(received_ID) +" anchorID:" + String(anchorID));


    if (received_ID == anchorID) {
        Serial.println("Valid ID");
        validID = true;
        delay(200);
    }

    Serial.println("is Valid:"+ String(validID) + " ranging:" + String(ranging) + " tagConnected:" + String(tagConnected));

    if (validID && ranging && tagConnected) {
      connected = true;
      break;
    }

    Serial.println(connected);

    display.fillRect(0, 40, SCREEN_WIDTH, 10, SSD1306_BLACK);
    display.display();
    delay(3000);
    max_attempts--;

   }
}
  display.clearDisplay();

  if (connected) {
    displayText(2, 10, 23, "Connected");
    delay(2000);

  }else {
    Serial.println("Failed to connect. Going to deep sleep...");
    displayText(2, 35, 23, "Failed");
    displayText(1, 32, 45, "Sleep mode On");

    delay(2000);
    display.clearDisplay();

    delay(6000);
    
    sleepDisplay(&display);

    // EXT0 wake-up on OK button, wake on LOW
    esp_sleep_enable_ext0_wakeup((gpio_num_t)OK_button, 0);
    esp_deep_sleep_start(); // Enter deep sleep
  }
}


String readLine() {
    String line = "";
    if (TagUWB.available()) {
        line = TagUWB.readStringUntil('\n');
        line.trim();

    //     if (line.length() > 0) {
    //         // Serial.println(line);
        
    }
    return line;
}

int getID() {
    String line = readLine();
    int received_anchorID = -1;
    if (line.length() > 0) {
      // Serial.println(line);
      int colon = line.indexOf(':');
      if (colon > 0) {
        received_anchorID = line.substring(0, colon).toInt();
        // Serial.printf("Anchor %d \n", received_anchorID);
      }
    }
    return received_anchorID;
}


// float getDistance() {
//     float distance;
//     String line = readLine();
//     if (line.length() > 0) {
//       // Serial.println("[Distance] " + line);  // Example: 0:2.45
//       int colon = line.indexOf(':');
//       if (colon > 0) {
//         distance = line.substring(colon + 1).toFloat();
//         // Serial.printf("%.2f m\n", distance);
//       }
//     }
//     return distance;

// }

