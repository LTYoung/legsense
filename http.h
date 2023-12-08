#ifndef HTTP_H
#define HTTP_H
// HTTP Server
// include wifinina
#include <WiFiNINA.h>

#ifndef LEGSENSE_H
#include "legsense.h"
#endif // LEGSENSE_H





// creates a wifi access point
void setAP();

// handles HTTP requests
void handle_client(imu_data_t imu_data);



#endif // HTTP_H