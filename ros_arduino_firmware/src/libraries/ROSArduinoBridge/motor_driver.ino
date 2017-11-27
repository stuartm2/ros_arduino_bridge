/***************************************************************
   Motor driver definitions
   
   Add a "#elif defined" block to this file to include support
   for a particular motor driver.  Then add the appropriate
   #define near the top of the main ROSArduinoBridge.ino file.
   
   *************************************************************/

#ifdef USE_BASE
   
#ifdef POLOLU_VNH5019
  /* Include the Pololu library */
  #include "DualVNH5019MotorShield.h"

  /* Create the motor driver object */
  DualVNH5019MotorShield drive;
  
  /* Wrap the motor driver initialization */
  void initMotorController() {
    drive.init();
  }

  /* Wrap the drive motor set speed function */
  void setMotorSpeed(int i, int spd) {
    if (i == LEFT) drive.setM1Speed(spd);
    else drive.setM2Speed(spd);
  }

  // A convenience function for setting both motor speeds
  void setMotorSpeeds(int leftSpeed, int rightSpeed) {
    setMotorSpeed(LEFT, leftSpeed);
    setMotorSpeed(RIGHT, rightSpeed);
  }
#elif defined POLOLU_MC33926
  /* Include the Pololu library */
  #include "DualMC33926MotorShield.h"

  /* Create the motor driver object */
  DualMC33926MotorShield drive;
  
  /* Wrap the motor driver initialization */
  void initMotorController() {
    drive.init();
  }

  /* Wrap the drive motor set speed function */
  void setMotorSpeed(int i, int spd) {
    if (i == LEFT) drive.setM1Speed(spd);
    else drive.setM2Speed(spd);
  }

  // A convenience function for setting both motor speeds
  void setMotorSpeeds(int leftSpeed, int rightSpeed) {
    setMotorSpeed(LEFT, leftSpeed);
    setMotorSpeed(RIGHT, rightSpeed);
  }
#elif defined L298_MOTOR_DRIVER
  void initMotorController() {
    pinMode(LEFT_MOTOR_FORWARD, OUTPUT);
    pinMode(LEFT_MOTOR_BACKWARD, OUTPUT);
    pinMode(RIGHT_MOTOR_FORWARD, OUTPUT);
    pinMode(RIGHT_MOTOR_BACKWARD, OUTPUT);
    pinMode(LEFT_MOTOR_ENABLE, OUTPUT);
    pinMode(RIGHT_MOTOR_ENABLE, OUTPUT);

    digitalWrite(LEFT_MOTOR_FORWARD, LOW);
    digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
    digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
    digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
    analogWrite(LEFT_MOTOR_ENABLE, 0);
    analogWrite(RIGHT_MOTOR_ENABLE, 0);
  }
  
  void setMotorSpeed(int i, int spd) {
    int fwdPin = LEFT_MOTOR_FORWARD;
    int backPin = LEFT_MOTOR_BACKWARD;
    int enPin = LEFT_MOTOR_ENABLE;

    if (i == RIGHT) {
      fwdPin = RIGHT_MOTOR_FORWARD;
      backPin = RIGHT_MOTOR_BACKWARD;
      enPin = RIGHT_MOTOR_ENABLE;
    }

    if (spd < 0) { // Backwards
      digitalWrite(fwdPin, LOW);
      digitalWrite(backPin, HIGH);
    } else if (spd > 0) { // Forwards
      digitalWrite(fwdPin, HIGH);
      digitalWrite(backPin, LOW);
    } else { // Stop
      digitalWrite(fwdPin, LOW);
      digitalWrite(backPin, LOW);
    }

    analogWrite(enPin, abs(spd));
  }
  
  void setMotorSpeeds(int leftSpeed, int rightSpeed) {
    setMotorSpeed(LEFT, leftSpeed);
    setMotorSpeed(RIGHT, rightSpeed);
  }
#else
  #error A motor driver must be selected!
#endif

#endif
