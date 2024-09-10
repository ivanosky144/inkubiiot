#ifndef DHT_SENSOR_MANAGER_H
#define DHT_SENSOR_MANAGER_H

#define DHTPIN1 5  // GPIO pin connected to DHT22 sensor 1
#define DHTPIN2 4  // GPIO pin connected to DHT22 sensor 2
#define DHTPIN3 14 // GPIO pin connected to DHT22 sensor 3
#define DHTPIN4 12 // GPIO pin connected to DHT22 sensor 4

#define DHTTYPE DHT22

void initializeSensors();
void readDHTSensors(float &t1, float &t2, float &t3, float &t4, float &h1, float &h2, float &h3, float &h4);

#endif