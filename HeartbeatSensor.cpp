/**
 * This Object will get the current heartbeat of the baby.
 *
 * @author Tygo van den Hurk, Student at TU/e: 1705709
 * @author Luuk Hoekstra, Student at TU/e: 1873474 
 *
 * @version 1.0
 */
// HEARTBEATSENSOR.cpp
#include "HardwareSerial.h"
#include "Arduino.h"
#include "HEARTBEATSENSOR.h"

/**
 * An object to read the current heartbeat of the baby
 */
HEARTBEATSENSOR::HEARTBEATSENSOR(int pin, int start_amount_of_time_between_measurements, int start_amount_of_measurements) {
  pinHeartbeatSensor = pin;
  amount_of_time_between_measurements = start_amount_of_time_between_measurements;
  amount_of_measurements = start_amount_of_measurements;
}

/**
 * Sets up the heartbeat senor.
 *
 * @pre {@code pinHeartbeatSensor != null}
 */
void HEARTBEATSENSOR::open() {
  pinMode(pinHeartbeatSensor, INPUT);

  // code

  Serial.println("[BUILD] ==> Opened the heartbeat sensor for input.");
}

/**
 * returns the current bpm of the heartbeat sensor.
 *
 * @pre {@code pinHeartbeatSensor != null}
 */
int HEARTBEATSENSOR::next() {
  int result = 1;

  for (int measurementIndex = 0; measurementIndex < amount_of_measurements; measurementIndex++) {

    // code ~= array[measurementIndex] = analogRead(pinHeartbeatSensor);

    delay(amount_of_time_between_measurements);
  }

  //result = mode(array);

  Serial.println("[QUEST] ==> Took input from the sensor: " + String(result) + ".");

  return result;
}

/**
 * closes the heartbeat senor.
 *
 * @pre {@code pinHeartbeatSensor != null}
 */
void HEARTBEATSENSOR::close() {
  
  //code
  
  Serial.println("[CLOSE] ==> Closed the heartbeat sensor for input.");
}
