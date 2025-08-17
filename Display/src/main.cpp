#include <Arduino.h>
#include <string>
#include "BLE.h"
#include "Display.h"
#include <adafruit_SSD1306.h>
#include "Menu.h"
#include "main.h"
// #include "kalman filter.h"
// #include <SimpleKalmanFilter.h>
// #include <freeRTOS.h>



//global variables
// SimpleKalmanFilter kalman(0.0, 2.0, 4.0);

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

  
  BLEDevice::init("");
  pClient = BLEDevice::createClient();
  Serial.println("Created a BLE client");

  //connect to BLE device

    // Check wake-up reason
  esp_sleep_wakeup_cause_t reason = esp_sleep_get_wakeup_cause();
  if (reason == ESP_SLEEP_WAKEUP_EXT0) {
    Serial.println("Woke up from OK button press, retrying BLE connection...");
  }

  max_attempts = 2;
  connector();


  display.clearDisplay();
  delay(1000);


}

void loop() {

  if (!pClient->isConnected()) {
    display.clearDisplay();
    digitalWrite(Vibration_motor,LOW);
    is_Connected = false;
    connector();
  }

    // if (!pClient->isConnected()) {
    //   Serial.println("Lost connection, restarting tasks...");
    //   is_Connected = false;
    //   startConnectionTasks();  // restart connection phase
    // }



   //function for distance update
   int rssi = pClient->getRssi();
   Measured_distance = calculateDistance(rssi);
   update_Distance(Measured_distance);
   
   if( Measured_distance > distance_threshold && alerts_enabled) {
    digitalWrite(Vibration_motor,HIGH);

   }
   else if (Measured_distance < distance_threshold) {
    digitalWrite(Vibration_motor,LOW);
   }
   
delay(2000);

  if (digitalRead(OK_button) == LOW) {
    delay(200);
    digitalWrite(Vibration_motor,LOW);
    go_to_menu();
    
  }

}


void update_Distance (float Measured_distance) {
  display.clearDisplay();
  // float filteredDistance = kalman.update(Measured_distance);
  displayText(2, 50, 23, String(Measured_distance,1) +" m");
  // displayText(2, 50, 23, String(filteredDistance,1) +" m");


}

float calculateDistance(int rssi) {
  int measuredPower = -59; //Calibrated RSSI at 1 m.
  float n = 2.0; // Environment factor
  return pow(10.0, (measuredPower - rssi) /(10 * n));

}
