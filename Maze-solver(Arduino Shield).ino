#include <AFMotor.h>

AF_DCMotor motorA(1);
AF_DCMotor motorB(3);
int vSpeed = 80;        // MAX 255
int turn_speed = 255;    // MAX 255 

#define leftFarSensor      A0
#define leftNearSensor     A1
#define leftCenterSensor   A2
#define rightCenterSensor  A3
#define rightNearSensor    A4
#define rightFarSensor     A5

int leftCenterReading;
int leftNearReading;
int leftFarReading;
int rightCenterReading;
int rightNearReading;
int rightFarReading;

int leftNudge;
int replaystage;
int rightNudge;

#define leapTime 200

char path[30] = {};
int pathLength;
int readLength;

void setup(){
  Serial.begin(9600);  
  pinMode(leftCenterSensor, INPUT);
  pinMode(leftNearSensor, INPUT);
  pinMode(leftFarSensor, INPUT);
  pinMode(rightCenterSensor, INPUT);
  pinMode(rightNearSensor, INPUT);
  pinMode(rightFarSensor, INPUT);
    
//   Turn ON Motor
  motorA.setSpeed(80);
  motorB.setSpeed(80); 
  motorA.run(RELEASE);
  motorB.run(RELEASE);
  delay(100);
}


void loop(){
  
 readSensors();                                                                                     
 
 if(leftFarReading>200 && rightFarReading>200 && 
   (leftCenterReading<200 || rightCenterReading<200) ){ 
    straight();                                                                                      
  }
  else{                                                                                              
    leftHandWall();                                                                                   
  }

}

void readSensors(){
  
  leftCenterReading  = analogRead(leftCenterSensor);
  leftNearReading    = analogRead(leftNearSensor);
  leftFarReading     = analogRead(leftFarSensor);
  rightCenterReading = analogRead(rightCenterSensor);
  rightNearReading   = analogRead(rightNearSensor);
  rightFarReading    = analogRead(rightFarSensor);  

// serial printing below for debugging purposes

// Serial.print("leftCenterReading: ");
// Serial.println(leftCenterReading);
// Serial.print("leftNearReading: ");
// Serial.println(leftNearReading);
// Serial.print("leftFarReading: ");
// Serial.println(leftFarReading);
  
// Serial.print("rightCenterReading: ");
// Serial.println(rightCenterReading);
// Serial.print("rightNearReading: ");
// Serial.println(rightNearReading);
// Serial.print("rightFarReading: ");
// Serial.println(rightFarReading);
// delay(200);
  
}


void leftHandWall(){
  

  if( leftFarReading<200 && rightFarReading<200){
    motorA.run(FORWARD);
    motorB.run(FORWARD);
    motorA.setSpeed(vSpeed);
    motorB.setSpeed(vSpeed);
    delay(leapTime);
    readSensors();
    
    if(leftFarReading<200 || rightFarReading<200){
      done();
    }
    if(leftFarReading>200 && rightFarReading>200){ 
      turnLeft();
    }
    
  }
  
  if(leftFarReading<200){ // if you can turn left then turn left
    motorA.run(FORWARD);
    motorB.run(FORWARD);
    motorA.setSpeed(vSpeed);
    motorB.setSpeed(vSpeed);
    delay(leapTime);
    readSensors();
      
      if(leftFarReading>200 && rightFarReading>200){
        turnLeft();
      }
      else{
        done();
      }
  }
   
  if(rightFarReading<200){
    motorA.run(FORWARD);
    motorB.run(FORWARD);
    motorA.setSpeed(vSpeed);
    motorB.setSpeed(vSpeed);
    delay(leapTime);
    readSensors();
    
    if(leftFarReading>200 && leftCenterReading>200 &&
      rightCenterReading>200 && rightFarReading>200){
      turnRight();
      return;
    }

    if(leftFarReading>200 && rightFarReading>200 && 
   (leftCenterReading<200 || rightCenterReading<200) ){ 
      straight();
    }  
    
    path[pathLength]='S';
   // Serial.println("s");
    pathLength++;
    //Serial.print("Path length: ");
    //Serial.println(pathLength);
    if(path[pathLength-2]=='B'){
    //Serial.println("shortening path");
    shortPath();
     }
  }
  delay(leapTime);
  readSensors();
  if(leftFarReading>200 && leftCenterReading>200 && rightCenterReading>200 
    && rightFarReading>200 && leftNearReading>200 && rightNearReading>200){
    turnAround();
  }

}
void done(){
  motorA.setSpeed(0);
  motorB.setSpeed(0);
  replaystage=1;
  path[pathLength]='D';
  pathLength++;
  delay(500);
  replay();
}

void turnLeft(){
       
//  while(analogRead(rightCenterSensor)>200||analogRead(leftCenterSensor)>200){
//    Serial.println("Turning Left");
//    motorA.run(BACKWARD);
//    motorB.run(FORWARD);
//    motorA.setSpeed(vSpeed);
//    motorB.setSpeed(turn_speed);
//    delay(2);
//    motorA.setSpeed(0);
//    motorB.setSpeed(0);
//    delay(1);
//  }
    
  while(analogRead(leftNearSensor)>200){
    Serial.println("Turning Left");
    motorA.run(BACKWARD);
    motorB.run(FORWARD);
    motorA.setSpeed(vSpeed);
    motorB.setSpeed(turn_speed);
    delay(2);
    motorA.setSpeed(0);
    motorB.setSpeed(0);
    delay(1);
  }
 
  if(replaystage==0){
    path[pathLength]='L';
    //Serial.println("l");
    pathLength++;
    //Serial.print("Path length: ");
    //Serial.println(pathLength);
      if(path[pathLength-2]=='B'){
        //Serial.println("shortening path");
        shortPath();
      }
  }
}

