# ThingsPH_MQTT
An arduino client library to easily integrate your IoT hardware to ThingsPH Platform. This library uses [PubSubClient](https://github.com/knolleary/pubsubclient "PubSubClient") by knolleary and [ArduinoJson](https://arduinojson.org/ "ArduinoJson").

## Functions
| Function/Method | Type | Parameters | Description |
| :------------: | :------------: | :------------: | :------------: |
| **initialize** | void | optional: `ThingsPH_Callback` , `uint16_t size size = 2048` | Setup the mqtt client. Optionally, you can set the maximum packet size and the ThingsPH_Callback that will be used when you subscribe to a topic. |
| **setClient** | void | `Client& client` | Set the connection client that will be used. (e.g. WifiClient or TinyGsmClient) |
| **connect** | bool | `const char* clientname` , `const char* user` , `const char* password` , `const char* serial` | Connect to ThingsPH MQTT broker by specifying your credentials. |
| **disconnect** | void |  | Disconnect to ThingsPH_MQTT broker. |
| **subscribe** | bool | `const char* topic`, optional: `uint8_t qos` | Subscribe to a topic and if specified, use the callback method that you set during initialization to receive the downlink payloads. |
| **unsubscribe** | bool | `const char* topic` | Unsubscribe to the topic. |
| **isconnected** | bool |  | Check if the client is currently connected to the broker. |
| **loop** | void |  | This method is **REQUIRED** to be called inside the sketch's loop. |
| **publish** | bool | `const JsonDocument&` | Publish the json document to the ThingsPH platform. |

***NOTE***:  Please make sure to call the loop() method inside your main loop.

## How to get you ThingsPH Credentials?
Your ThingsPH MQTT credentials can be found at the [docs section](https://console.things.ph/user-settings/documentation "docs section") of things ph console. Navigate to "**MQTT Integration**" tab and you will see the username and password.

## Quickstart
In this guide, we will use the [basic_example](examples/basic_example/ "basic_example") sketch provided in the library.

In the first line, make sure to use the correct wifi library. (These libraries are already installed by default).
```cpp
#include <WiFi.h> // * If you use EP32.
//#include <ESP8266WiFi.h> // * If you use an ESP8266 Module.
```
Next, we create an instance of WiFiClient because we will use an internet connection to connect to the things ph broker.
```cpp
WiFiClient espClient;
ThingsPH_MQTT thingsph(espClient);
```

Then, we need to specify the credentials we are going to use. Input your wifi ssid and password, and your ThingsPH credentials. `thingsSerial` is the name of your device (it is automatically created in the platform in case that it doesn't exists).
```cpp
const char* ssid = "...."; // <- Change to your WiFi Name.
const char* password =  "...."; // <- Change to your WiFi Password.
char* thingsUser = "";  // Get the username on things Docs/Guides under MQTT integration
char* thingsPassword = ""; // Get the password on things Docs/Guides under MQTT integration
char* thingsSerial = "test_device_01"; // Hardware Serial, Change this.
```

In the  `setup()` method, we need first to connect to the WiFi. Set the wifi module into station mode to begin the connection:
```cpp
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  Serial.println("Connecting to WiFi..");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println("Connected to the WiFi network");
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());
```
Next, we must prepare the client by calling the `initialize()` method. Afterwards, we will add a `hardware_serial` payload to the JsonDocument. All sensor data must be put inside a nested object with name `payload_fields`.
```cpp
  jsondoc["hardware_serial"] = thingsSerial;
  jsondoc["id"] = WiFi.macAddress();
  telemetry = jsondoc.createNestedObject("payload_fields");
```
In the `loop()` method, we can see that the connect() method is put inside a while loop. It is because we need to make sure every time that the client is connected to the broker before publishing. Then, we will use a mock data that is increasing incrementally  every loop.

To send a the payload or json document, just call the `publish()` function. It returns a boolean value that determines whether the payload is successfully sent or not.
```cpp
if (thingsph.isconnected()) {
    if (thingsph.publish(jsondoc)) {
      Serial.println(F("Successfully sent!"));
    } else {
      Serial.println(F("Unable to send payload."));
    }
    espClient.flush();
  }
```
Note that we call the flush() method of the WiFiClient. This is a fix to prevent random disconnection after publishing a payload.

## FAQs
**1. Does ThingsPH_MQTT can be used in PlatformIO?**
- As long as the target framework is set to "Arduino", this library can be used.

**2. The payload received by the platform is not complete.**
- The client has a default maximum packet size of 2048. You can change this by specifying it in the initialize() method.

**3. Serial monitor says that the payload is successfully sent, but there is no device created in the thingsph platform.**
- Go to the unknown events tab in your console. The most common cause is you have already reached the maximum number of devices available in your account.