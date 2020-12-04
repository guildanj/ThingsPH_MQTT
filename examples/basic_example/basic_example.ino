#include <WiFi.h> // * If you use EP32.
//#include <ESP8266WiFi.h> // * If you use an ESP8266 Module.
#include <ThingsPH_MQTT.h>


WiFiClient espClient;
ThingsPH_MQTT thingsph(espClient);

const char* ssid = "...."; // <- Change to your WiFi Name.
const char* password =  "...."; // <- Change to your WiFi Password.
char* thingsUser = "";  // Get the username on things Docs/Guides under MQTT integration
char* thingsPassword = ""; // Get the password on things Docs/Guides under MQTT integration
char* thingsSerial = "test_device_01"; // Hardware Serial, Change this.

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  Serial.println("Connecting to WiFi..");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println("Connected to the WiFi network");
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());

    // Don't forget to initialize ThingsPH_MQTT
  thingsph.initialize();
}

void loop() {
    while (!thingsph.isconnected()) {
        // Attempt to connect to Things Platform:
        thingsph.connect(thingsUser, thingsPassword, thingsSerial);
        delay(500);
    }

    // Add fields:
    thingsph.addpayload("Temperature", 88);
    thingsph.addpayload("Battery", 99);
  
    // Send Payload:
    if (thingsph.publish()) Serial.println("SENT!");

    // Do not forget to call this function:
    thingsph.loop();
}