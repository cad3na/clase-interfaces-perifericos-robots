const int pin_servo = 13;
float pos = 90;
float t_on = 0;
float t_off = 0;

void setup() {
  Serial.begin(9600);
  pinMode(pin_servo, OUTPUT);
}

void loop() {
  recibir_datos();
  mandar_senal_servo();
}

void recibir_datos(){
  if (Serial.available()) {
    pos = Serial.readString().toFloat();
    definir_senal_servo();
  }
}

void definir_senal_servo(){
  t_on = pos/150.0 + 0.9;
  t_off = 3 - t_on;
}

void mandar_senal_servo(){
  digitalWrite(pin_servo, HIGH);
  delayMicroseconds(t_on*1000);
  digitalWrite(pin_servo, LOW);
  delayMicroseconds(t_off*1000);
  delay(17);
}
