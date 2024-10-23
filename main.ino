#include "wifi_manager.h"
#include "hdc_sensor_manager.h"
#include "mqtt_manager.h"
#include <Wire.h> 

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
  
  // Initialize I2C
  Wire.begin(21, 22); // Use your specific GPIOs for SDA and SCL

  Serial.println("I2C Scanner");
  byte error, address;
  int nDevices = 0;

  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.print(address, HEX);
      Serial.println("  !");
      nDevices++;
    } else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0) {
    Serial.println("No I2C devices found\n");
  } else {
    Serial.println("done\n");
  }

  initializeHTUSensors(); // Initialize HDC1080 sensors
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
    readHTUSensors(t1, h1, t2, h2, t3, h3, t4, h4);

    int soundLevel = analogRead(soundSensorPin);
    Serial.printf("Sound sensor level: %d\n", soundLevel);

    publishSensorData(t1, h1, t2, h2, t3, h3, t4, h4, soundLevel);
  }
}
