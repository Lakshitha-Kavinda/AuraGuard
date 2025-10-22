#include <Arduino.h>
#include "Menu.h"
#include "Display.h"

bool alerts_enabled = true;
bool timeout_on = true;
int screen_timeout = 15000;
const int n_of_modes = 6;
String menu [n_of_modes] = {"Set distance", "Disable alerts", "Enable alerts","Screen timeout", "Disable_timeout","Enable_timeout"};
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
    delay(500);
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
      else if (current_mode == 1) {
        display.clearDisplay();
        alerts_enabled = false;
        displayText(2, 27, 23, "Disabled");
        delay(1000);
        display.clearDisplay();
        displayText(2,0, 23, menu[current_mode]);
      }
      else if (current_mode == 2) {
        display.clearDisplay();
        alerts_enabled = true;
        displayText(2, 27, 23, "Enabled");
        delay(1000);
        display.clearDisplay();
        displayText(2,0, 23, menu[current_mode]);

      }
      else if (current_mode == 3) {
        setScreen_timeout();
      }
      else if(current_mode == 4) {
        display.clearDisplay();
        timeout_on = false;
        displayText(2, 27, 23, "Disabled");
        delay(1000);
        display.clearDisplay();
        displayText(2,0, 23, menu[current_mode]);

      }
      else if(current_mode == 5) {
        display.clearDisplay();
        timeout_on = true;
        displayText(2, 27, 23, "Enabled");
        delay(1000);
        display.clearDisplay();
        displayText(2,0, 23, menu[current_mode]);       
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

void setScreen_timeout() {
  display.clearDisplay();
  int set_timeout = screen_timeout;
    displayText(2, 50, 23, String(screen_timeout/1000) +" s");
    delay(500);
    while (true) {

        int clicked_button = wait_for_button_press();

        if (clicked_button == Cancel_button) {
            display.clearDisplay();
            break;
        }

        else if (clicked_button == UP_button) {
        display.clearDisplay();
        set_timeout += 1000;
        if (set_timeout > 60000) {
            set_timeout = 60000;
        }
        displayText(2, 50, 23, String(set_timeout/1000) +" s");

        }
        else if (clicked_button == DOWN_button) {
            display.clearDisplay();
            set_timeout -= 1000;
            if ( set_timeout < 0) {
                set_timeout = 0;
            }
            displayText(2, 50, 23, String(set_timeout/1000) +" s");
        }
        else if (clicked_button == OK_button) {
            screen_timeout = set_timeout;
            break;
    }

    }
    display.clearDisplay();
    delay(500);
    displayText(2,0, 23, menu[current_mode]);
    Serial.println(distance_threshold);
}


