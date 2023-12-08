# LegSense


Lower extremity rehabilitation is essential for recovering patients who have leg or knee injuries. Physical Therapy contributes to strengthening leg muscles, especially with leg lift exercises.

The LegSense project focuses on the development of an affordable and integrated device designed to facilitate and improve the effectiveness of lower extremity rehabilitation. This project primarily targets the enhancement of therapy through straight leg lift exercises.

LegSense prototype was developed at Boston University in 2023.

## Table of Contents

1. [Prototype](#prototype)
2. [Getting Started Using Prototype](#getting-started-using-prototype)
3. [Dependencies](#dependencies)
4. [Licenses and Contributions](#licenses-and-contributions)
5. [PCB](#pcb)
6. [Known Issues](#known-issues)

## Prototype

This device has been prototyped on the [Arudino Nano RP2040 Connect](https://docs.arduino.cc/hardware/nano-rp2040-connect).
This is due to the onboard IMU and wireless capabilities of the device.

A 1602 I2C LCD with LED has also been connected to extend functionality.

## Getting Started Using Prototype

- Attach RP2040 to power and LCD
- Turn on the power to the system
- Flash program to RP2040
- Ensure LCD starts loading data after the initialization period (5 seconds max)
  - In the event it does not load, reload the program
- You can connect to the device wirelessly through WiFi
  - SSID: LegSense
  - passphrase: rp2040Nano
  - This can be updated in [http.cpp](./http.cpp)


## Dependencies

All libraries are available on the Arduino Library Manager and may need to be downloaded.

- Arduino_LSM6DS0X
- MadgwickAHRS
- WiFiNINA
- ArduinoBLE

### Madgwick Filter

Papers, documentation, code, and simulations for the Madgwick Filter are available [here](https://x-io.co.uk/open-source-imu-and-ahrs-algorithms/)

## Licenses and Contributions

Licenses used include: GNU Lesser GPL by Arduino

This project is licensed under [BSD 3-Clause License](./LICENSE)

## PCB

The LegSense PCB was created with Altium CircuitMaker, and the current model is available [here](https://365.altium.com/files/01BA11E5-04AE-48AB-B72D-11DF33FCA85D).

The board is still being developed, but the general design is represented in the 3D model.

![PCB 3D Model](https://woska.net/img/legsense_v0.3_pcb.png)

The full product is modeled below:
modelv0
![LegSense Model](https://woska.net/img/legsense_v0.3_model.png)

## Known Issues

TBD
