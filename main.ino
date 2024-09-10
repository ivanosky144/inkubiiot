#include "wifi_manager.h"
#include "dht_sensor_manager.h"

const char* ssid = "mySSID";
const char* password = "myPassword";


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  connectToWifi(ssid, password);
}

void loop() {
  // put your main code here, to run repeatedly:

}
