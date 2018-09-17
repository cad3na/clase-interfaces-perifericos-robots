#include <AFMotor.h>

AF_DCMotor motor(3);
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to

//float kp = 10;
//float kd = 2;
float kp=0; float kd=0;
float deseado = 300;
float sensor = 0;
float sensor_ant = 0;
float error = 0;
float error_vel= 0;
float salida = 0;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(115200);
  // turn on motor
  motor.setSpeed(0);
  motor.run(RELEASE);
}

void loop() {
  // read the analog in value:
  sensor_ant = sensor;
  sensor = analogRead(analogInPin);
  error = deseado - sensor;
  error_vel = (sensor_ant - sensor)/0.2;
  // map it to the range of the analog out:
  salida = map(kp*error + kd*error_vel, 0, 1023, 0, 255);
  // change the analog out value:
  if(salida>0){
    motor.run(BACKWARD);
    motor.setSpeed(salida); 
  }
  else{
    motor.run(FORWARD);
    motor.setSpeed(-salida); 
  }

  // print the results to the serial monitor:
  Serial.print("sensor = ");
  Serial.print(sensor);
  Serial.print("\t control = ");
  Serial.print(salida);
  Serial.print("\t error = ");
  Serial.println(error);

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(2);
}
