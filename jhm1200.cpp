#include "jhm1200.h"

JHM1200::JHM1200() {}

void JHM1200::begin() {
  Wire.begin();
}

bool JHM1200::startMeasurement() {
  Wire.beginTransmission(JHM1200_ADDR);
  Wire.write(JHM1200_CMD_MEASURE);
  byte error = Wire.endTransmission();
  return (error == 0);
}

bool JHM1200::readData(unsigned long &pressureRaw, unsigned int &temperatureRaw) {
  byte status = 0xFF;
  unsigned long startTime = millis();
  while ((status & 0x20) && (millis() - startTime < 2000)) {
    Wire.requestFrom(JHM1200_ADDR, 1);
    if (Wire.available()) {
      status = Wire.read();
    }
    delay(50);
  }

  if (status & 0x20) {
    return false;
  }

  Wire.requestFrom(JHM1200_ADDR, 5);
  if (Wire.available() >= 5) {
    byte receivedStatus = Wire.read();
    byte bridgeHigh = Wire.read();
    byte bridgeMid = Wire.read();
    byte bridgeLow = Wire.read();
    byte tempHigh = Wire.read();
    byte tempLow = Wire.read();

    pressureRaw = (bridgeHigh << 16) | (bridgeMid << 8) | bridgeLow;
    temperatureRaw = (tempHigh << 8) | tempLow;
    return true;
  } else {
    return false;
  }
}

float JHM1200::convertPressure(unsigned long pressureRaw) {
  return (PMAX - PMIN) / (float)(DMAX - DMIN) * (pressureRaw - DMIN) + PMIN;
}

float JHM1200::convertTemperature(unsigned int temperatureRaw) {
  return (temperatureRaw / 65536.0) * (TEMP_MAX - TEMP_MIN) + TEMP_MIN;
}
