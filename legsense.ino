// Dependencies
#include <Arduino_LSM6DSOX.h>

// Global variables
float Ax, Ay, Az; // accelerometer values
float Gx, Gy, Gz; // gyroscope values

void setup()
{
    // Setup here
    Serial.begin(9600);
    if (!IMU.begin())
    {
        Serial.println("Failed to initialize IMU!");
        while (1)
            ;
    }
    Serial.print("Accelerometer sample rate = ");
    Serial.print(IMU.accelerationSampleRate());
    Serial.println("Hz");
    Serial.println();

    Serial.print("Gyroscope sample rate = ");
    Serial.print(IMU.gyroscopeSampleRate());
    Serial.println("Hz");
    Serial.println();
}

void loop()
{
    // Loop here
    if (IMU.accelerationAvailable())
    {
        IMU.readAcceleration(Ax, Ay, Az);

        Serial.println("Accelerometer data: ");
        Serial.print(Ax);
        Serial.print('\t');
        Serial.print(Ay);
        Serial.print('\t');
        Serial.println(Az);
        Serial.println();
    }

    if (IMU.gyroscopeAvailable())
    {
        IMU.readGyroscope(Gx, Gy, Gz);

        Serial.println("Gyroscope data: ");
        Serial.print(Gx);
        Serial.print('\t');
        Serial.print(Gy);
        Serial.print('\t');
        Serial.println(Gz);
        Serial.println();
    }

    delay(500);
}
