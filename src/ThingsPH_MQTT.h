#ifndef ThingsPH_MQTT_h
#define ThingsPH_MQTT_h
#include <PubSubClient.h>
#include <ArduinoJson.h>

class ThingsPH_MQTT
{
    private:
        PubSubClient mqttClient;

    public:
        inline ThingsPH_MQTT(Client &client) : mqttClient(client) { }

        typedef void (*ThingsPH_Callback)(char* topic, byte* payload, unsigned int length);

        void initialize(uint16_t size = 1024);
        void initialize(ThingsPH_Callback, uint16_t size = 1024);

        bool connect(const char*, const char*, const char*, const char*);
        void disconnect();

        bool subscribe(const char*);
        bool subscribe(const char*, uint8_t);
        bool unsubscribe(const char*);

        bool isconnected();
        void loop();
        bool publish(const JsonDocument&);
};
#endif