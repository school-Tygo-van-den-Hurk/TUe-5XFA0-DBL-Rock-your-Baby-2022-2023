/**
 * This headerfile is for  the SoundSensor object.
 *
 * @author Tygo van den Hurk, Student at TU/e: 1705709
 * @author Luuk Hoekstra, Student at TU/e: 1873474 
 *
 * @version 1.0
 */
// SoundSensor.h
#ifndef SoundSensor_H
#define SoundSensor_H

#include <Arduino.h>
/**
 * An object to get the baby's crying strength.
 */
class SoundSensor {
  private:
    int SoundSensorPin;
    bool exitOnError;

  public:
    SoundSensor(int pin, bool EoE);
    void open();
    int next();
    void close();
};

#endif