#include "ble.h"

void bleSetup(){
    BLE.setLocalName("LegSense");
    BLE.setAdvertisedService(legSenseService);
    legSenseService.addCharacteristic(accelXChar);
    legSenseService.addCharacteristic(accelYChar);
    legSenseService.addCharacteristic(accelZChar);
    legSenseService.addCharacteristic(gyroXChar);
    legSenseService.addCharacteristic(gyroYChar);
    legSenseService.addCharacteristic(gyroZChar);
    legSenseService.addCharacteristic(rollChar);
    legSenseService.addCharacteristic(pitchChar);
    legSenseService.addCharacteristic(yawChar);
    BLE.addService(legSenseService);
    BLE.advertise();
}


void bleNotify(imu_data_t imu_data){
    accelXChar.writeValue(imu_data.Ax);
    accelYChar.writeValue(imu_data.Ay);
    accelZChar.writeValue(imu_data.Az);
    gyroXChar.writeValue(imu_data.Gx);
    gyroYChar.writeValue(imu_data.Gy);
    gyroZChar.writeValue(imu_data.Gz);
    rollChar.writeValue(imu_data.roll);
    pitchChar.writeValue(imu_data.pitch);
    yawChar.writeValue(imu_data.yaw);
}