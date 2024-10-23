#ifndef HDC_SENSOR_MANAGER_H
#define HDC_SENSOR_MANAGER_H

#define HDC1080_ADDRESS1 0x40
#define HDC1080_ADDRESS2 0x41
#define HDC1080_ADDRESS3 0x42
#define HDC1080_ADDRESS4 0x43

void initializeHDCSensors();
void readHDCSensors(float &t1, float &t2, float &t3, float &t4, float &h1, float &h2, float &h3, float &h4);

#endif