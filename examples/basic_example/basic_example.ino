#include <WiFi.h> // * If you use EP32.
//#include <ESP8266WiFi.h> // * If you use an ESP8266 Module.
#include <ThingsPH_MQTT.h>


WiFiClient espClient;
ThingsPH_MQTT thingsph(espClient);
StaticJsonDocument<256> jsondoc;
JsonObject telemetry;

const char* ssid = "...."; // <- Change to your WiFi Name.
const char* password =  "...."; // <- Change to your WiFi Password.
char* thingsUser = "";  // Get the username on things Docs/Guides under MQTT integration
char* thingsPassword = ""; // Get the password on things Docs/Guides under MQTT integration
char* thingsSerial = "test_device_01"; // Hardware Serial, Change this.

bool sensor1 = true;
float sensor2 = 1.0;
int sensor3 = 10;

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

  
  jsondoc["hardware_serial"] = thingsSerial;
  jsondoc["id"] = WiFi.macAddress();
  telemetry = jsondoc.createNestedObject("payload_fields");
}

void loop() {
  while (!thingsph.isconnected()) {
      // Attempt to connect to Things Platform:
      // params: clientName, username, password, serial
      thingsph.connect("espclient-test", thingsUser, thingsPassword, thingsSerial);
      delay(500);
  }

  // Add data:
  telemetry["sensor1"] = sensor1;
  telemetry["sensor2"] = sensor2;
  telemetry["sensor3"] = sensor3;
  
  // Update data:
  sensor1 = !sensor1;
  sensor2 = sensor2 + 0.2;
  sensor3 = sensor3 + 3;

  // Send Payload:
  if (thingsph.isconnected()) {
    if (thingsph.publish(jsondoc)) {
      Serial.println(F("Successfully sent!"));
    } else {
      Serial.println(F("Unable to send payload."));
    }
    espClient.flush(); // * Fix random disconnection after publishing
  }

  // Do not forget to call this function:
  thingsph.loop();
  delay(10000); // Wait for 10 seconds
}
