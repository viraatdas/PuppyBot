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

const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;

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
  bool NoiseLevel = micTest(); 
  
  // Check For Patting
  bool HeadPat = flexDifference(HEADFLEX); 

  // Check For Hugging
   bool Hugging = flexDifference(BODYFLEX); 

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
// Read Audio Loudness Levels from Microphone (And Threshold)
bool micTest() {
       unsigned long startMillis= millis();  // Start of sample window
   unsigned int peakToPeak = 0;   // peak-to-peak level

   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;

   // collect data for 50 mS
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(MIC);
      if (sample < 1024)  // toss out spurious readings
      {
         if (sample > signalMax)
         {
            signalMax = sample;  // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;  // save just the min levels
         }
      }
   }
   peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
   double volts = (peakToPeak * 5.0) / 10;  // convert to volt
   bool k;
   if (volts>20)
        bool k = HIGH;
   else 
        bool k = LOW;

   return k;
  }

// Read Flex Difference Levels from Flex Sensors (And Threshold)
bool flexDifference(int pin) {
  double flexInitial;
  double flexFinal;
  double flexDifference; 
  flexInitial = analogRead(pin);
  delay(400);
  flexFinal= analogRead(pin);
  flexDifference = (abs(flexInitial-flexFinal)/(abs(flexInitial+flexFinal)/2) * 100);
   bool k;
  if (flexDifference>5)
        bool k = HIGH;
   else 
        bool k = LOW;
   return k;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
