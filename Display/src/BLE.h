#ifndef BLE_H
#define BLE_H
#define SCREEN_WIDTH 128
#include <BLEDevice.h>

extern bool is_Connected;
extern float Measured_distance;
extern BLEClient* pClient;


void connector ();

#endif