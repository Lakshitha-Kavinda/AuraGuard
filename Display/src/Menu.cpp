#include <Arduino.h>
#include "Menu.h"
#include "Display.h"

const int n_of_modes = 3;
String menu [n_of_modes] = {"Set distance", "Disable alerts", "Enable alerts"};
int distance_threshold = 1;
int current_mode;

void go_to_menu() {
  current_mode = 0;

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
      current_mode = (current_mode+1) % n_of_modes;
      displayText(2,0, 23, menu[current_mode]);

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
      if (current_mode == 0) {
        setDistance();
      }
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

void setDistance() {
    display.clearDisplay();
    int set_distance = distance_threshold;
    displayText(2, 50, 23, String(distance_threshold) +" m");
    delay(500);
    while (true) {

        int clicked_button = wait_for_button_press();

        if (clicked_button == Cancel_button) {
            display.clearDisplay();
            break;
        }

        else if (clicked_button == UP_button) {
        display.clearDisplay();
        set_distance++;
        if (set_distance > 10) {
            set_distance = 10;
        }
        displayText(2, 50, 23, String(set_distance) +" m");

        }
        else if (clicked_button == DOWN_button) {
            display.clearDisplay();
            set_distance--;
            if ( set_distance < 0) {
                set_distance = 0;
            }
            displayText(2, 50, 23, String(set_distance) +" m");
        }
        else if (clicked_button == OK_button) {
            distance_threshold = set_distance;
            break;
    }

    }
    display.clearDisplay();
    delay(500);
    displayText(2,0, 23, menu[current_mode]);
    Serial.println(distance_threshold);

}


