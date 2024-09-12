#include "mqtt_manager.h"

WiFiClient espClient;
PubSubClient client(espClient);

const char* mqtt_topic = "sensor/dht";

void setupMqtt(const char* mqtt_server, int mqtt_port) {
  client.setServer(mqtt_server, mqtt_port);
}

void reconnectMqtt() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

    if (client.connect("ESP32Client")) {
      Serial.println("Connected");
    } else {
      Serial.println("Failed");
      Serial.print(client.state());
      delay(5000);
    }
  }
}

void publishSensorData(float t1, float h1, float t2, float h2, float t3, float h3, float t4, float h4) {
  String payload = "{";
  payload += "\"sensor1\":{\"temperature\":" + String(t1) + ", \"humidity\":" + String(h1) + "},";
  payload += "\"sensor2\":{\"temperature\":" + String(t2) + ", \"humidity\":" + String(h2) + "},";
  payload += "\"sensor3\":{\"temperature\":" + String(t3) + ", \"humidity\":" + String(h3) + "},";
  payload += "\"sensor4\":{\"temperature\":" + String(t4) + ", \"humidity\":" + String(h4) + "}";
  payload += "}";

  client.publish(mqtt_topic, payload.c_str());
}