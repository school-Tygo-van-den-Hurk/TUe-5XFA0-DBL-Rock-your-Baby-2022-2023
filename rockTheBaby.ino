/**
 * This program finds the best amplitude and frequentcy for the baby to rock at.
 *
 * @author Tygo van den Hurk, Student at TU/e: 1705709
 * @author Luuk Hoekstra, Student at TU/e: 1873474 
 *
 * @version 1.0
 */
///
/*
 * Define the constands: (you can change this), however, there are also some defined in the objects
 * themselves
 */
// Define pins: (you can change this)                 // Choose out of these options, and no other.
#define HEARTBEATSENSOR_PIN                   35      // analog pin  :  {A0, A1, A2, A3, A4}
#define MOTOR_PIN_frequency                   3       //    PWM pin  :  {3, 5, 6, 9, 10, 11}
#define MOTOR_PIN_amplitude                   3       //    PWM pin  :  {3, 5, 6, 9, 10, 11}
#define SOUNDSENSOR_PIN                       36      // analog pin  :  {A0, A1, A2, A3, A4}
 
// Define global Objects: (do not change)
#include <headerFiles/HeartbeatSensor.h>
/** Sensor to measure the heartbeat of the baby */
HeartbeatSensor heartbeatSensor(HEARTBEATSENSOR_PIN);

#include <headerFiles/MOTOR.h>
/** Object to control the motors to rock the baby */
Motor motor(MOTOR_PIN_frequency, MOTOR_PIN_amplitude);

#include <headerFiles/SoundSensor.h>
/** Sensor to measure the crying level of the baby */
SoundSensor soundSensor(SOUNDSENSOR_PIN);

#include <M5Stack.h>
#include <headerFiles/Display.h>
/** Object to control the M5Stack's Display */
Display display();

#include <headerFiles/Common.h>
/** Object to acces common functions */
Common common(&heartbeatSensor, &motor, &soundSensor, &display);

#include <headerFiles/BinarySearch.h>
/** Algarithm to calm the baby down. */
BinarySearch binarySearch(&common);

#include <headerFiles/PathFinding.h>
/** Algarithm to calm the baby down. */
PathFinding pathFinding(&common);

#include <headerFiles/Exception.h>
//
/*
 * Contains the following methods (in this order):
 *  - void setup;
 *  - bool usePathFinding();
 *  - void loop().
 */
//
/**
 * @brief Sets up the sensors, and serial connection, then starts the loop.
 *
 * @pre true
 * @post {@code frequentcy ~= optimal && amplitude ~= optimal}
 * @since 1.0
 */
void setup() {

  Serial.begin(9600);
  Serial.println("[BUILD] ==> try setting up.");

  commonMethods.setupSensors();
  display.drawOptions();
  Serial.println("[BUILD] ==> please chose an algorithm to calm the baby.");
  /** Wether or not to use PathFinding, if false BinarySearch will be used. */
  bool usePathFindingBool = usePathFinding();

  if (usePathFindingBool) {
    Serial.println("[BUILD] ==> You've chosen Pathfinding.");
    display.updateCurrentAlgorithm("Pathfinding");
    pathFinding.setup();
  }
  
  else {
    Serial.println("[BUILD] ==> You've chosen BinarySearch.");
    display.updateCurrentAlgorithm("BinarySearch");
    binarySearch.setup();
  }

  /*
   * unreachable code, both objects will terminate when they've found a solution, but in case not,
   * we run the exit method ourselves, with exit code 1 since that is not supposed to happen.
   */
  Serial.println("[ERROR] ==> You've somehow reached unreachable code.");
  Serial.println("            this was at: void RockYourBaby::setup()");
  Exception::thrown();
}

/**
 * @brief Is used for the user to make a choice between the algarithms.
 * 
 * @return true if we want to use the PathFinding, or BinarySearch algarithm.
 * @since 1.0
 */
bool usePathFinding() {

  while (true) {

    // if the user presses the first button, then we use PathFinding.
    if (M5.BtnA.isReleased()) {
      return true;
    } 
        
    // if the user presses the first button, then we use PathFinding.
    else if (M5.BtnB.isReleased()) {
      return false;
    }
  }
}

/**
 * @brief loop method for the ardruino, is unused. But since the ardiuno expects there to be one, we'll 
 * leave it in.
 *
 * @pre true
 */
void loop() {
  //
  /*
   * unused method, that has to be here for the compiler, since an arduino expects a loop method.
   */
  //
}
