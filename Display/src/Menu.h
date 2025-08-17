#ifndef MENU_H
#define MENU_H

#define OK_button 4
#define Cancel_button 5
#define UP_button 13
#define DOWN_button 14

extern int distance_threshold;
extern bool alerts_enabled;

void go_to_menu();
int wait_for_button_press();
void setDistance();

#endif