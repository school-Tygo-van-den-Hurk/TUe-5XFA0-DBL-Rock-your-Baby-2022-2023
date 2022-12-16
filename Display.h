/**
 * This headerfile is for  the Display object.
 *
 * @author Tygo van den Hurk, Student at TU/e: 1705709
 * @author Luuk Hoekstra, Student at TU/e: 1873474 
 *
 * @version 1.0
 */
// Display.h
#ifndef Display_H
#define Display_H

#include <Arduino.h>
/**
 * An object to control the display.
 */
class Display {
  private:
    int currentBPM;
    int currentFrequentcy;
    int currentAmplitude;
    String currentTask;
    bool exitOnError;

  public:
    Display(bool EoE);
    void open();
    void next();
    void close();
    void updateBPM(int newBPM);
    void updateFrequentcy(int newFrequentcy);
    void updateAmplitude(int newAmplitude);
    void updateCurrentTask(String newTask);
};

#endif