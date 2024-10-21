#include "mqtt_manager.h"
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient client(espClient);

void setupMqtt(const char* server, int port, const char* clientID) {
  client.setServer(server, port);
  client.setCallback(mqttCallback);
  reconnectMqtt(clientID);  // Pass client ID here
}

void reconnectMqtt(const char* clientID) {
  while (!client.connected()) {
    Serial.println("[MQTT] Connecting to broker...");
    if (client.connect(clientID)) {  // Use client ID here
      Serial.println("[MQTT] Connected to broker");
      client.subscribe("sensor/dht");
    } else {
      Serial.print("[MQTT] Failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5 seconds...");
      delay(5000);
    }
  }
}

void publishSensorData(float t1, float h1, float t2, float h2, float t3, float h3, float t4, float h4, int soundLevel) {
  String payload = "[" +
                   String("{\"temperature\":") + String(t1, 2) + ",\"humidity\":" + String(h1, 2) + "}," +
                   String("{\"temperature\":") + String(t2, 2) + ",\"humidity\":" + String(h2, 2) + "}," +
                   String("{\"temperature\":") + String(t3, 2) + ",\"humidity\":" + String(h3, 2) + "}," +
                   String("{\"temperature\":") + String(t4, 2) + ",\"humidity\":" + String(h4, 2) + "}" +
                   "]";

  client.publish("sensor/dht", payload.c_str());
}



void mqttCallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.println(topic);
}
