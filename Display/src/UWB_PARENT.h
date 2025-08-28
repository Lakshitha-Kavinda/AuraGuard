#ifndef UWB_PARENT_H
#define UWB_PARENT_H

#define TAG_RX 16
#define TAG_TX 17

extern HardwareSerial TagUWB;
extern int anchorID;
extern int received_ID;
extern bool validID;
extern bool connected;

float getDistance();
int getID();
String readLine();
void initialize ();

#endif