/***** goForwardAndShoot.ino
Written by Luis Sanchez 21 February 2018 *****/

int leftLauncherDirection = 24;   //Choosing Pins for H-bridge Launcher
int rightLauncherDirection = 25; 
int leftLauncherSpeed = 11;
int rightLauncherSpeed = 10;

int leftWheelDirection1 = 26;     // Choosing Pins for H-bridge goForward    // IN1
int leftWheelDirection2 = 27;                                                // IN2
int rightWheelDirection1 = 28;                                               // IN3
int rightWheelDirection2 = 29;                                               // IN4

int encoderReaderA = 2;           // Choosing Pins for encoder
int encoderReaderB = 3;                // Storing variables for encoder
int encoderValueA;
int encoderValueB; 

int angle = 0;
float DistanceTravelled;
const float pi = 3.141592654;

void setup(){
                                            //Feeder initialization
  
  pinMode(leftLauncherDirection,OUTPUT);    // Launcher initialization 
  pinMode(rightLauncherDirection,OUTPUT);
  pinMode(leftLauncherSpeed,OUTPUT);
  pinMode(rightLauncherSpeed,OUTPUT);
  
  pinMode(leftWheelDirection1,OUTPUT);      // Displacement intialization
  pinMode(leftWheelDirection2,OUTPUT);
  pinMode(rightWheelDirection1,OUTPUT);
  pinMode(rightWheelDirection2,OUTPUT);
  
  pinMode(encoderReaderA,INPUT);            // Encoder initialization
  pinMode(encoderReaderB,INPUT);          
 
  Serial.begin(9600);                      // Communication initialization for debugging 
  encoderValueB = digitalRead(encoderReaderA);
}

void loop(){
  Encoder();
  do {
    goForward (500);
  } while (DistanceTravelled <= 50);

  do {
    Stop();
  } while (DistanceTravelled > 50); 
}
                  

void launch (int launcherSpeed, int timeLaps1) {
  Serial.print("LauncherSpeed Value: "); Serial.print(launcherSpeed); // Print the PWM value
  digitalWrite(leftLauncherDirection ,LOW);                           // Makes the motor turn 
  digitalWrite(rightLauncherDirection ,LOW);                          // to the speed desired from 0 to 255
  analogWrite(leftLauncherSpeed,launcherSpeed);
  analogWrite(rightLauncherSpeed,launcherSpeed);
  delay(timeLaps1);
  analogWrite(leftLauncherSpeed,0);
  analogWrite(rightLauncherSpeed,0);
}

void goForward (int timeLaps2) {
  Encoder ();                                 
 //Serial.print("Go Forward");
  digitalWrite(leftWheelDirection1,LOW);            // Directions need to have opposite polarity for the motor to turn
  digitalWrite(leftWheelDirection1,HIGH);                            
  digitalWrite(rightWheelDirection2,LOW);
  digitalWrite(rightWheelDirection2,HIGH);
}

void Encoder () {
 encoderValueA = digitalRead(encoderReaderA); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   
   if (encoderValueA != encoderValueB)       // If the outputB state is different to the outputA state, that means the encoder is turning
     {   
      if (digitalRead(encoderReaderB) != encoderValueA) { 
       angle ++;                            // The encoder is rotating clockwise
     } else {
       angle --;                            // The encoder is rotating counter clockwise
     }
     encoderValueB = encoderValueA;
     DistanceTravelled = angle*3.3*(pi/20);          // Calculate the distance travelled by the encoder in (cm)
     Serial.print("Distance: ");      
     Serial.print(DistanceTravelled);
     Serial.println("cm");
   }
}

void Stop(){
  Encoder ();                   
  digitalWrite(leftWheelDirection1,LOW);                      
  digitalWrite(leftWheelDirection1,LOW);                            
  digitalWrite(rightWheelDirection2,LOW);
  digitalWrite(rightWheelDirection2,LOW);
  //Serial.println("Motor stop");
}



