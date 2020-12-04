#ifndef ThingsPH_MQTT_h
#define ThingsPH_MQTT_h
#include <PubSubClient.h>


#if defined(ESP8266)
#define CLIENT_NAME 0
#else
#define CLIENT_NAME 1
#endif

class ThingsPH_MQTT
{
    private:
        PubSubClient mqttClient;

    public:
        inline ThingsPH_MQTT(Client &client) : mqttClient(client) { }

        typedef void (*ThingsPH_Callback)(char* topic, byte* payload, unsigned int length);

        void initialize();
        void initialize(ThingsPH_Callback);

        bool connect(char*, char*, char*);
        void disconnect();

        bool subscribe(char*);
        bool subscribe(char*, uint8_t);
        bool unsubscribe(char*);

        bool addpayload(String, String, bool);
        bool addpayload(String, int8_t);
        bool addpayload(String, int16_t);
        bool addpayload(String, int32_t);
        bool addpayload(String, uint8_t);
        bool addpayload(String, uint16_t);
        bool addpayload(String, uint32_t);
        bool addpayload(String, float);
        bool addpayload(String, double);

        bool isconnected();
        void loop();
        bool publish();
};
#endif