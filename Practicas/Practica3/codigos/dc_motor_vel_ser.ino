int motor_pin = 10;
float freq = 1000;
float T = 1000000/freq;
float dc = 0.5;
float t_on = T*dc;
float t_off = T*(1-dc);
String cad_frec = "";
void setup()
{
  Serial.begin(9600);
  pinMode(motor_pin, OUTPUT);
}
void loop()
{
  if(Serial.available() > 0){
    cad_frec = Serial.readString();
    modificar_tiempos(cad_frec.toFloat());}
  digitalWrite(motor_pin, HIGH);
  delayMicroseconds(t_on);
  digitalWrite(motor_pin, LOW);
  delayMicroseconds(t_off);
}
void modificar_tiempos(float frecuencia)
{
  freq = frecuencia;
  T = 1000000/freq;
  t_on = T*dc;
  t_off = T*(1-dc);
}
