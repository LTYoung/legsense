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
 * Updated on   : 10/24/2023
 * Changelist   :
 */

// Dependencies
#include <Arduino_LSM6DSOX.h>
#include <MadgwickAHRS.h>
#include "legsense.h"
#include "http.h"

/* global variables */
imu_data_t imu_data;

Madgwick filter;

int rate;   // sample rate in Hz
unsigned long microsPerReading, microsPrevious;

/* implementation */

void setup()
{
    Serial.begin(115200);
    if (!IMU.begin())
    {
        Serial.println("Failed to initialize IMU!");
        while (1)
            ;
    }

    prints("Accelerometer sample rate = ");
    prints(IMU.accelerationSampleRate());
    printlns("Hz");
    printlns();

    prints("Gyroscope sample rate = ");
    prints(IMU.gyroscopeSampleRate());
    printlns("Hz");
    printlns();

    rate = max(IMU.gyroscopeSampleRate(), IMU.accelerationSampleRate());

    filter.begin(rate);

    microsPerReading = 1000000 / rate;
    microsPrevious = micros();

    // Start AP
    setAP();
}

void loop()
{
    unsigned long microsNow;

    microsNow = micros();
    if (microsNow - microsPrevious >= microsPerReading)
    {
        read_sensors();
        microsPrevious = microsNow + microsPerReading;
    }
    handle_client(imu_data);
}


void read_sensors()
{
    if (IMU.accelerationAvailable())
    {
        IMU.readAcceleration(imu_data.Ax, imu_data.Ax, imu_data.Ax);
        print_accel_data();
    }

    if (IMU.gyroscopeAvailable())
    {
        IMU.readGyroscope(imu_data.Gx, imu_data.Gy, imu_data.Gz);
        print_gyro_data();
    }
    filter.updateIMU(imu_data.Gx, imu_data.Gy, imu_data.Gz, imu_data.Ax, imu_data.Ay, imu_data.Az);
    imu_data.roll = filter.getRoll();
    imu_data.pitch = filter.getPitch();
    imu_data.yaw = filter.getYaw();
    print_orientation_data();
}

void print_accel_data() 
{
#ifndef FILTER_ONLY
    printlns("Accelerometer data: ");
    prints(imu_data.Ax);
    prints('\t');
    prints(imu_data.Ay);
    prints('\t');
    prints(imu_data.Az);
    printlns();
#endif // FILTER_ONLY
}

void print_gyro_data()
{
#ifndef FILTER_ONLY
    printlns("Gyroscope data: ");
    prints(imu_data.Gx);
    prints('\t');
    prints(imu_data.Gy);
    prints('\t');
    prints(imu_data.Gz);
    printlns();
#endif // FILTER_ONLY
}

void print_orientation_data()
{
    printlns("Orientation data: ");
    prints(imu_data.roll);
    prints('\t');
    prints(imu_data.pitch);
    prints('\t');
    prints(imu_data.yaw);
    printlns();
}