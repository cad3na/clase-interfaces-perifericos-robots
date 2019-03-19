const int pot_pin = A0;
const int m1 = 10;
const int m2 = 11;
int kp = 10;
int sensor = 0;
int pos_des = 100;
int error = 0;
int senal = 0;

void setup(){
  Serial.begin(9600);
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
}

void loop(){
  sensor = analogRead(pot_pin);
  Serial.println(sensor);
  calcular_error();
  calcular_senal();
  if(error < 0) reversa();
  else avance();
  delay(2);
}


void calcular_error(){
  error = pos_des - sensor;
}


void calcular_senal(){
  senal = kp*error;
}


void reversa(){
  digitalWrite(m1, 0);
  digitalWrite(m2, senal);
}


void avance(){
  digitalWrite(m2, 0);
  digitalWrite(m1, senal);
}
