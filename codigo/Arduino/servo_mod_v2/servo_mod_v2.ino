#include <AFMotor.h>
#include <PID_v1.h>

AF_DCMotor motor(3);
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
double Kp=10, Ki=1, Kd=4;
PID controladorPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup() {
  Serial.begin(115200);
  // turn on motor
  motor.setSpeed(0);
  motor.run(RELEASE);
  Setpoint = 500;
  Input = 0;
  controladorPID.SetMode(AUTOMATIC);
  controladorPID.SetOutputLimits(-255,255);
  controladorPID.SetSampleTime(2);
}

void loop() {
  //if(Serial.available()>0){Setpoint = Serial.readString().toInt();}
  
  Input = analogRead(analogInPin);
  controladorPID.Compute();
  
  if(Output>=0){
    motor.run(BACKWARD);
    motor.setSpeed(Output);}
  else{
    motor.run(FORWARD);
    motor.setSpeed(-Output);}

  // print the results to the serial monitor:
  //Serial.print("sensor = ");
  Serial.print(Input);
  Serial.print("\t");
  Serial.print(Output-255);
  Serial.print("\t");
  Serial.println(500 - Input);
  Serial.print("\n");

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(1);
}
