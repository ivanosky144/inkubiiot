#ifndef MQTT_MANAGER_H
#define MQTT_MANAGER_H

#include <WiFi.h>
#include <PubSubClient.h>

extern PubSubClient client;

void setupMqtt(const char* server, int port, const char* clientID);
void reconnectMqtt(const char* clientID);  // Updated function signature
void publishSensorData(float t1, float h1, float t2, float h2, float t3, float h3, float t4, float h4, int soundLevel);
void mqttCallback(char* topic, byte* payload, unsigned int length);

#endif
