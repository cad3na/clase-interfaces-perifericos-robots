const int pin_servo = 13;
float pos = 0;
float t_on = 0;
float t_off = 0;
float frec = 1;
float omega = TWO_PI*frec;
float t = 0;

void setup() {
  Serial.begin(9600);
  pinMode(pin_servo, OUTPUT);
}
void loop() {
  recibir_datos();
  trayectoria();
  definir_senal_servo();
  mandar_senal_servo();
}
void recibir_datos(){
  if (Serial.available()) {
    frec = Serial.readString().toFloat();
    Serial.println(frec);
    definir_frecuencia();
  }
}


void definir_senal_servo(){
  t_on = pos/150 + 0.9;
  t_off = 20 - t_on;
}


void mandar_senal_servo(){
  digitalWrite(pin_servo, HIGH);
  delayMicroseconds(t_on*1000);
  digitalWrite(pin_servo, LOW);
  delayMicroseconds(t_off*1000);
  delay(17);
}


void definir_frecuencia(){
  omega = TWO_PI*frec;
}


void trayectoria(){
  t = millis()/1000.0;
  pos = (sin(omega*t) + 1)*90;
}
