#include <AFMotor.h>

AF_DCMotor motor(3);
const int puerto_entrada = A0;
const int referencia = 512;
const int kp = 10;
const int ki = 1;
const int kd = 2;
int entrada;
double error;
double error_anterior;
double ep;
double historial = 0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
motor.setSpeed(0);
motor.run(RELEASE);

}

void loop() {
  // put your main code here, to run repeatedly:
entrada= analogRead(A0);
error_anterior = error;
ep = (error-error_anterior)/0.002;
error = (referencia-entrada);
historial += error*0.002;
if(error < 0){
  motor.run(FORWARD);
  motor.setSpeed(kp*error+kd*ep+ki*historial);
}
else{
  motor.run(BACKWARD);
  motor.setSpeed(kp*error+kd*ep+ki*historial);
}
  
Serial.print(error);
Serial.print("\n");
delay(2);
}
