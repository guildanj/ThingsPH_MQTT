#include <Arduino.h>
#include <thingsph_mqtt.h>


String hardwareSerial;
String payload;
int _payloadCount;


void ThingsPH_MQTT::initialize() {

    const char* mqttServer = "mqtt.things.ph";
    const int mqttPort = 1883;

    this->mqttClient.setServer(mqttServer, mqttPort);

    _payloadCount = 0;
}

void ThingsPH_MQTT::initialize(ThingsPH_Callback callBack) {

    const char* mqttServer = "mqtt.things.ph";
    const int mqttPort = 1883;

    this->mqttClient.setServer(mqttServer, mqttPort);
    this->mqttClient.setCallback(callBack);

    _payloadCount = 0;
}

bool ThingsPH_MQTT::connect(char* user, char* password, char* serial) {
    
    Serial.println("Attempting MQTT connection...");

    char* _clName;
    if (CLIENT_NAME == 1) {
        _clName = "ESP32Client";
    } else {
        _clName = "ESP8266Client";
    }
    // Attempt to connect
    if (this->mqttClient.connect(_clName, user, password)) {
        Serial.println("Connected to Things PH - " + String(_clName));
        Serial.println(F(""));

        char _hSerial[50];
        strcpy(_hSerial, serial);
        hardwareSerial = "/ingest/v2/" + String(_hSerial);

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

bool ThingsPH_MQTT::subscribe(char* topic) {
    return this->mqttClient.subscribe(topic);
}

bool ThingsPH_MQTT::subscribe(char* topic, uint8_t qos) {
    return this->mqttClient.subscribe(topic, qos);
}

bool ThingsPH_MQTT::unsubscribe(char* topic) {
    return this->mqttClient.unsubscribe(topic);
}

int ThingsPH_MQTT::payloadcount() {
    return _payloadCount;
}

void ThingsPH_MQTT::loop() {
    this->mqttClient.loop();
}

bool ThingsPH_MQTT::addpayload(String dataname, String data, bool isString = true) {
    if (_payloadCount == 0) {
        payload = "{\"payload_fields\": {";
    } else {
        payload = payload + ", ";
    }

    payload = payload + "\"" + dataname + "\":";
    
    if (isString) {
        payload = payload + "\"" + String(data) + "\"";
    } else {
        payload = payload + String(data);
    }
    
    _payloadCount++;
}

bool ThingsPH_MQTT::addpayload(String dataname, int8_t data) {
    return addpayload(dataname, String(data), false);
}

bool ThingsPH_MQTT::addpayload(String dataname, int16_t data) {
    return addpayload(dataname, String(data), false);
}

bool ThingsPH_MQTT::addpayload(String dataname, int32_t data) {
    return addpayload(dataname, String(data), false);
}

bool ThingsPH_MQTT::addpayload(String dataname, uint8_t data) {
    return addpayload(dataname, String(data), false);
}

bool ThingsPH_MQTT::addpayload(String dataname, uint16_t data) {
    return addpayload(dataname, String(data), false);
}

bool ThingsPH_MQTT::addpayload(String dataname, uint32_t data) {
    return addpayload(dataname, String(data), false);
}

bool ThingsPH_MQTT::addpayload(String dataname, float data) {
    return addpayload(dataname, String(data), false);
}

bool ThingsPH_MQTT::addpayload(String dataname, double data) {
    return addpayload(dataname, String(data), false);
}

void ThingsPH_MQTT::clearpayloads() {
    _payloadCount = 0; 
    payload = "";
}

bool ThingsPH_MQTT::publish() {
    payload = payload + "}}";
    
    Serial.print(F("Sending: "));
    Serial.println(payload);

    char serial_chararray[50];
    char payload_chararray[1000];
    hardwareSerial.toCharArray(serial_chararray, 50);
    payload.toCharArray(payload_chararray, 1000);

    // Reset
    payload = "";
    _payloadCount = 0;

    return this->mqttClient.publish(serial_chararray, payload_chararray);
}
