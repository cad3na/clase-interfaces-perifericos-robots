const int pot_pin = A0;
const int m1 = 10;
const int m2 = 11;

float kp = 1;
float sensor = 0;
float pos_des = 100;
float error = 0;
int senal = 0;

void setup(){
  Serial.begin(9600);
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
}

void loop(){
  recibir_datos();
  sensor = analogRead(pot_pin);
  Serial.println(sensor);
  calcular_error();
  calcular_senal();
  if(senal < 0) reversa();
  else avance();
  delay(2);
}

void recibir_datos(){
  if(Serial.available() > 0){
    pos_des = Serial.readString().toFloat();
  }
}

void calcular_error(){
  error = pos_des - sensor;
}

void calcular_senal(){
  senal = int(max(min(kp*error, 255), -255));
}

void reversa(){
  analogWrite(m1, 0);
  analogWrite(m2, abs(senal));
}

void avance(){
  analogWrite(m2, 0);
  analogWrite(m1, senal);
}
