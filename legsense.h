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

#define DEFAULT_BOUND_LOW   20.0    // 20 degrees
#define DEFAULT_BOUND_HIGH  40.0    // 40 degrees
#define DEFAULT_HOLD_TIME   5000    // 5s

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

/**
 * type to represent leg lift ratings
 */
typedef enum {
    RATING_NONE             = 0x00,

    // angle ratings
    RATING_BAD_ANGLE_LOW    = 0x11,
    RATING_BAD_ANGLE_HIGH   = 0x12,
    RATING_CLOSE_ANGLE      = 0x13,

    // timing ratings
    RATING_TOO_SHORT        = 0x21,
    RATING_TOO_LONG         = 0x22,

    // good ratings
    RATING_GOOD_GENERIC     = 0x80,
} rating_t;

/* functions */

/**
 * updates all values in imu_data
 */
void read_sensors();

/**
 * get the rating of the current leg lift
 */
rating_t get_rating();

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
 * set LED based on orientation using rating
 */
void set_led();

#endif // LEGSENSE_H
