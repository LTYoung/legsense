// Contains the WiFi AP setup, and HTTP server setup.
#include "http.h"

const char *ssid = "LegSense";
const char *pass = "rp2040Nano";

WiFiServer server(80);

int status = WL_IDLE_STATUS;

// Starts the WiFi AP for a client to connect to
// and starts the HTTP server once AP is up
void setAP()
{
    Serial.println("\n[*] Creating AP");
    pinMode(LEDR, OUTPUT);
    pinMode(LEDG, OUTPUT);
    pinMode(LEDB, OUTPUT);
    digitalWrite(LEDG, LOW);  // turn off gree LED
    digitalWrite(LEDB, HIGH); // blue means setup mode
    status = WiFi.beginAP(ssid, pass);
    if (status != WL_AP_LISTENING)
    {
        Serial.println("Creating access point failed");
        // don't continue, blue light will go off, red means something went wrong
        digitalWrite(LEDB, LOW);
        digitalWrite(LEDR, HIGH);
        while (true)
            ;
    }
    Serial.print("[+] AP Created with IP Gateway ");
    Serial.println(WiFi.gatewayIP());
    delay(10000); // 10 second delay
    server.begin();
}



// handle_client()
// handles client requests
// and prints the IMU data to the client
// on every get request

void handle_client(imu_data_t imu_data){
    WiFiClient client = server.available();
    // if there is a client connected
    if (client){
        Serial.println("[*] Client connected");
        // wait for the client to send data
        while (client.connected()){
            // if there is data available
            if (client.available()){
                // read the data
                String req = client.readStringUntil('\r');
                Serial.println(req);
                client.flush();
                // if the request is a GET request
                if (req.indexOf("GET") != -1){
                    // send the IMU data
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-Type: text/html");
                    client.println("Connection: close");
                    client.println();
                    client.println("<!DOCTYPE HTML>");
                    client.println("<html>");
                    client.println("<head>");
                    client.println("<title>LegSense</title>");
                    client.println("</head>");
                    client.println("<body>");
                    client.println("<h1>LegSense</h1>");
                    client.println("<p>Accelerometer Data</p>");
                    client.println("<p>Roll: " + String(imu_data.roll) + "</p>");
                    client.println("<p>Pitch: " + String(imu_data.pitch) + "</p>");
                    client.println("<p>Yaw: " + String(imu_data.yaw) + "</p>");
                    client.println("<p> Gyroscope Data </p>");
                    client.println("<p>Gx: " + String(imu_data.Gx) + "</p>");
                    client.println("<p>Gy: " + String(imu_data.Gy) + "</p>");
                    client.println("<p>Gz: " + String(imu_data.Gz) + "</p>");
                    client.println("<p> Raw Accelerometer Data </p>");
                    client.println("<p>Ax: " + String(imu_data.Ax) + "</p>");
                    client.println("<p>Ay: " + String(imu_data.Ay) + "</p>");
                    client.println("<p>Az: " + String(imu_data.Az) + "</p>");
                    //client.println("Updated on " + String(day()) + "/" + String(month()) + "/" + String(year()) + " at " + String(hour()) + ":" + String(minute()) + ":" + String(second()));
                    client.println("</body>");
                    client.println("</html>");
                    break;
                }
            }
        }
        // close the connection
        client.stop();
        Serial.println("[*] Client disconnected");
    }
    else {
        Serial.println("[*] No client connected");
    }
}