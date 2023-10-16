/**
 * File         : legsense.h
 * Author       : Andrew Woska
 *                Young Ma
 * Project      : LegSense
 * Purpose      : Measures angle of leg lift using an IMU
 * 
 * Created on   : 10/16/2023
 * Updated on   : 10/16/2023
 * Changelist   :
 */

#ifndef LEGSENSE_H
#define LEGSENSE_H

/* constants */
#define DEBUG

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


#endif // LEGSENSE_H