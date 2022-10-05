#include <AccelStepper.h>
#include <string>

#define home_switch_1 7;
#define home_switch_2 6;

AccelStepper motor1(200, 10, 11);
AccelStepper motor2(200, 8, 9);
  
void setup() {
  float targetTheta1;
  float targetTheta2;
  const float degsPerStep = 0.2f;
  long homing = 1;//step position used to home steppers. positive is CW.
  
  //first home motor 1. Arm must be manually aligned in "A" configuration
  //move stepper 1 CW until home switch activated
  while(digitalRead(home_switch_1){
    motor1.moveTo(homing);
    homing++;
    motor1.run();
    delay(5);
  }

  //set current position of motor1 as 180 deg
  motor1.setCurrentPosition(getStepsFromDeg(180f));
  motor1.setMaxSpeed(100.0);
  motor1.setAcceleration(100.0);

  //put motor1 in 90 deg position
  motor1.moveTo(getStepsFromDeg(90f));
  while (motor1.distanceToGo > 0){
    motor1.run();
    delay(5);
  }

  //set homing for CCW
  homing = -1;
  while(digitalRead(home_switch_2){
    motor2.moveTo(homing);
    homing--;
    motor2.run();
    delay(5);
  }

  //set current position of motor2 as 0.
  motor2.setCurrentPosition(0);
  motor2.setMaxSpeed(100.0);
  motor2.setAcceleration(100.0);

  //put motor2 in 90 deg position
  motor1.moveTo(getStepsFromDeg(90f));
  while (motor2.distanceToGo > 0){
    motor2.run();
    delay(5);
  }

  Serial.begin(115200);
  Serial.setTimeout(1);
  String cmd;
}


void loop(){
  
  //read 17 bytes at a time. Only read when there are more than 17 bytes 
  //available
  //left target position: double | right target position: double | EOL: char
  //EOL is discarded
  
  if (Serial.available() > 17) {
    //read string until EOL
    cmd = Serial.readStringUntil('\n');
    
    //slice cmd string into 2 halves
    String motor1Str = cmd.substr(0, 8);
    String motor2Str = cmd.substr(8, 16);
    
    //cast each half-string into double precision motor positions
    double motor1Double = std::stod(motor1Str);
    double motor2Double = std::stod(motor2Str);
    
    //set motor position
    motor1.moveTo(getStepsFromDeg(motor1Double));
    motor2.moveTo(getStepsFromDeg(motor2Double));
  }  

  //run motor
  motor1.run();
  motor2.run();
}

long getStepsFromDeg(double deg){
  const float degsPerStep = 0.2f;
  return (long)(deg/degsPerStep)
}
