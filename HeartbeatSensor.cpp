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
#include "HeartbeatSensor.h"
#define MAX_BABY_HEARTBEAT 160
#define MIN_BABY_HEARTBEAT 90
#define HEARTBEAT_THRESHOLD 4025

/**
 * An object to read the current heartbeat of the baby
 */
HeartbeatSensor::HeartbeatSensor(int pin, int start_amount_of_time_between_measurements, int start_amount_of_measurements) {
  pinHeartbeatSensor = pin;
  amount_of_time_between_measurements = start_amount_of_time_between_measurements;
  amount_of_measurements = start_amount_of_measurements;
}

/**
 * Sets up the heartbeat senor.
 *
 * @pre {@code pinHeartbeatSensor != null}
 */
void HeartbeatSensor::open() {
  pinMode(pinHeartbeatSensor, INPUT);

  // code

  Serial.println("[BUILD] ==> Opened the heartbeat sensor for input.");
}

/**
 * returns the current bpm of the heartbeat sensor.
 *
 * @pre {@code pinHeartbeatSensor != null}
 */
int HeartbeatSensor::next() {
  int result = -1;

  for (int measurementIndex = 0; measurementIndex < amount_of_measurements; measurementIndex++) {

    this -> measure(measurementIndex); 

    delay(amount_of_time_between_measurements);
  }

  // TODO: It needs to filter the received input for glitches.

  int modeOfHighTimeInMs = this -> mode(single_high_array, amount_of_measurements);
  int modeOfLowTimeInMs = this -> mode(single_low_array, amount_of_measurements);
  result = this -> bpm(modeOfHighTimeInMs, modeOfLowTimeInMs);

  Serial.println("[FETCH] ==> Took input from the sensor: " + String(result) + ".");

  // Post-Condition Guard-Statement:
  if (result < MIN_BABY_HEARTBEAT || result > MAX_BABY_HEARTBEAT) {
    Serial.println("[ERROR] ==> this is not with in the baby's normal parameters.");
    exit(1);
  }

  return result;
}

/**
 * closes the heartbeat senor.
 */
void HeartbeatSensor::close() {
  
  //code
  
  Serial.println("[CLOSE] ==> Closed the heartbeat sensor for input.");
}

/**
 * gets the length of high and low state for one period and stores this at the arrays:<ul>
 * <li> single_high_array for the length of the heigh state. <li>
 * <li> single_low_array for the length of the low state. <li>
 *
 * @pre {@code this.ammountOfMeassurement <= 200}
 * @modifies {@code single_high_array}
 * @modifies {@code && single_low_array}
 * @post {@code single_high_array[measurementIndex] > 0 && single_low_array[measurementIndex] > 0}
 * @throws exception if {@code this.ammountOfMeassurement > 200}
 */
void HeartbeatSensor::measure(int measurementIndex) {

  // Pre-Condition Guard-Statement:
  if(measurementIndex > 200) {
    Serial.print("[ERROR] ==> array can only hold at most 200 messurements.");
    exit(1);
  }

  // Reset the previous entry back to zero.
  single_high_array[measurementIndex] = 0;
  single_low_array[measurementIndex] = 0;

  bool hasBeenlow = false;

  while (true) {
    
    // see what the resistance is:
    int input = analogRead(pinHeartbeatSensor);

    // if the read was high enough then the state is actually high, otherwise it remains low.
    int state = LOW;
    if (input >= HEARTBEAT_THRESHOLD) {
      state = HIGH;
    }

    // Guard-statement: if a new cycle begins we break.
    if (state == HIGH && hasBeenlow) {
      return;
    }
    
    if (state == HIGH) { // if it is high we count up the length
      single_high_array[measurementIndex]++;

    } else /*if (state == LOW)*/ {
      hasBeenlow = true;
      single_low_array[measurementIndex]++;
    }

    delay(1);
  }
}

/**
 * calculates the mode of an array
 *
 * @pre {@code array != null}
 * @param array, is an array of integers
 * @param amount_of_measurements, is the length of array that we will use, since
 * @return the mode of the array
 * @post {@code TODO}
 */
int HeartbeatSensor::mode(int array[], int amount_of_measurements) {

  // Pre-Condition Guard-Statement:
  if (amount_of_measurements > 200) {
    Serial.print("[ERROR] ==> array can only hold at most 200 messurements.");
    exit(1);
  }

  int counter = 1;
  int max = 0;
  int mode = array[0];

  for (int index = 0; index < amount_of_measurements - 1; index++) {

    if (array[index] == array[index + 1]) {

      counter++;

      if (counter > max) {
        max = counter;
        mode = array[index];

      } else { // reset counter.
        counter = 1; 
      }
    }
  }

  return mode;
}  

/**
 * Calculates the BPM from the duration of one wave length since that is that is 1 / 
 * 
 * @pre {@code (modeOfHighTimeInMs + modeOfLowTimeInMs) != 0}
 * @param modeOfHighTimeInMs is the mode of the total time (in miliseconds) where the the
 * heartbeat is high.
 * @param modeOfLowTimeInMs is the mode of the total time (in miliseconds) where the the heartbeat
 * is low.
 * @result is the BPM of the baby, given a given a the time it takes for one heartbeat.
 * @post {@code result == (60 * BPS)} where:
 *   {@code BPS ==(1 / waveDuration)} where:
 *   {@code waveDuration == (modeOfHighTimeInMs + modeOfLowTimeInMs)}
 */
int HeartbeatSensor::bpm(int modeOfHighTimeInMs, int modeOfLowTimeInMs) {
  
  // Pre-Condition Guard-Statement:
  if (modeOfHighTimeInMs + modeOfLowTimeInMs == 0) {
    Serial.print(
      "[ERROR] ==> heartbeat time (modeOfHighTimeInMs + modeOfLowTimeInMs) cannot be 0ms."
    );
    exit(1);
  }

  return (60 * (1 / (modeOfHighTimeInMs + modeOfLowTimeInMs)));  
}
