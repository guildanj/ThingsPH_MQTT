# ThingsPH_MQTT
This library uses [PubSubClient](https://github.com/knolleary/pubsubclient "PubSubClient") by knolleary as it's base mqtt client and [ArduinoJson](https://arduinojson.org/ "ArduinoJson") library. ThingsPH_MQTT functions almost exactly the same as PubSubClient but tweaked to work for ThingsPH Platform and provide easy-to-use functionalities.

# Installation
1. Download the [Arduino IDE](rhttps://www.arduino.cc/en/software/ "Arduino IDE") and install it to your system.
2. Download this library as a .zip file and extract it to your '..\Documents\Arduino\libraries' directory.

# Getting Started
ThingsPH_MQTT provides a basic example you can use to quick start your program.

1. You need to have a WiFi with an internet connection that your device can connect to. Change the values of 'ssid' and 'password' with your wifi credentials.
2. The values of the variables 'thingsSerial' and 'thingsPassword' should be replaced by the mqtt credentials provided by the ThingsPH Platform (You can find it in the [docs section](https://app.things.ph/user-settings/documentation "docs section")). 

# How to Use?

#### Functions
- **initialize()** - This function should be called during the initialization of your device (preferably in the void setup()). There is also an optional parameter for the subscribe callback function.
- **connect()** - Connect to the ThingsPH Platform using the provided credentials.
- **disconnect()** - Safely disconnecto to the ThingsPH MQTT Broker.
- **subscribe(topic)** - Subscribe to the topic (char*) with the callback function registered in the initialize().
- **unsubscribe(topic)** - Safely unsubscribe to the topic (char*).
- **publish(document)** - Publish or send a JsonDocument to the ThingsPH MQTT Broker (&JsonDocument).
- **loop()** - This function should be called inside the void loop().


#### Notes

- ***DO NOT FORGET** to loop the thingsph client by calling the loop() function inside the void loop().
