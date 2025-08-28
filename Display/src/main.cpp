#include <Arduino.h>
#include <string>
#include "BLE.h"
#include "Display.h"
#include <adafruit_SSD1306.h>
#include "Menu.h"
#include "main.h"
#include <UWB_PARENT.h>
#include <HardwareSerial.h>

// #define TAG_RX 16
// #define TAG_TX 17 
// HardwareSerial TagUWB(2);



//global variables
int screen_timeout = 15000;
int last_update = 0;
unsigned long current_millis = 0;
bool screen_on = true;

void update_Distance(float Measured_distance);
void displayText(float TextSize, int x, int y, String text);
float calculateDistance(int rssi);


//  KalmanFilter kalman(0.0, 2.0, 4.0); 

void setup() {
  Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("SSD1306 allocation failed");
    for(;;);
  }

  //For UWB initilizing
  // TagUWB.begin(115200, SERIAL_8N1, TAG_RX, TAG_TX);
  // delay(1000);
  // TagUWB.println("AT+anchor_tag=0,1");  // Tag mode
  // delay(200);
  // TagUWB.println("AT+switchdis=1");     // Enable ranging
  // delay(200);

  // TagUWB.println("AT+interval=10");     

  pinMode(OK_button, INPUT_PULLUP);
  pinMode(Cancel_button,INPUT_PULLUP);
  pinMode(UP_button,INPUT_PULLUP);
  pinMode(DOWN_button,INPUT_PULLUP);
  pinMode(Vibration_motor,OUTPUT);
  digitalWrite(Vibration_motor,LOW);

  //turn on OLED display
  display.display();
  delay(2000);

  //clear OLED display
  display.clearDisplay();

  //display the AuraGuard
  displayText(2, 10,23, "AuraGuard");
  delay(2000);

  display.clearDisplay();

  
  // BLEDevice::init("");
  // pClient = BLEDevice::createClient();
  // Serial.println("Created a BLE client");

  //connect to BLE device

    // Check wake-up reason
  esp_sleep_wakeup_cause_t reason = esp_sleep_get_wakeup_cause();
  if (reason == ESP_SLEEP_WAKEUP_EXT0) {
    Serial.println("Woke up from OK button press, retrying BLE connection...");
  }

  max_attempts = 2;
  // connector();
  initialize();


  display.clearDisplay();
  delay(1000);
  last_update = millis();


}

void loop() {

  // if (!pClient->isConnected()) {

  //   digitalWrite(Vibration_motor,LOW);
  //   if (!screen_on) {
  //     wakeDisplay(&display);
  //     display.clearDisplay();
  //     display.display();
  //     last_update = millis();
  //     screen_on = true;
  //   }
  //   display.clearDisplay();

  //   is_Connected = false;
  //   connector();
  //   last_update = millis();
  // }

  current_millis = millis();

  //checking for screen timeout condition
  if ((current_millis-last_update) > screen_timeout && screen_on) {
    display.clearDisplay();
    screen_on = false;
    sleepDisplay(&display);
  }

   //function for distance update
  //  int rssi = pClient->getRssi();
  // Measured_distance = calculateDistance(rssi);
  //  update_Distance(Measured_distance);
if (TagUWB.available()) {
  String line = TagUWB.readStringUntil('\n');
    line.trim();
    if (line.length() > 0) {
      // Serial.println("[Distance] " + line);  // Example: 0:2.45
      int colon = line.indexOf(':');
      if (colon > 0) {
        int anchorID = line.substring(0, colon).toInt();
        Measured_distance = line.substring(colon + 1).toFloat();
        // Serial.printf("Anchor %d → %.2f m\n", anchorID, Measured_distance);
        update_Distance(Measured_distance);
      }
    }
  } 

// Measured_distance = getDistance();
// update_Distance(Measured_distance);
// Serial.printf("Measured Distance: %.2f m\n", Measured_distance);

   if( Measured_distance > distance_threshold && alerts_enabled) {
    digitalWrite(Vibration_motor,HIGH);

   }
   else if (Measured_distance < distance_threshold) {
    digitalWrite(Vibration_motor,LOW);
   }
   
// delay(1500);

  if (digitalRead(OK_button) == LOW) {
    delay(200);
    digitalWrite(Vibration_motor,LOW);
    go_to_menu();
    last_update = millis();
    delay(200);
  }
  else if (digitalRead(Cancel_button) == LOW) {
    delay(200);
    wakeDisplay(&display);
    screen_on = true;
    display.clearDisplay();
    display.display();
    last_update = millis();
  }

}


void update_Distance (float Measured_distance) {
  display.clearDisplay();
  // float filteredDistance = kalman.update(Measured_distance);
  displayText(2, 50, 23, String(Measured_distance,2) +" m");
  // displayText(2, 50, 23, String(filteredDistance,1) +" m");


}

float calculateDistance(int rssi) {
  int measuredPower = -59; //Calibrated RSSI at 1 m.
  float n = 2.0; // Environment factor
  return pow(10.0, (measuredPower - rssi) /(10 * n));

}
