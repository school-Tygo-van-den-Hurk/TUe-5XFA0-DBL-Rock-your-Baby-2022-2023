/**
 * This headerfile is for  the heartbeat sensor object.
 *
 * @author Tygo van den Hurk, Student at TU/e: 1705709
 * @author Luuk Hoekstra, Student at TU/e: 1873474 
 *
 * @version 1.0
 */
// HEARTBEATSENSOR.h
#ifndef HEARTBEATSENSOR_h
#define HEARTBEATSENSOR_h

#include <Arduino.h>
/**
 * An object to read the current heartbeat of the baby
 */
class HEARTBEATSENSOR {
  private:
    int pinHeartbeatSensor;
    int amount_of_time_between_measurements;
    int amount_of_measurements;

  public:
    HEARTBEATSENSOR(int pin, int start_amount_of_time_between_measurements, int start_amount_of_measurements);
    void open();
    int next();
    void close();
};

#endif