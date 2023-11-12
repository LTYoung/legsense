/**
 * File         : legsense.h
 * Author       : Andrew Woska
 *                Young Ma
 * Project      : LegSense
 * Purpose      : Measures angle of leg lift using an IMU
 * 
 * Created on   : 10/16/2023
 * Updated on   : 11/12/2023
 * Changelist   :
 */

#pragma once

#ifndef LEGSENSE_H
#define LEGSENSE_H

/* constants */
#define DEBUG
#define FILTER_ONLY

/* macros */

// print safe
#ifdef DEBUG
#define printlns(s) ( Serial.println(s) )
#define prints(s)   ( Serial.print(s) )
#define prinths(s)  ( Serial.print(s, HEX) )
#else
#define printlns(s) (0)
#define prints(s)   (0)
#define prinths(s)  (0)
#endif //DEBUG

/* types */

/**
 * type for holding relevant IMU data
 */
typedef struct {
    float
        // accelerometer values
        Ax,
        Ay,
        Az,
        // gyroscope values
        Gx,
        Gy,
        Gz,
        // orientation values
        roll,
        pitch,
        yaw;
} imu_data_t;

/* functions */

/**
 * updates all values in imu_data
 */
void read_sensors();

/**
 * prints out accelerometer data if DEBUG is defined
 */
void print_accel_data();

/**
 * prints out gyroscope data if DEBUG is defined
 */
void print_gyro_data();

/**
 * prints out orientation data
 */
void print_orientation_data();

/**
 * set LED based on orientation
 */
void set_led();

#endif // LEGSENSE_H
