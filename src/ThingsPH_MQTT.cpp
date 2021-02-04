#include <Arduino.h>
#include <thingsph_mqtt.h>

String hardwareSerial;

void ThingsPH_MQTT::initialize(uint16_t size) {

    const char* mqttServer = "mqtt.things.ph";
    const int mqttPort = 1883;

    this->mqttClient.setBufferSize(size);
    this->mqttClient.setServer(mqttServer, mqttPort);
}

void ThingsPH_MQTT::initialize(ThingsPH_Callback callBack, uint16_t size) {

    const char* mqttServer = "mqtt.things.ph";
    const int mqttPort = 1883;

    this->mqttClient.setBufferSize(size);
    this->mqttClient.setServer(mqttServer, mqttPort);
    this->mqttClient.setCallback(callBack);
}

bool ThingsPH_MQTT::connect(const char* clientname, const char* user, const char* password, const char* serial) {
    
    Serial.println("Attempting MQTT connection...");

    // Attempt to connect
    if (this->mqttClient.connect(clientname, user, password)) {
        Serial.println(F("Connected to Things PH MQTT!"));

        char _hSerial[50];
        strcpy(_hSerial, serial);
        hardwareSerial = "/ingest/" + String(_hSerial);

        return true;
    }

    Serial.print(F(" Failed, rc="));
    Serial.print(this->mqttClient.state());
    Serial.println(F(""));

    return false;
}

bool ThingsPH_MQTT::isconnected() {
    return this->mqttClient.connected();
}

void ThingsPH_MQTT::disconnect() {
    this->mqttClient.disconnect();
    Serial.print("Disconnected to Things PH!");
}

bool ThingsPH_MQTT::subscribe(const char* topic) {
    return this->mqttClient.subscribe(topic);
}

bool ThingsPH_MQTT::subscribe(const char* topic, uint8_t qos) {
    return this->mqttClient.subscribe(topic, qos);
}

bool ThingsPH_MQTT::unsubscribe(const char* topic) {
    return this->mqttClient.unsubscribe(topic);
}

void ThingsPH_MQTT::loop() {
    this->mqttClient.loop();
}

bool ThingsPH_MQTT::publish(const JsonDocument& doc) {
    std::string output;
    serializeJson(doc, output);

    char payload_chararray[output.size() + 1];
    memcpy(payload_chararray, output.data(), output.size() + 1); 

    char serial_chararray[50];
    hardwareSerial.toCharArray(serial_chararray, 50);

    Serial.println(payload_chararray);

    return this->mqttClient.publish(serial_chararray, payload_chararray);
}