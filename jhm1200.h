#ifndef JHM1200_H
#define JHM1200_H

#include <Arduino.h>
#include <Wire.h>

// Adresse I2C du capteur
#define JHM1200_ADDR 0x78

// Commande pour lancer une mesure
#define JHM1200_CMD_MEASURE 0xAC

// Valeurs de calibration pour la pression
#define PMAX 100.0      // Pression maximale (kPa)
#define PMIN 0.0       // Pression minimale (kPa)
#define DMAX 15099494  // Valeur numérique maximale
#define DMIN 1677722   // Valeur numérique minimale

// Valeurs de calibration pour la température
#define TEMP_MAX 150.0   // Température maximale (°C)
#define TEMP_MIN -40.0   // Température minimale (°C)

class JHM1200 {
public:
  JHM1200();

  void begin();

  bool startMeasurement();

  bool readData(unsigned long &pressureRaw, unsigned int &temperatureRaw);

  float convertPressure(unsigned long pressureRaw);

  float convertTemperature(unsigned int temperatureRaw);

};

#endif
