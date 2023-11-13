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
 * Updated on   : 11/12/2023
 * Changelist   :
 */

// Dependencies
#include <Arduino_LSM6DSOX.h>
#include <MadgwickAHRS.h>
#include "legsense.h"
#include "http.h"
#include "ble.h"

/* global variables */
imu_data_t imu_data;

Madgwick filter;

int rate;   // sample rate in Hz
unsigned long microsPerReading, microsPrevious;

/* implementation */

void setup()
{
    Serial.begin(115200);

    // Set up LEDs
    pinMode(LEDR, OUTPUT);
    pinMode(LEDG, OUTPUT);
    pinMode(LEDB, OUTPUT);
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDG, HIGH);
    digitalWrite(LEDB, HIGH);

    // Set up IMU
    delay(10);
    printlns("LegSense v0.1");
    if (!IMU.begin())
    {
        printlns("Failed to initialize IMU!");
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

    rate = min(IMU.gyroscopeSampleRate(), IMU.accelerationSampleRate());

    // Connectivity
    // Wi-Fi AP and HTTP server
    setAP();
    // BLE
    bleSetup();


    filter.begin(rate);

    microsPerReading = 1000000 / rate;
    microsPrevious = micros();
}

void loop()
{
    unsigned long microsNow;

    microsNow = micros();
    if (microsNow - microsPrevious >= microsPerReading) {
        read_sensors();
        microsPrevious = microsNow + microsPerReading;
        print_orientation_data();
        set_led();
        handle_client(imu_data);
        bleNotify(imu_data);
    }
    delay(1);
}


void read_sensors()
{
    if (IMU.accelerationAvailable())
    {
        IMU.readAcceleration(imu_data.Ax, imu_data.Ay, imu_data.Az);
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
#ifndef FILTER_ONLY
    printlns("Orientation data: ");
#endif // FILTER_ONLY
    prints(imu_data.roll);
    prints('\t');
    prints(imu_data.pitch);
    prints('\t');
    prints(imu_data.yaw);
    printlns();
}

void set_led()
{
    if (abs(imu_data.pitch) < 20) {
        digitalWrite(LEDR, HIGH);
        digitalWrite(LEDG, LOW);
        digitalWrite(LEDB, LOW);
    } else if (abs(imu_data.pitch) < 40) {
        digitalWrite(LEDR, LOW);
        digitalWrite(LEDG, HIGH);
        digitalWrite(LEDB, LOW);
    } else {
        digitalWrite(LEDR, LOW);
        digitalWrite(LEDG, LOW);
        digitalWrite(LEDB, HIGH);
    }
}
