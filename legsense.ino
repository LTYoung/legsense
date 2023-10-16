/**
 * File         : legsense.ino
 * Author       : Andrew Woska
 *                Young Ma
 * Project      : LegSense
 * Purpose      : Measures angle of leg lift using an IMU
 *
 * Board        : Arduino Nano RP2040 Connect
 * 
 * Modules      : Arduino_LSM6DSOX, MadgwickAHRS
 * 
 * Created on   : 10/11/2023
 * Updated on   : 10/16/2023
 * Changelist   :
 */

// Dependencies
#include <Arduino_LSM6DSOX.h>
#include <MadgwickAHRS.h>
#include "legsense.h"

// Global variables
imu_data_t imu_data;

Madgwick filter;

void setup()
{
    // Setup here
    Serial.begin(115200);
    if (!IMU.begin())
    {
        Serial.println("Failed to initialize IMU!");
        while (1)
            ;
    }
#ifdef DEBUG
    Serial.print("Accelerometer sample rate = ");
    Serial.print(IMU.accelerationSampleRate());
    Serial.println("Hz");
    Serial.println();

    Serial.print("Gyroscope sample rate = ");
    Serial.print(IMU.gyroscopeSampleRate());
    Serial.println("Hz");
    Serial.println();
#endif // DEBUG

    filter.begin(25);
}

void loop()
{
    // Loop here
    if (IMU.accelerationAvailable())
    {
        IMU.readAcceleration(imu_data.Ax, imu_data.Ax, imu_data.Ax);
#ifdef DEBUG
        Serial.println("Accelerometer data: ");
        Serial.print(imu_data.Ax);
        Serial.print('\t');
        Serial.print(imu_data.Ay);
        Serial.print('\t');
        Serial.println(imu_data.Az);
        Serial.println();
#endif // DEBUG
    }

    if (IMU.gyroscopeAvailable())
    {
        IMU.readGyroscope(imu_data.Gx, imu_data.Gy, imu_data.Gz);
#ifdef DEBUG
        Serial.println("Gyroscope data: ");
        Serial.print(imu_data.Gx);
        Serial.print('\t');
        Serial.print(imu_data.Gy);
        Serial.print('\t');
        Serial.println(imu_data.Gz);
        Serial.println();
#endif // DEBUG
    }

    // Filter
    filter.updateIMU(imu_data.Gx, imu_data.Gy, imu_data.Gz, imu_data.Ax, imu_data.Ay, imu_data.Az);

    imu_data.roll = filter.getRoll();
    imu_data.pitch = filter.getPitch();
    imu_data.yaw = filter.getYaw();
#ifdef DEBUG
    Serial.print("Filtered data: ");
    Serial.print(imu_data.roll);
    Serial.print('\t');
    Serial.print(imu_data.pitch);
    Serial.print('\t');
    Serial.print(imu_data.yaw);
    Serial.println();
#endif // DEBUG
    delay(500);
}
