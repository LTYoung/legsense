#ifndef BLE_H
#define BLE_H

#include <ArduinoBLE.h>

#ifndef LEGSENSE_H
#include "legsense.h"
#endif // LEGSENSE_H

BLEService legSenseService("51cf29a9-692f-4dc9-9dba-5f08dc9a60c2");
BLEByteCharacteristic accelXChar("51cf29a9-692f-4dc9-9dba-5f08dc9a60b2", BLERead | BLENotify);
BLEByteCharacteristic accelYChar("51cf29a9-692f-4dc9-9dba-5f08dc9a60c1", BLERead | BLENotify);
BLEByteCharacteristic accelZChar("51cf29a9-692f-4dc9-9dba-5f08dc9a60e2", BLERead | BLENotify);
BLEByteCharacteristic gyroXChar("51cf29a9-692f-4dc9-9dba-5f08dc9a60c3", BLERead | BLENotify);
BLEByteCharacteristic gyroYChar("51cf29a9-692f-4dc9-9dba-5f08dc9a60c4", BLERead | BLENotify);
BLEByteCharacteristic gyroZChar("51cf29a9-692f-4dc9-9dba-5f08dc9a60c5", BLERead | BLENotify);
BLEByteCharacteristic rollChar("51cf29a9-692f-4dc9-9dba-5f08dc9a60c6", BLERead | BLENotify);
BLEByteCharacteristic pitchChar("51cf29a9-692f-4dc9-9dba-5f08dc9a60c7", BLERead | BLENotify);
BLEByteCharacteristic yawChar("51cf29a9-692f-4dc9-9dba-5f08dc9a60c8", BLERead | BLENotify);


void bleSetup();

void bleNotify(imu_data_t imu_data);
#endif // BLE_H