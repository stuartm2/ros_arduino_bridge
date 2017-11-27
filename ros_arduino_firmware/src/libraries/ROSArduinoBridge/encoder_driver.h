/* *************************************************************
   Encoder driver function definitions - by James Nugen
   ************************************************************ */
   
   
#ifdef ARDUINO_ENC_COUNTER
  //below can be changed, but should be PORTD pins; 
  //otherwise additional changes in the code are required
  #define LEFT_ENC_PIN_A PD2  //pin 2
  #define LEFT_ENC_PIN_B PD3  //pin 3
  
  //below can be changed, but should be PORTC pins
  #define RIGHT_ENC_PIN_A PC4  //pin A4
  #define RIGHT_ENC_PIN_B PC5   //pin A5
#elif defined STM32_ENCODER
  #define encoder0PinA  PB10
  #define encoder0PinB  PB11
  #define encoder1PinA  PB2
  #define encoder1PinB  PB12

  void initEncoders();
#endif
   
long readEncoder(int i);
void resetEncoder(int i);
void resetEncoders();

