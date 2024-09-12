#include "wifi_manager.h"
#include "dht_sensor_manager.h"
#include "mqtt_manager.h"

const char* ssid = "mySSID";
const char* password = "myPassword";
const char* mqtt_server = "myBroker";
const int mqtt_port = 1883;

float t1, h1, t2, h2, t3, h3, t4, h4;

void setup() {
  Serial.begin(115200);

  connectToWifi(ssid, password);

  setupMqtt(mqtt_server, mqtt_port);
}

void loop() {
  readDHTSensors(t1, t2, t3, t4, h1, h2, h3, h4);

  if (isnan(h1) || isnan(t1) || isnan(h2) || isnan(t2) || isnan(h3) || isnan(t3) || isnan(h4) || isnan(t4)) {
    Serial.println("Failed to read from DHT sensors!");
    return;
  }

  publishSensorData(t1, h1, t2, h2, t3, h3, t4, h4);

  delay(2000);
}
