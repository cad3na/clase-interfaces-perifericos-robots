int motor_pin = 10;
float freq = 1000;
float T = 1000000/freq;
float dc = 0.3;
float t_on = T*dc;
float t_off = T*(1-dc);

void setup()
{
  pinMode(motor_pin, OUTPUT);
}

void loop()
{
  digitalWrite(motor_pin, HIGH);
  delayMicroseconds(t_on);
  digitalWrite(motor_pin, LOW);
  delayMicroseconds(t_off);
}
