/**
 * This program finds the best amplitude and frequentcy for the baby to rock at.
 *
 * @author Tygo van den Hurk, Student at TU/e: 1705709
 * @author Luuk Hoekstra, Student at TU/e: 1873474 
 *
 * @version 1.0
 */
// Define the constands: (you can change this), however, it is ALSO defined in the objects themselves
//  - exit on error:
#define EXIT_ON_ERROR                         true

// Define pins: (you can change this)                 // Choose out of these options, and no other.
#define HEARTBEATSENSOR_PIN                   35      // analog pin  :  {A0, A1, A2, A3, A4}
#define MOTOR_PIN_frequency                   3       //    PWM pin  :  {3, 5, 6, 9, 10, 11}
#define MOTOR_PIN_amplitude                   3       //    PWM pin  :  {3, 5, 6, 9, 10, 11}
#define SOUNDSENSOR_PIN                       36      // analog pin  :  {A0, A1, A2, A3, A4}
                                                      
// Define global variables: (do not change)           
int array[AMOUNT_OF_MEASUREMENTS];

int frequentcyUpper = 5;
int frequentcyLower = 0;
int frequentcyCounter = 0;

int amplitudeUpper = 5;
int amplitudeLower = 0;
int amplitudeCounter = 0;

int lowerSearch = 0;
int upperSearch = 0;

// Define global Objects: (do not change)
#include "headerFiles/HeartbeatSensor.h"
HeartbeatSensor heartbeatSensor(
  HEARTBEATSENSOR_PIN,
  AMOUNT_OF_MEASUREMENTS,
  AMOUNT_OF_TIME_BETWEEN_MEASUREMENTS,
  EXIT_ON_ERROR
);
#include "headerFiles/MOTOR.h"
Motor motor(MOTOR_PIN_frequency, MOTOR_PIN_amplitude, EXIT_ON_ERROR);
#include "headerFiles/SoundSensor.h"
SoundSensor soundSensor(SOUNDSENSOR_PIN, EXIT_ON_ERROR);
#include "headerFiles/Display.h"
Display display(EXIT_ON_ERROR);
#include "headerFiles/CommonMethods.h"
CommonMethods commonMethods(EXIT_ON_ERROR);

/**
 * Sets up the sensors, and serial connection, then starts the loop.
 *
 * @pre true
 * @post {@code frequentcy ~= optimal && amplitude ~= optimal}
 */
void setup() {
  
  // TODO: make GUI on options for algarithms

  Serial.begin(9600);

  Serial.println("[BUILD] ==> try setting up.");

  display.updateCurrentTask("Setting up");

  Serial.println("[BUILD] ==> please chose an algorithm to calm the baby.");
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

  // unreachable code, both objects will terminate when they've found a solution, but in case not:
  commonMethods.exitting(0);
}

/* *
  // they are not set up correctly then that means that something has gone wrong
  //commonMethods.setupSensors();
  // Serial.println("[BUILD] ==> check setup of the objects.");
  /*if (!sensorCheck()) { 

    Serial.println("[ERROR] ==> There was a problem setting up the connections.");
    if (EXIT_ON_ERROR) { 
      exiting(1);
    
    } else {
      delay(10000);
      Serial.println("[BUILD] ==> We will try again.");
      setup();
      exit(0);
    }    
  }
  
  Serial.println("[ RUN ] ==> Finding optimal solution.");
  display.updateCurrentTask("Finding Optimal Solution");
  
  // use an algarithm depending on the setting
  if (useBinarySearch) { // TODO make it depent on a switch on the board
    binarySearch.setup();
    
  } else{
    pathFinding.setup();
  }


 * checks if the sensors are installed correctly
 *
 * @pre {@code motor != null && heartbeatSensor != null}
 * @return true iff motor and heartbeatSensor are set up correctly
 * /
bool sensorCheck() {
  
  Serial.println("[BUILD] ==> Checking if the sensors are working correctly.");

  // motor check
  Serial.println("[CHECK] ==> Motor:");
  int motorA = motor.getAmplitude();
  Serial.println("[CHECK] ==> amplitude   = " + motorA);
  int motorF = motor.getFrequentcy();
  Serial.println("[CHECK] ==> frequentcy  = " + motorF);

  // heartbeat check
  Serial.println("[CHECK] ==> HearBeatSensor:");
  int heartbeatSensorTest = currentHeartbeat();
  Serial.println("[CHECK] ==> current_bmp = " + heartbeatSensorTest);

  // sound check
  Serial.println("[CHECK] ==> SoundSensor:");
  int soundSensorTest = currentCryingStrength();
  Serial.println("[CHECK] ==> current_bmp = " + soundSensorTest);

  // display check
  Serial.println("[CHECK] ==> Display:");
  display.updateCurrentTask("testing");
  Serial.println("[CHECK] ==> currentTask = testing");

  // to make sure that you can see the display
  delay(2000);
  
  bool result = (

    // check motor has correct start values
    (motorA == 50 && motorF == 50) &&

    // and the heartbeat sensor is returning a valid bmp
    (heartbeatSensorTest >= MIN_BABY_HEARTBEAT && heartbeatSensorTest <= MAX_BABY_HEARTBEAT) &&

    // and the sound sensor is returning a valid bmp
    (soundSensorTest != 0 && soundSensorTest != NULL)
  );

  return result;
}*/

/**
 * Is used for the user to make a choice between the algarithms.
 * 
 * @return true if we want to use the PathFinding, or BinarySearch algarithm.
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
 * loop method for the ardruino, is unused.
 *
 * @pre true
 */
void loop() { /* unused method, that has to be here for the compiler */}
