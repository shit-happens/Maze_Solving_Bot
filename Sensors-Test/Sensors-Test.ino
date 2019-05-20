#define leftFarSensor      A0
#define leftNearSensor     A1
#define leftCenterSensor   A2
#define rightCenterSensor  A3
#define rightNearSensor    A4
#define rightFarSensor     A5

#define leftMotor1 10 
#define leftMotor2 11 
#define rightMotor1 9 
#define rightMotor2 8 

int leftCenterReading;
int leftNearReading;
int leftFarReading;
int rightCenterReading;
int rightNearReading;
int rightFarReading;

void setup(){
  
  Serial.begin(9600);
  pinMode(leftCenterSensor, INPUT);
  pinMode(leftNearSensor, INPUT);
  pinMode(leftFarSensor, INPUT);
  pinMode(rightCenterSensor, INPUT);
  pinMode(rightNearSensor, INPUT);
  pinMode(rightFarSensor, INPUT);
  pinMode(leftMotor1, OUTPUT); 
  pinMode(leftMotor2, OUTPUT); 
  pinMode(rightMotor1, OUTPUT); 
  pinMode(rightMotor2, OUTPUT);
    
}

void loop(){
    
  leftCenterReading = analogRead(leftCenterSensor); 
  leftNearReading = analogRead(leftNearSensor); 
  leftFarReading = analogRead(leftFarSensor);  
  rightCenterReading = analogRead(rightCenterSensor); 
  rightNearReading = analogRead(rightNearSensor); 
  rightFarReading = analogRead(rightFarSensor);  

// Serial printing below for Debugging purposes:-

  Serial.print("leftFarReading: ");
  Serial.println(leftFarReading);
  Serial.print("leftNearReading: ");
  Serial.println(leftNearReading);
  Serial.print("leftCenterReading: ");
  Serial.println(leftCenterReading);
  Serial.print("rightCenterReading: ");
  Serial.println(rightCenterReading);
  Serial.print("rightNearReading: ");
  Serial.println(rightNearReading);
  Serial.print("rightFarReading: ");
  Serial.println(rightFarReading);
  delay(2000);                                                                                     
  digitalWrite(leftMotor1, HIGH); 
  digitalWrite(leftMotor2, LOW); 
  digitalWrite(rightMotor1, HIGH); 
  digitalWrite(rightMotor2, LOW); 
}
