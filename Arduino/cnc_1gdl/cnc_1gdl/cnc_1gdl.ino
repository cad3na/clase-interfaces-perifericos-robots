
#include <AccelStepper.h>
#include <AFMotor.h>

// two stepper motors one on each port
AF_Stepper motor(200, 1);
String comando = "";
boolean stringComplete = false;
boolean reposo = true;
String primer = "G";
String segundo0 = "0";
int maxvel = 200;

// you can change these to DOUBLE or INTERLEAVE or MICROSTEP!
// wrappers for the first motor!
void forwardstep() {  
  motor.onestep(FORWARD, SINGLE);
}
void backwardstep() {  
  motor.onestep(BACKWARD, SINGLE);
}

// Motor shield has two motor ports, now we'll wrap them in an AccelStepper object
AccelStepper stepper(forwardstep, backwardstep);

void setup()
{
    Serial.begin(9600);
    stepper.setMaxSpeed(200.0);
    stepper.setAcceleration(1000.0);
    stepper.moveTo(100);
    
}

void loop()
{
	    //stepper.moveTo(-stepper.currentPosition());
    if(stepper.distanceToGo()==0 && reposo == false){
      Serial.println("ok");
      reposo = true;
      }
    stepper.run();
    
    if (stringComplete) {
    Serial.println(comando);
    if(comando[0] == primer[0]){
      reposo = false;
      if(comando[1] == segundo0[0]){
        stepper.setMaxSpeed(maxvel);
        stepper.moveTo(comando.substring(3,6).toInt());
        }
      else{
        stepper.setMaxSpeed(comando.substring(7,10).toInt());
        stepper.moveTo(comando.substring(3,6).toInt());
        }
    }
    else{Serial.println("Datos erroneos");}
    // clear the string:
    comando = "";
    stringComplete = false;
  }
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    comando += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
