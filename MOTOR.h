/**
 * This headerfile is for  the Motor object.
 *
 * @author Tygo van den Hurk, Student at TU/e: 1705709
 * @author Luuk Hoekstra, Student at TU/e: 1873474 
 *
 * @version 1.0
 */
// MOTOR.h
#ifndef MOTOR_h
#define MOTOR_h

#include <Arduino.h>
/**
 * An object to contol the motors amplitude, and frequentcy.
 */
class MOTOR {
  private:
    int MOTORPin;
    int frequentcy;
    int amplitude;

  public:
    MOTOR(int pin);
    void open();
    void setAmplitude(int target);
    void setFrequentcy(int target);
    int getAmplitude();
    int getFrequentcy();
    void close();
};

#endif