/***************************************************************
   Motor driver function definitions - by James Nugen
   *************************************************************/

#ifdef L298_MOTOR_DRIVER
  #define RIGHT_MOTOR_BACKWARD PA14
  #define LEFT_MOTOR_BACKWARD  PB5
  #define RIGHT_MOTOR_FORWARD  PB3
  #define LEFT_MOTOR_FORWARD   PB7
  #define RIGHT_MOTOR_ENABLE   PA6
  #define LEFT_MOTOR_ENABLE    PA7
#endif

void initMotorController();
void setMotorSpeed(int i, int spd);
void setMotorSpeeds(int leftSpeed, int rightSpeed);
