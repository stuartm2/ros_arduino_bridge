/* *************************************************************
   Encoder definitions
   
   Add an "#ifdef" block to this file to include support for
   a particular encoder board or library. Then add the appropriate
   #define near the top of the main ROSArduinoBridge.ino file.
   
   ************************************************************ */
   
#ifdef USE_BASE

#ifdef ROBOGAIA
  /* The Robogaia Mega Encoder shield */
  #include "MegaEncoderCounter.h"

  /* Create the encoder shield object */
  MegaEncoderCounter encoders = MegaEncoderCounter(4); // Initializes the Mega Encoder Counter in the 4X Count mode
  
  /* Wrap the encoder reading function */
  long readEncoder(int i) {
    if (i == LEFT) return encoders.YAxisGetCount();
    else return encoders.XAxisGetCount();
  }

  /* Wrap the encoder reset function */
  void resetEncoder(int i) {
    if (i == LEFT) return encoders.YAxisReset();
    else return encoders.XAxisReset();
  }
#elif defined(ARDUINO_ENC_COUNTER)
  volatile long left_enc_pos = 0L;
  volatile long right_enc_pos = 0L;
  static const int8_t ENC_STATES [] = {0,1,-1,0,-1,0,0,1,1,0,0,-1,0,-1,1,0};  //encoder lookup table
    
  /* Interrupt routine for LEFT encoder, taking care of actual counting */
  ISR (PCINT2_vect){
  	static uint8_t enc_last=0;
        
	enc_last <<=2; //shift previous state two places
	enc_last |= (PIND & (3 << 2)) >> 2; //read the current state into lowest 2 bits
  
  	left_enc_pos += ENC_STATES[(enc_last & 0x0f)];
  }
  
  /* Interrupt routine for RIGHT encoder, taking care of actual counting */
  ISR (PCINT1_vect){
        static uint8_t enc_last=0;
          	
	enc_last <<=2; //shift previous state two places
	enc_last |= (PINC & (3 << 4)) >> 4; //read the current state into lowest 2 bits
  
  	right_enc_pos += ENC_STATES[(enc_last & 0x0f)];
  }
  
  /* Wrap the encoder reading function */
  long readEncoder(int i) {
    if (i == LEFT) return left_enc_pos;
    else return right_enc_pos;
  }

  /* Wrap the encoder reset function */
  void resetEncoder(int i) {
    if (i == LEFT){
      left_enc_pos=0L;
      return;
    } else { 
      right_enc_pos=0L;
      return;
    }
  }
#elif defined STM32_ENCODER
  // Borrowed from https://playground.arduino.cc/Main/RotaryEncoders#Example5
  volatile unsigned int encoder0Pos = 0;
  volatile unsigned int encoder1Pos = 0;

  boolean A0_set;
  boolean B0_set;

  boolean A1_set;
  boolean B1_set;

  // Interrupt on A changing state
  void doEncoder0A() {
    // Low to High transition?
    if (digitalRead(encoder0PinA) == HIGH) {
      A0_set = true;
      if (!B0_set) {
        encoder0Pos = encoder0Pos - 1;
      }
    }

    // High-to-low transition?
    if (digitalRead(encoder0PinA) == LOW) {
      A0_set = false;
    }
  }

  // Interrupt on A changing state
  void doEncoder1A() {
    // Low to High transition?
    if (digitalRead(encoder1PinA) == HIGH) {
      A1_set = true;
      if (!B1_set) {
        encoder1Pos = encoder1Pos - 1;
      }
    }

    // High-to-low transition?
    if (digitalRead(encoder1PinA) == LOW) {
      A1_set = false;
    }
  }

  // Interrupt on B changing state
  void doEncoder0B() {
    // Low-to-high transition?
    if (digitalRead(encoder0PinB) == HIGH) {
      B0_set = true;
      if (!A0_set) {
        encoder0Pos = encoder0Pos + 1;
      }
    }

    // High-to-low transition?
    if (digitalRead(encoder0PinB) == LOW) {
      B0_set = false;
    }
  }

  // Interrupt on B changing state
  void doEncoder1B() {
    // Low-to-high transition?
    if (digitalRead(encoder1PinB) == HIGH) {
      B1_set = true;
      if (!A1_set) {
        encoder1Pos = encoder1Pos + 1;
      }
    }

    // High-to-low transition?
    if (digitalRead(encoder1PinB) == LOW) {
      B1_set = false;
    }
  }

  void initEncoders() {
    pinMode(encoder0PinA, INPUT);
    pinMode(encoder0PinB, INPUT);
    pinMode(encoder1PinA, INPUT);
    pinMode(encoder1PinB, INPUT);

    attachInterrupt(encoder0PinA, doEncoder0A, CHANGE);
    attachInterrupt(encoder0PinB, doEncoder0B, CHANGE);
    attachInterrupt(encoder1PinA, doEncoder1A, CHANGE);
    attachInterrupt(encoder1PinB, doEncoder1B, CHANGE);
  }

  long readEncoder(int i) {
    if (i == LEFT) {
      return encoder0Pos;
    } else {
      return encoder1Pos;
    }
  }

  void resetEncoder(int i) {
    if (i == LEFT) {
      encoder0Pos = 0;
    } else {
      encoder1Pos = 0;
    }
  }
#else
  #error A encoder driver must be selected!
#endif

/* Wrap the encoder reset function */
void resetEncoders() {
  resetEncoder(LEFT);
  resetEncoder(RIGHT);
}

#endif

