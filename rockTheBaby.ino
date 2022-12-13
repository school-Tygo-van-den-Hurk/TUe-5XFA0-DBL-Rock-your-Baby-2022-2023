/**
 * This program finds the best amplitude and frequentcy for the baby to rock at.
 *
 * @author Tygo van den Hurk, Student at TU/e: 1705709
 * @author Luuk Hoekstra, Student at TU/e: 1873474 
 *
 * @version 1.0
 */
// Define the constands: (you can change this), however, it is ALSO defined in HearbeatSensor.cpp
//  - baby:                                           
 #define MAX_BABY_HEARTBEAT                    160      
 #define MIN_BABY_HEARTBEAT                    90       
//  - measurements:                                    
#define AMOUNT_OF_MEASUREMENTS                1500     
#define AMOUNT_OF_TIME_BETWEEN_MEASUREMENTS   0       // recommended 0.     
#define WEIGHT_ADJUSTMENT                     4        
#define THRESHOLD                             10       
//  - frequentcy:                                     
#define FREQUENTCY_UPPER                      100      
#define FREQUENTCY_LOWER                      0        
#define ACCEPTANCE_SENSITIVITY_FREQUENTCY     1       
//  - amplitude:                                       
#define AMPLITUDE_UPPER                       100      
#define AMPLITUDE_LOWER                       0        
#define ACCEPTANCE_SENSITIVITY_AMPLITUDE      1       
// Define pins: (you can change this)                 // Choose out of these options, and no other.
#define HEARTBEATSENSOR_PIN                   A0      // analog pin  :  {A0, A1, A2, A3, A4}
#define MOTOR_PIN                             3       //    PWM pin  :  {3, 5, 6, 9, 10, 11}
#define SOUNDSENSOR_PIN                       A1      // analog pin  :  {A0, A1, A2, A3, A4}
                                                      
// Define global variables: (do not change)           
int array[AMOUNT_OF_MEASUREMENTS];
int frequentcyUpper = FREQUENTCY_UPPER;
int frequentcyLower = FREQUENTCY_LOWER;
int frequentcyCounter = 0;
int amplitudeUpper = AMPLITUDE_UPPER;
int amplitudeLower = AMPLITUDE_LOWER;
int amplitudeCounter = 0;
int lowerSearch = 0;
int upperSearch = 0;

// Define global Objects: (do not change)
#include "HeartbeatSensor.h"
HeartbeatSensor heartbeatSensor(HEARTBEATSENSOR_PIN, AMOUNT_OF_MEASUREMENTS, AMOUNT_OF_TIME_BETWEEN_MEASUREMENTS);
#include "MOTOR.h"
Motor motor(MOTOR_PIN);
#include "SoundSensor.h"
SoundSensor soundSensor(SOUNDSENSOR_PIN);

// Methods: (do not change)
/*
 * LayOut of the Methods:
 * - void Setup
 *   - void setupSensors
 *   - bool sensorCheck
 * - void loop
 *   - void blink 
 *   - void improveFrequentcy
 *   - void improveAmplitude
 *   - int currentHeartbeat
 *   - int currentCryingStrength
 * - void exiting
 */
 //
//
/**
 * Sets up the sensors, and serial connection, then starts the loop.
 *
 * @pre true
 * @post {@code frequentcy ~= optimal && amplitude ~= optimal}
 */
void setup() {
  
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  
  Serial.println("[BUILD] ==> try setting up the objects.");
  setupSensors();

  Serial.println("[BUILD] ==> check setup of the objects.");
  if (!sensorCheck()) { // they are not set up correctly then that means that something has gone wrong
    Serial.println("[ERROR] ==> There was a problem setting up the connections.");
    exiting();
  }
  
  Serial.println("[ RUN ] ==> Finding optimal solution.");
  // goes to void loop();
}

/**
 * sets up the heartbeat sensor and motor.
 * 
 * @pre {@code motor != null && heartbeatSensor != null}
 */
void setupSensors() {
  heartbeatSensor.open();
  motor.open();
  soundSensor.open();
}

/**
 * checks if the sensors are installed correctly
 *
 * @pre {@code motor != null && heartbeatSensor != null}
 * @return true iff motor and heartbeatSensor are set up correctly
 */
bool sensorCheck() {
  Serial.println("[BUILD] ==> Checking if the sensors are working correctly.");
  
  int motorA = motor.getAmplitude();
  int motorF = motor.getFrequentcy();

  int heartbeatSensorTest = heartbeatSensor.next();

  bool result = (
    (motorA == 50 && motorF == 50) // check motor has correct start values
    &&
    (heartbeatSensorTest >= MIN_BABY_HEARTBEAT && heartbeatSensorTest <= MAX_BABY_HEARTBEAT) // and the heartbeat sensor is returning a valid bmp
  );

  Serial.println("[CHECK] ==> Motor:");
  Serial.println("[CHECK] ==> amplitude   = " + motorA);
  Serial.println("[CHECK] ==> frequentcy  = " + motorF);
  Serial.println("[CHECK] ==> HearBeatSensor:");
  Serial.println("[CHECK] ==> current_bmp = " + heartbeatSensorTest);

  return result; //TODO
}

/**
 * This is the main body of the code, it runs until the optimal frequentcy and amplitude are found.
 *
 * @post {@code frequentcy ~= optimal && amplitude ~= optimal}
 */
void loop() {
  improveFrequentcy();
  improveAmplitude();
  
  // TODO Exception handling

  // to show that we have done one loop, we blink.
  blink();

  // if it has been the same for a while, we break the loop
  if (amplitudeCounter >= THRESHOLD && frequentcyCounter >= THRESHOLD) {
    Serial.println("[CLOSE] ==> Found optimal solution.");
    exiting();
  }
}

