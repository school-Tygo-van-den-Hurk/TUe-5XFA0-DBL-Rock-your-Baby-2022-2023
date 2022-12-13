/**
 * This headerfile is for  the heartbeat sensor object.
 *
 * @author Tygo van den Hurk, Student at TU/e: 1705709
 * @author Luuk Hoekstra, Student at TU/e: 1873474 
 *
 * @version 1.0
 */
// HEARTBEATSENSOR.h
#ifndef HeartbeatSensor_h
#define HeartbeatSensor_h
#include <Arduino.h>
#include "HardwareSerial.h"
#define MAX_BABY_HEARTBEAT 160
#define MIN_BABY_HEARTBEAT 90
/**
 * An object to read the current heartbeat of the baby
 */
class HeartbeatSensor {
  private:
    // private variables
    int pinHeartbeatSensor;
    int amount_of_time_between_measurements;
    int amount_of_measurements;
    int single_high_array[200];
    int single_low_array[200];
    int arrayLength = 200;

    // private methods
    void measure(int measurementIndex);
    int mode(int array[], int amount_of_measurements);
    int bpm(int modeOfHighTimeInMs, int modeOfLowTimeInMs);

  public:
    // constructor
    HeartbeatSensor(int pin, int start_amount_of_time_between_measurements, int start_amount_of_measurements);
    
    // public methods
    void open();
    int next();
    void close();
};

#endif