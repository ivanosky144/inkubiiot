#include "hdc_sensor_manager.h"
#include <Adafruit_Sensor.h>
#include "Adafruit_HDC1000.h"
#include <Wire.h>

TwoWire I2CHDC = TwoWire(0); 
Adafruit_HDC1000 hdcSensors[4]; 
uint8_t multiplexerPins[3] = {3, 4, 5}; 
uint8_t hdcAddresses[4] = {0x40, 0x41, 0x42, 0x43}; 

void setupMultiplexer() {
  for (int i = 0; i < 3; i++) {
    pinMode(multiplexerPins[i], OUTPUT); 
}

void selectSensor(int sensorIndex) {
  for (int i = 0; i < 3; i++) {
    digitalWrite(multiplexerPins[i], (sensorIndex >> i) & 0x01); 
  }
}

void initializeHDCSensors() {
  I2CHDC.begin(21, 22, 100000); 
  setupMultiplexer(); 

  for (int i = 0; i < 4; i++) {
    selectSensor(i); 

    if (!hdcSensors[i].begin(&I2CHDC)) { 
      Serial.print("Couldn't find HDC1080 sensor ");
      Serial.println(i + 1);
      delay(2000);
      continue; 
    }

    float humidity = htuSensors[i].readHumidity();
    float temperature = htuSensors[i].readTemperature();

    if (humidity < 0 || temperature < -40) {
      Serial.print("Couldn't find HDC sensor ");
      Serial.println(i + 1);
      delay(2000);
    } else {
      Serial.print("HDC Sensor ");
      Serial.print(i + 1);
      Serial.print(" initialized. Humidity: ");
      Serial.print(humidity);
      Serial.print(", Temperature: ");
      Serial.println(temperature);
    }
  }
}

void readHDCSensors(float &t1, float &h1, float &t2, float &h2, float &t3, float &h3, float &t4, float &h4) {
  float* temps[4] = { &t1, &t2, &t3, &t4 };
  float* hums[4] = { &h1, &h2, &h3, &h4 };

  for (int i = 0; i < 4; i++) {
    selectSensor(i); 
    *hums[i] = hdcSensors[i].readHumidity();
    *temps[i] = hdcSensors[i].readTemperature();

    Serial.print("Humidity ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(*hums[i]);
    Serial.print(" Temperature ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.println(*temps[i]);
  }
}
