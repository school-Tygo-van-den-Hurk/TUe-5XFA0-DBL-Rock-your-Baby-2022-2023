/**
 * This Object will control the display.
 *
 * @author Tygo van den Hurk, Student at TU/e: 1705709
 * @author Luuk Hoekstra, Student at TU/e: 1873474 
 *
 * @version 1.0
 */
// Display.cpp
#include "Arduino.h"
#include "Display.h"
//! #include "M5Stack.h"

/**
 * An object to control the display.
 */
Display::Display(bool EoE) {
  exitOnError = EoE;
}

/**
 * Sets up the display.
 *
 * @pre {@code M5 != null}
 */
void Display::open() {

  //! M5.begin();
  //! M5.Lcd.setBrightness(200);

  Serial.println("[BUILD] => Opened the Display for input.");
}

/**
 * updates the information on the Display, this includes:
 * <ul>
 *  <li> currentFrequentcy </li>
 *  <li> currentAmplitude </li>
 *  <li> currentBPM </li>
 *  <li> currentTask </li>
 * </ul>
 * @pre {@code M5 != null}
 * @modifies {@code M5.Lcd}
 */
void Display::next() {

  /*
   * resets the display by making it black, then prints the new values over it.
   */
  // M5.Lcd.fillScreen(TFT_BlACK);
  //! m5.Lcd.setCursor(0, 0);
  //! m5.Lcd.println("current Frequentcy: " + currentFrequentcy);
  //! m5.Lcd.setCursor(0, 1);
  //! m5.Lcd.println("current Amplitude: " + currentAmplitude);
  //! m5.Lcd.setCursor(0, 2);
  //! m5.Lcd.println("current BMP: " + currentBPM);
  //! m5.Lcd.setCursor(0, 3);
  //! m5.Lcd.println("current amplitude: " + currentTask);
  //! m5.update();

  Serial.println("[ RUN ] ==> Updated the display information.");
  Serial.println("[ LCD ] ==> current Frequentcy: " + currentFrequentcy);
  Serial.println("[ LCD ] ==> current Amplitude: " + currentAmplitude);
  Serial.println("[ LCD ] ==> current BMP: " + currentBPM);
  Serial.println("[ LCD ] ==> current amplitude: " + currentTask);
  
  return;
}

/**
 * closes the Display senor.
 */
void Display::close() {

  // TODO

  Serial.println("[CLOSE] ==> Closed the Display for input.");
}

/**
 * Updates the value on the screen for the frequentcy.
 */
void Display::updateFrequentcy(int newFrequentcy) {

  currentFrequentcy = newFrequentcy;

  Serial.println(
    "[ RUN ] ==> updated the frequentcy on the screen to: " + String(newFrequentcy) + "."
  );
  this -> next();
}

/**
 * Updates the value on the screen for  the amplitude.
 */
void  Display::updateAmplitude(int newAmplitude) {

  currentAmplitude = newAmplitude;

  Serial.println(
    "[ RUN ] ==> updated the amplitude on the screen to: " + String(newAmplitude) + "."
  );
  this -> next();
}

/**
 * Updates the value on the screen for the current babyHeartRate.
 */
void Display::updateBPM(int newBPM) {

  currentBPM = newBPM;

  Serial.println(
    "[ RUN ] ==> updated the BPM on the screen to: " + String(newBPM) + "."
  );
  this -> next();
}


/**
 * Updates the value on the screen for the current task.
 */
void Display::updateCurrentTask(String newTask) {

  currentTask = newTask

  Serial.println(
    "[ RUN ] ==> updated the frequentcy on the screen to: " + task + "."
  );

  this -> next();
}