#include "WString.h"
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

/**
 * An object to contol the motors amplitude, and frequentcy.
 */
MOTOR::MOTOR(int pin) {
  MOTORPin = pin;
}

/**
 * Sets up the heartbeat senor.
 *
 * @pre {@code pinHeartbeatSensor != null}
 */
void MOTOR::open() {
  pinMode(MOTORPin, INPUT);
  // I am not sure what the " -> " operator does, but at least it compiles.
  this -> setAmplitude(50);
  this -> setFrequentcy(50);
  Serial.println("[BUILD] => Opened the motor sensor for input.");
}

/**
 * sets the current amplitude.
 * 
 * @param target sets the amplitude to this variable
 * @modifies amplitude
 */
void MOTOR::setAmplitude(int target) {
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
void MOTOR::setFrequentcy(int target) {
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
int MOTOR::getAmplitude() {
  Serial.println("[FETCH] ==> Gotten Amplitude: " + String(amplitude) + ".");
  return amplitude;
}

/**
 * gets the current frequentcy.
 *
 * @return frequentcy
 */
int MOTOR::getFrequentcy() {
  Serial.println("[FETCH] ==> Gotten Frequency: " + String(frequentcy) + ".");
  return frequentcy;
}

/**
 * closes the heartbeat senor.
 *
 * @pre {@code pinMOTOR != null}
 */
void MOTOR::close() {

  // code: analogWrite(MOTORPin, 0); 

  Serial.println("[CLOSE] ==> Closed the motor for input.");
}
