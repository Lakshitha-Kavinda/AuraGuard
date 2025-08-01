#include <Arduino.h>
#include <Wire.h>
#include <adafruit_GFX.h>
#include <adafruit_SSD1306.h>
#include <string>


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3c

#define OK_button 4
#define Cancel_button 5
#define UP_button 13
#define DOWN_button 14

const int n_of_modes = 3;
String menu [n_of_modes] = {"Set distance", "Disable alerts", "Enable alerts"};

//global variables
bool isConnected = 1;
int distance_threshold = 1;
float Measured_distance = 0.0;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void go_to_menu();
int wait_for_button_press();
void update_Distance(float Measured_distance);
void displayText(float TextSize, int x, int y, String text);
void connector();

void setup() {
  Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("SSD1306 allocation failed");
    for(;;);
  }

  pinMode(OK_button, INPUT);
  pinMode(Cancel_button,INPUT);
  pinMode(UP_button,INPUT);
  pinMode(DOWN_button,INPUT);
  //turn on OLED display
  display.display();
  delay(2000);

  //clear OLED display
  display.clearDisplay();

  //display the AuraGuard
  displayText(2, 10,23, "AuraGuard");
  delay(2000);

  //connect to BLE device
  connector();

  display.clearDisplay();
  delay(1000);


}

void loop() {

  // put your main code here, to run repeatedly:
   //function for distance update
   update_Distance(Measured_distance);

  if (digitalRead(OK_button) == LOW) {
    delay(200);
    go_to_menu();
    
  }
}

void displayText(float TextSize, int x, int y, String text) {

  display.setTextSize(TextSize);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(x,y);
  display.println(text);
  display.display();
}


void go_to_menu() {
  int current_mode = 0;

  display.clearDisplay();
  displayText(2,46, 23, "MENU");
  delay(2000);
  display.clearDisplay();

  displayText(2,0, 23, menu[current_mode]);

  while (true) {

    int clicked_button = wait_for_button_press();

    if (clicked_button == Cancel_button) {
      display.clearDisplay();
      // update_Distance(Measured_distance);
      break;
    }
    else if (clicked_button == UP_button) {
      display.clearDisplay();
      displayText(2,0, 23, menu[(current_mode++) % n_of_modes]);

    }
    else if (clicked_button == DOWN_button) {
      current_mode--;
      if ( current_mode < 0) {
        current_mode = 2;
      }
      display.clearDisplay();
      displayText(2, 0, 23, menu[current_mode]);
    }
    else if (clicked_button == OK_button) {
      continue;
    }

}

}

int wait_for_button_press() {
  while (true){
    if (digitalRead(Cancel_button) == LOW) {
      delay(200);
      return Cancel_button;
    }
    else if (digitalRead(UP_button) == LOW) {
      delay(200);
      return UP_button;
    }
    else if (digitalRead(DOWN_button) == LOW) {
      delay(200);
      return DOWN_button;
    }
    else if (digitalRead(OK_button) == LOW) {
      delay(200);
      return OK_button;
    }
  }

}

void update_Distance (float Measured_distance) {
  display.clearDisplay();
  displayText(2, 50, 23, String(Measured_distance,1) +" m");

}

void connector () {

  while(!isConnected) {
  displayText(2, 7, 23, "Connecting");
  delay(2000);
  while (!isConnected) {
    delay(1000);
    for (int i =0; i < 3; i++) {
      displayText(2,50+i*10,35,".");
      delay(500);
    }
    display.fillRect(0, 40, SCREEN_WIDTH, 10, SSD1306_BLACK);
    display.display();

  }
}
  display.clearDisplay();
  displayText(2, 10, 23, "Connected");
  delay(2000);
}
