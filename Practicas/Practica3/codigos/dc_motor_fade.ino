int motor_pin = 10;
int motor_vel = 0;
int motor_accel = 5;

void setup() {
  pinMode(motor_pin, OUTPUT);
}

void loop() {
  analogWrite(motor_pin, motor_vel);
  motor_vel = motor_vel + motor_accel;

  if (motor_vel <= 0 || motor_vel >= 255) {
    motor_accel = -motor_accel;
  }
  delay(30);
}
