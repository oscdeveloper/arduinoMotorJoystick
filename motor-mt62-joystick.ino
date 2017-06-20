// start motor setup
int aPhase = 2;    
int aEnable = 3;  
int aMotorSpeed = 0; 

int bPhase = 4;   
int bEnable = 5;
int bMotorSpeed = 0;

float steering;
// end motor setup


// start joystick setup
int xPin = A1;
int yPin = A0;
int buttonPin = 8;

int xPosition = 0;
int yPosition = 0;
int buttonState = 0;

int xPositionValue = 0;             
int yPositionValue = 0;
// end joystick setup




void setup(){

  Serial.begin(9600); 
  
  pinMode(aPhase, OUTPUT);
  pinMode(bPhase, OUTPUT);
  pinMode(aEnable, OUTPUT);
  pinMode(bEnable, OUTPUT);
  
  
//    digitalWrite(aPhase, LOW);
//    digitalWrite(bPhase, LOW);
  digitalWrite(aEnable, aMotorSpeed);
  digitalWrite(aEnable, bMotorSpeed);
  

  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  
}





void loop(){

  xPosition = analogRead(xPin);
  //delay(20);
  yPosition = analogRead(yPin);
  buttonState = digitalRead(buttonPin);

//  Serial.print("Y axis: ");
//  Serial.print(yPosition);
//  Serial.print(" | ");
//  Serial.print("X axis: ");
//  Serial.print(xPosition);
//  Serial.println(" | ");

  if ( yPosition > 545 && yPosition < 550 ) {  
    aMotorSpeed = 0;  
    bMotorSpeed = 0; 
  } else if ( yPosition >= 550 ) { // forward    
    digitalWrite(aPhase, HIGH);
    digitalWrite(bPhase, HIGH);
    aMotorSpeed = map(yPosition, 550, 1018, 0, 155);
    bMotorSpeed = map(yPosition, 550, 1018, 0, 155);
  } else if ( yPosition <= 545 ) { // reverse
    digitalWrite(aPhase, LOW);
    digitalWrite(bPhase, LOW);
    aMotorSpeed = 255 - map(yPosition, 0, 545, 0, 155);
    bMotorSpeed = 255 - map(yPosition, 0, 545, 0, 155);
  }

//  Serial.print("aMotorSpeed: ");
//  Serial.print(aMotorSpeed);
//  Serial.print(" | ");
//  Serial.print("bMotorSpeed: ");
//  Serial.print(bMotorSpeed);
//  Serial.print(" | ");

  if ( xPosition >= 529 && xPosition <= 531 ) {
    steering = 0;
  } else if ( xPosition > 531 ) { // left
    steering = (float)map(xPosition, 532, 1020, 0, 255) / 255; 
    aMotorSpeed -= aMotorSpeed * steering;
  } else if ( xPosition < 529 ) { // right
    steering = ( 255 - (float)map(xPosition, 2, 528, 0, 255) ) / 255;
    bMotorSpeed -= bMotorSpeed * steering;
  }
  
  if ( aMotorSpeed > 255 ) {
    aMotorSpeed = 255;
  }

  if ( bMotorSpeed > 255 ) {
    bMotorSpeed = 255;
  }

  if ( aMotorSpeed < 5 ) {
    aMotorSpeed = 0;
  }

  if ( bMotorSpeed < 5 ) {
    bMotorSpeed = 0;
  }  

//  Serial.print("aMotorSpeed: ");
//  Serial.print(aMotorSpeed);
//  Serial.print(" | ");
//  Serial.print("bMotorSpeed: ");
//  Serial.print(bMotorSpeed);
//  Serial.print(" | ");

  analogWrite(aEnable, aMotorSpeed);
  analogWrite(bEnable, bMotorSpeed);

//  Serial.print("steering: ");
//  Serial.print(steering, DEC);
//  Serial.print(" | ");
//  Serial.print("xPosition: ");
//  Serial.println(xPosition);

  delay(100);

}