void turnRight(){

    
  while(analogRead(rightCenterSensor)>200||analogRead(leftCenterSensor)>200){
    Serial.println("Turning Right");
    motorA.run(FORWARD);
    motorB.run(BACKWARD);
    motorA.setSpeed(turn_speed);
    motorB.setSpeed(vSpeed);
    delay(2);
    motorA.setSpeed(0);
    motorB.setSpeed(0);
    delay(1);
  }
  
  if(replaystage==0){
  path[pathLength]='R';
  Serial.println("r");
  pathLength++;
  Serial.print("Path length: ");
  Serial.println(pathLength);
    if(path[pathLength-2]=='B'){
      Serial.println("shortening path");
      shortPath();
    }
  }
 
}

void straight(){
  if( analogRead(leftCenterSensor)<200){
    Serial.println("Going Forward");
    motorA.run(FORWARD);
    motorB.run(FORWARD);
    motorA.setSpeed(vSpeed);
    motorB.setSpeed(vSpeed);
    delay(1);
    motorA.run(FORWARD);
    motorA.setSpeed(vSpeed);
    motorB.setSpeed(vSpeed+50);
    delay(5);
    return;
  }
  if(analogRead(rightCenterSensor)<200){
    Serial.println("Going Forward");
    motorA.run(FORWARD);
    motorB.run(FORWARD);
    motorA.setSpeed(vSpeed);
    motorB.setSpeed(vSpeed);
    delay(1);
    motorB.run(FORWARD);
    motorA.setSpeed(vSpeed+50);
    motorB.setSpeed(vSpeed);
    delay(5);
    return;
  }
  
    Serial.println("Going Forward");
    motorA.run(FORWARD);
    motorB.run(FORWARD);
    motorA.setSpeed(vSpeed);
    motorB.setSpeed(vSpeed);
    delay(4);
    motorA.setSpeed(0);
    motorB.setSpeed(0);
    delay(1);
  
}

void turnAround(){
    motorA.run(FORWARD);
    motorB.run(FORWARD);
    motorA.setSpeed(vSpeed);
    motorB.setSpeed(vSpeed);
    delay(150);
    while(analogRead(leftCenterSensor)>200){
    motorA.run(BACKWARD);
    motorB.run(FORWARD);
    motorA.setSpeed(vSpeed);
    motorB.setSpeed(turn_speed);
    delay(2);
    motorA.setSpeed(0);
    motorB.setSpeed(0);
    delay(1);
  }
  path[pathLength]='B';
  pathLength++;
  straight();
  //Serial.println("b");
  //Serial.print("Path length: ");
  //Serial.println(pathLength);
}

void shortPath(){
 int shortDone=0;
  if(path[pathLength-3]=='L' && path[pathLength-1]=='R'){
    pathLength-=3;
    path[pathLength]='B';
    //Serial.println("test1");
    shortDone=1;
  }
   
  if(path[pathLength-3]=='L' && path[pathLength-1]=='S' && shortDone==0){
    pathLength-=3;
    path[pathLength]='R';
    //Serial.println("test2");
    shortDone=1;
  }
   
  if(path[pathLength-3]=='R' && path[pathLength-1]=='L' && shortDone==0){
    pathLength-=3;
    path[pathLength]='B';
    //Serial.println("test3");
    shortDone=1;
  }
  
   
  if(path[pathLength-3]=='S' && path[pathLength-1]=='L' && shortDone==0){
    pathLength-=3;
    path[pathLength]='R';
    //Serial.println("test4");
    shortDone=1;
  }
     
  if(path[pathLength-3]=='S' && path[pathLength-1]=='S' && shortDone==0){
    pathLength-=3;
    path[pathLength]='B';
    //Serial.println("test5");
    shortDone=1;
  }
    if(path[pathLength-3]=='L' && path[pathLength-1]=='L' && shortDone==0){
    pathLength-=3;
    path[pathLength]='S';
    //Serial.println("test6");
    shortDone=1;
  }
  
  path[pathLength+1]='D';
  path[pathLength+2]='D';
  pathLength++;
  //Serial.print("Path length: ");
  //Serial.println(pathLength);
  //printPath();
}




void printPath(){
  Serial.println("+++++++++++++++++");
  int x;
  while(x<=pathLength){
  Serial.println(path[x]);
  x++;
  }
  Serial.println("+++++++++++++++++");
}


void replay(){
   readSensors();
  if(leftFarReading<200 && rightFarReading<200){
    straight();
  }
  else{
    if(path[readLength]=='D'){
    motorA.run(FORWARD);
    motorB.run(FORWARD);
    motorA.setSpeed(vSpeed);
    motorB.setSpeed(vSpeed);
    delay(100);
    motorA.setSpeed(0);
    motorB.setSpeed(0);
    endMotion();
    }
    if(path[readLength]=='L'){
    motorA.run(FORWARD);
    motorB.run(FORWARD);
    motorA.setSpeed(vSpeed);
    motorB.setSpeed(vSpeed);
    delay(leapTime);
      turnLeft();
    }
    if(path[readLength]=='R'){
    motorA.run(FORWARD);
    motorB.run(FORWARD);
    motorA.setSpeed(vSpeed);
    motorB.setSpeed(vSpeed);
    delay(leapTime);
    turnRight();
    }
    if(path[readLength]=='S'){
    motorA.run(FORWARD);
    motorB.run(FORWARD);
    motorA.setSpeed(vSpeed);
    motorB.setSpeed(vSpeed);
    delay(leapTime);
    straight();
    }
    
    readLength++;
  }
    
  replay();
  
}

void endMotion(){
  Serial.println("~~~~~~~~~~~~THE END~~~~~~~~~~~~");
}
