/**
 * This Object will get, and set the frequentcy and amplitude of the motor.
 *
 * @author Tygo van den Hurk, Student at TU/e: 1705709
 * @author Luuk Hoekstra, Student at TU/e: 1873474 
 *
 * @version 1.0
 */
// MOTOR.cpp
#include "HardwareSerial.h"
#include "Arduino.h"
#include "MOTOR.h"
#include "WString.h"

/**
 * An object to contol the motors amplitude, and frequentcy.
 */
Motor::Motor(int pin) {
  MOTORPin = pin;
}

/**
 * Sets up the motor.
 *
 * @pre {@code pinHeartbeatSensor != null}
 */
void Motor::open() {
  pinMode(MOTORPin, INPUT);
  // I am not sure what the " -> " operator does, but at least it compiles.
  this -> setAmplitude(50);
  this -> setFrequentcy(50);
  Serial.println("[BUILD] => Opened the motor for input.");
}

/**
 * sets the current amplitude.
 * 
 * @param target sets the amplitude to this variable
 * @modifies amplitude
 */
void Motor::setAmplitude(int target) {
  Serial.println("[ RUN ] ==> setting amplitude to: " + target);
  double newTarget = (255 / 100) * (0.0 + target);
  analogWrite(MOTORPin, (int) newTarget);
  amplitude = target;
}

/**
 * sets the current frequentcy.
 *
 * @param target sets the frequentcy to this variable
 * @modifies frequentcy
 */
void Motor::setFrequentcy(int target) {
  Serial.println("[ RUN ] ==> setting frequentcy to: " + target);
  double newTarget = (255 / 100) * (0.0 + target);
  analogWrite(MOTORPin, (int) newTarget);
  frequentcy = target;
}

/**
 * gets the current amplitude.
 *
 * @return amplitude
 */
int Motor::getAmplitude() {
  Serial.println("[FETCH] ==> Gotten Amplitude: " + String(amplitude) + ".");
  return amplitude;
}

/**
 * gets the current frequentcy.
 *
 * @return frequentcy
 */
int Motor::getFrequentcy() {
  Serial.println("[FETCH] ==> Gotten Frequency: " + String(frequentcy) + ".");
  return frequentcy;
}

/**
 * closes the motor.
 */
void Motor::close() {

  // code: analogWrite(MOTORPin, 0); 

  Serial.println("[CLOSE] ==> Closed the motor for input.");
}
