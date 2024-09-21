#include "dht_sensor_manager.h"
#include <DHT.h>

DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);
DHT dht3(DHTPIN3, DHTTYPE);
DHT dht4(DHTPIN4, DHTTYPE);

void initializeDHTSensors() {
  dht1.begin();
  dht2.begin();
  dht3.begin();
  dht4.begin();
}

void readDHTSensors(float &t1, float &h1, float &t2, float &h2, float &t3, float &h3, float &t4, float &h4) {
  h1 = dht1.readHumidity();
  t1 = dht1.readTemperature();
  h2 = dht2.readHumidity();
  t2 = dht2.readTemperature();
  h3 = dht3.readHumidity();
  t3 = dht3.readTemperature();
  h4 = dht4.readHumidity();
  t4 = dht4.readTemperature();
}
