//////////////////////////////////// Initialize Arduino ////////////////////////////////////////////////////////////
// Import Header Files
#include <Servo.h> 

// Define Pins
// Outputs First...
int HEAD = 6;      // Head servo pin
int VIBRATOR = 7;  // Vibration motor pin
int SPEAKER = 8;   // Piezo pin
int TAIL = 9;      // Tail servo pin
Servo headSERVO;   // create servo object for the head servo
Servo tailSERVO;   // create servo object for the tail servo

// Now Inputs...
int MIC = A0;      // Microphone pin
int BODYFLEX = A1; // Body flex sensor pin
int HEADFLEX = A2; // Head flex sensor pin

void setup() {
  headSERVO.attach(HEAD);
  pinMode(VIBRATOR,OUTPUT);
  pinMode(SPEAKER,OUTPUT);
  tailSERVO.attach(TAIL);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////// Main Code /////////////////////////////////////////////////////////////////
void loop()  {
  // Check Noise Level
  
  // Check For Patting

  // Check For Hugging

  // If Noisy AND Head Pat AND Hugging
  if (NoiseLevel == HIGH && HeadPat == HIGH && Hugging == HIGH) {
    
  }

  // If Noisy AND Head Pat
  if (NoiseLevel == HIGH && HeadPat == HIGH && Hugging == LOW) {
    
  }

  // If Head Pat AND Hugging
  if (NoiseLevel == LOW && HeadPat == HIGH && Hugging == HIGH) {
    
  }

  // If Noisy AND Hugging
  if (NoiseLevel == HIGH && HeadPat == LOW && Hugging == HIGH) {
    
  }

  // If Noisy
  if (NoiseLevel == HIGH && HeadPat == LOW && Hugging == LOW) {
    headturn();
    headturn();
    servoreset();
    tailswish();
    tailswish();
    tailswish();
    servoreset();  
  }

  // If Head Pat
  if (NoiseLevel == LOW && HeadPat == HIGH && Hugging == LOW) {
    bark();
    bark();
    tailswish();
    tailswish();
    tailswish();
    servoreset(); 
  }

  // If Hugging
  if (NoiseLevel == LOW && HeadPat == LOW && Hugging == HIGH) {
    heartbeat();
    heartbeat();
    heartbeat();
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////// User Defined Functions /////////////////////////////////////////////////////////
// Output Functions First...
// Dog Bark Code
void bark() {
  int DurationPerHertz = 10;
  for(int i = 440; i<7040; i+=1){
  tone(SPEAKER,i,DurationPerHertz);  
  }
}

// Head turn Code
void headturn() {
  int rightpos = 30;
  int leftpos = 150;
  int delaytime = 100;
  headSERVO.write(rightpos);
  delay(delaytime);
  headSERVO.write(leftpos);
  delay(delaytime);    
}

// Tail swish Code
void tailswish() {
  int rightpos = 30;
  int leftpos = 150;
  int delaytime = 100;
  tailSERVO.write(rightpos);
  delay(delaytime);
  tailSERVO.write(leftpos);
  delay(delaytime);  
}

// Hertbeat Code
void heartbeat() {
  int spacing = 200;
  digitalWrite(VIBRATOR, HIGH); // LU...
  delay(400);
  digitalWrite(VIBRATOR, LOW);  // ...B
  delay(spacing);
  digitalWrite(VIBRATOR, HIGH); // DU...
  delay(200);
  digitalWrite(VIBRATOR, LOW);  // ...B
  delay(spacing);
}

// Servo Reset Code
void servoreset() {
  int headneutralpos = 90;
  int tailneutralpos = 90;
  headSERVO.write(headneutralpos); 
  tailSERVO.write(tailneutralpos);
}


// Now Input Functions...

double flexDifference(int pin) {
  double flexInitial;
  double flexFinal;
  double flexDifference; 
  flexInitial = analogRead(pin);
  delay(400);
  flexFinal= analogRead(pin);
  flexDifference = (abs(flexInitial-flexFinal)/(abs(flexInitial+flexFinal)/2) * 100);
  return flexDifference;
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
