// Contains the WiFi AP setup, and HTTP server setup.
#include "http.h"

const char *ssid = "LegSense";
const char *pass = "rp2040Nano";

WiFiServer server(80);

int status = WL_IDLE_STATUS;


const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>IMU Data</title>
  <script>
    function fetchData() {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
                var data = JSON.parse(this.responseText);
                document.getElementById("accelX").innerText = data.accelX;
                document.getElementById("accelY").innerText = data.accelY;
                document.getElementById("accelZ").innerText = data.accelZ;
                document.getElementById("gyroX").innerText = data.gyroX;
                document.getElementById("gyroY").innerText = data.gyroY;
                document.getElementById("gyroZ").innerText = data.gyroZ;
                document.getElementById("roll").innerText = data.roll;
                document.getElementById("pitch").innerText = data.pitch;
                document.getElementById("yaw").innerText = data.yaw;
            }
        };
        xhttp.open("GET", "/data", true);
        xhttp.send();
    }
    setInterval(fetchData, 1000);
  </script>
</head>
<body>
  <h1>IMU Data</h1>
  <p>Accelerometer X: <span id="accelX"></span></p>
  <p>Accelerometer Y: <span id="accelY"></span></p>
  <p>Accelerometer Z: <span id="accelZ"></span></p>
    <p>Gyroscope X: <span id="gyroX"></span></p>
    <p>Gyroscope Y: <span id="gyroY"></span></p>
    <p>Gyroscope Z: <span id="gyroZ"></span></p>
    <p>Roll: <span id="roll"></span></p>
    <p>Pitch: <span id="pitch"></span></p>
    <p>Yaw: <span id="yaw"></span></p>
</body>
</html>
)rawliteral";


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

void handle_client(imu_data_t imu_data)
{
    WiFiClient client = server.available();
    // if there is a client connected
    if (client)
    {
        Serial.println("[*] Client connected");
        // wait for the client to send data
        while (client.connected())
        {
            // if there is data available
            if (client.available())
            {
                // read the data
                String req = client.readStringUntil('\r');
                Serial.println(req);
                client.flush();

                if (req.indexOf("GET / ") != -1)
                {
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-Type: text/html");
                    client.println("Connection: close");
                    client.println();
                    client.println(index_html); // Send the HTML content
                }

                // if the request is a GET request for the /data endpoint
                if (req.indexOf("GET /data") != -1)
                {
                    // send the IMU data
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-Type: application/json");
                    client.println("Connection: close");
                    client.println();

                    // Send the IMU data in JSON format
                    client.print("{\"accelX\":");
                    client.print(imu_data.Ax);
                    client.print(",\"accelY\":");
                    client.print(imu_data.Ay);
                    client.print(",\"accelZ\":");
                    client.print(imu_data.Az);
                    client.print(",\"gyroX\":");
                    client.print(imu_data.Gx);
                    client.print(",\"gyroY\":");
                    client.print(imu_data.Gy);
                    client.print(",\"gyroZ\":");
                    client.print(imu_data.Gz);
                    client.print(",\"roll\":");
                    client.print(imu_data.roll);
                    client.print(",\"pitch\":");
                    client.print(imu_data.pitch);
                    client.print(",\"yaw\":");
                    client.print(imu_data.yaw);
                    client.println("}");
                }
            }
        }
    }
}