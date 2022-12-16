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
Motor::Motor(int pinF, int pinA, bool EoE) {
  moterPinFrequency = pinF;
  moterPinAmplitude = pinA;
}

/**
 * Sets up the motor.
 *
 * @pre {@code pinHeartbeatSensor != null}
 */
void Motor::open() {
  
  // set the pins to the right mode
  pinMode(moterPinFrequency, INPUT);
  pinMode(moterPinAmplitude, INPUT);

  // I am not sure what the " -> " operator does, but at least it compiles.
  // todo remove
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
  // TODO use map function
  double newTarget = (255 / 100) * (0.0 + target);
  analogWrite(moterPinAmplitude, (int) newTarget);
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
  // TODO use map function
  double newTarget = (255 / 100) * (0.0 + target);
  analogWrite(moterPinFrequency, (int) newTarget);
  frequentcy = target;
}

/**
 * gets the current amplitude.
 *
 * @return this.amplitude
 */
int Motor::getAmplitude() {
  Serial.println("[FETCH] ==> Gotten Amplitude: " + String(amplitude) + ".");
  return amplitude;
}

/**
 * gets the current frequentcy.
 *
 * @return this.frequentcy
 */
int Motor::getFrequentcy() {
  Serial.println("[FETCH] ==> Gotten Frequency: " + String(frequentcy) + ".");
  return frequentcy;
}

/**
 * closes the motor.
 */
void Motor::close() {

  // TODO. Maybe code: analogWrite(MOTORPin, 0); 

  Serial.println("[CLOSE] ==> Closed the motor for input.");
}
