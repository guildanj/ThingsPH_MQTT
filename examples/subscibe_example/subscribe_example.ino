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

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("]: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

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
  thingsph.initialize(callback);
}

void loop() {
    while (!thingsph.isconnected()) {
      // Attempt to connect to Things Platform:
      thingsph.connect(thingsUser, thingsPassword, thingsSerial);
      delay(500);

      // Subscribe if connected:
      if (thingsph.isconnected()) {
        thingsph.subscribe(thingsSerial);
      }
    }
    
    // Do not forget to call this function:
    thingsph.loop();
}