/**
 * This Object will get the crying strength of the baby.
 *
 * @author Tygo van den Hurk, Student at TU/e: 1705709
 * @author Luuk Hoekstra, Student at TU/e: 1873474 
 *
 * @version 1.0
 */
// SoundSensor.cpp
#include "Arduino.h"
#include "SoundSensor.h"

/**
 * An object to get the baby's crying strength.
 */
SoundSensor::SoundSensor(int pin) {
  SoundSensorPin = pin;
}

/**
 * Sets up the SoundSensor senor.
 *
 * @pre {@code SoundSensorPin != null}
 */
void SoundSensor::open() {
  pinMode(SoundSensorPin, INPUT);
  
  // TODO

  Serial.println("[BUILD] => Opened the sound sensor for input.");
}

/**
 * gets the crying strength of the baby.
 *
 * @pre {@code SoundSensorPin != null}
 * @return the crying strength of the baby
 */
int SoundSensor::next() {
  
  int result = 0;

  // TODO

  Serial.println("[FETCH] ==> Gotten current crying strength: " + String(result) + ".");
  
  return result;
}

/**
 * closes the SoundSensor senor.
 *
 * @pre {@code SoundSensorPin != null}
 */
void SoundSensor::close() {

  // code: analogWrite(MOTORPin, 0); TODO

  Serial.println("[CLOSE] ==> Closed the SoundSensor for input.");
}