/**
 * turns the build in LED on for x seconds.
 *
 * @pre LED_BUILTIN is set to INPUT
 */
void blink() {
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("[ RUN ] ==> Completed one cycle.");
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
}

/**
 * improves the settings for frequentcy for the baby rocking motion.
 * 
 * @pre true
 */
void improveFrequentcy() {

  Serial.println("[ RUN ] ==> improving frequentcy.");

  int middle = (frequentcyUpper + frequentcyLower) / 2;
  Serial.println("[ RUN ] ==> middle := " + middle);

  int adjustmentFromMiddle = (frequentcyUpper + frequentcyLower) / WEIGHT_ADJUSTMENT;
  Serial.println("[ RUN ] ==> adjustmentFromMiddle := " + adjustmentFromMiddle);

  // try upper half
  Serial.println("[ RUN ] ==> Trying upper half:");
  motor.setFrequentcy(middle + adjustmentFromMiddle);
  upperSearch = currentHeartbeat();

  // try lower half
  Serial.println("[ RUN ] ==> Trying lower half:");
  motor.setFrequentcy(middle - adjustmentFromMiddle);
  lowerSearch = currentHeartbeat();

  /*
   * we check if they are similar, if they are, then we up the counter, otherwise we reset. If it goes over the
   * THRESHOLD, we stop the program.
   */ 
  bool upperRange = (upperSearch <= lowerSearch + ACCEPTANCE_SENSITIVITY_FREQUENTCY);
  bool lowerRange = (lowerSearch >= upperSearch - ACCEPTANCE_SENSITIVITY_FREQUENTCY);
  if (upperRange && lowerRange) {
    frequentcyCounter++;
    Serial.println("[ RUN ] ==> amplitudeCounter++ (" + String(frequentcyCounter) + ").");

  } else {
    frequentcyCounter = 0;
    Serial.println("[ RUN ] ==> amplitudeCounter is set to zero.");
  }

  /*
   * if the upper setting lead to a lower heartbeat then this was perfered and then this is where the solution
   * is, else, its on the other side.
   */
  if (upperSearch < lowerSearch) { 
    Serial.println("[ RUN ] ==> optimal frequentcy is in the upper half.");
    frequentcyLower = middle;

  } else {
    Serial.println("[ RUN ] ==> optimal frequentcy is in the lower half.");
    frequentcyUpper = middle;
  }

  return;
}

/**
 * improves the settings for amplitude for the baby rocking motion.
 * 
 * @pre true
 */
void improveAmplitude() {

  Serial.println("[ RUN ] ==> improving amplitude.");

  int middle = (frequentcyUpper + frequentcyLower) / 2;
  Serial.println("[ RUN ] ==> middle := " + middle);

  int adjustmentFromMiddle = (frequentcyUpper + frequentcyLower) / WEIGHT_ADJUSTMENT;
  Serial.println("[ RUN ] ==> adjustmentFromMiddle := " + adjustmentFromMiddle);

  // try upper half
  Serial.println("[ RUN ] ==> Trying upper half:");
  motor.setAmplitude(middle + adjustmentFromMiddle);
  upperSearch = currentHeartbeat();

  // try lower half
  Serial.println("[ RUN ] ==> Trying lower half:");
  motor.setAmplitude(middle - adjustmentFromMiddle);
  lowerSearch = currentHeartbeat();

  /*
   * we check if they are similar, if they are, then we up the counter, otherwise we reset. If it goes over the
   * THRESHOLD, we stop the program.
   */ 
  bool upperRange = (upperSearch <= lowerSearch + ACCEPTANCE_SENSITIVITY_AMPLITUDE);
  bool lowerRange = (lowerSearch >= upperSearch - ACCEPTANCE_SENSITIVITY_AMPLITUDE);
  if (upperRange && lowerRange) {
    amplitudeCounter++;
    Serial.println("[ RUN ] ==> amplitudeCounter++ (" + String(amplitudeCounter) + ").");

  } else {
    amplitudeCounter = 0;
    Serial.println("[ RUN ] ==> amplitudeCounter is set to zero.");
  }

  /*
   * if the upper setting lead to a lower heartbeat then this was perfered and then this is where the solution
   * is, else, its on the other side.
   */
  if (upperSearch < lowerSearch) { 
    Serial.println("[ RUN ] ==> optimal amplitude is in the upper half.");
    amplitudeLower = middle;

  } else {
    Serial.println("[ RUN ] ==> optimal amplitude is in the lower half.");
    amplitudeUpper = middle;
  }

  return;
}

/**
 * Takes n measurements, each with a delay of m miliseconds, then takes the mode of that en then returns that.
 * 
 * @pre {@code heartbeatSensor != null}
 * @return the mode of n measurements, each with a delay of m miliseconds.
 * @post {@code \result == heartbeatSensor.next()}
 */
int currentHeartbeat() {
  return heartbeatSensor.next();
}

/** 
 * Gets the current crying strength of the baby and returns it.
 * 
 * @pre {@code soundSensor != null}
 * @return the current crying strength of the baby .
 * @post {@code \result == soundSensor.next()}
 */
int currentCryingStrength() {
  return soundSensor.next();
}

/**
 * Exits the programm with the exit code, zero meaing correct exicution.
 *
 * @pre {@code heartbeatSensor != null && motor != null}
 * @post we exited the programm 
 */ 
void exiting() {

  Serial.println("[CLOSE] ==> Programm will now terminate.\n");

  heartbeatSensor.close();
  motor.close();
  soundSensor.close();

  exit(0);
}
