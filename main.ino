#include "wifi_manager.h"
#include "dht_sensor_manager.h"
#include "mqtt_manager.h"

const char* ssid = "vivo Y36 5G";
const char* password = "modalbos123";
const char* mqtt_server = "test.mosquitto.org"; 
const int mqtt_port = 1883;
const char* mqtt_client_id = "ESP32";  

unsigned long lastPublishTime = 0;
const unsigned long publishInterval = 5000;  

float t1, h1, t2, h2, t3, h3, t4, h4;
const int soundSensorPin = A0;

void setup() {
  Serial.begin(115200);
  Serial.println("Testing setup");

  connectToWiFi(ssid, password);
  initializeDHTSensors();
  setupMqtt(mqtt_server, mqtt_port, mqtt_client_id);  
  pinMode(soundSensorPin, INPUT);
}

void loop() {
  if (!client.connected()) {
    reconnectMqtt(mqtt_client_id);  
  }
  client.loop();  

  if (millis() - lastPublishTime >= publishInterval) {
    lastPublishTime = millis();
    readDHTSensors(t1, h1, t2, h2, t3, h3, t4, h4);

    int soundLevel = analogRead(soundSensorPin);
    Serial.printf("Sound sensor level: %d\n", soundLevel);

    publishSensorData(t1, h1, t2, h2, t3, h3, t4, h4, soundLevel);
  }
}
