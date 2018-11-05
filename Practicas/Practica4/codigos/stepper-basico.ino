int subpaso = 0;
int pos = 0;
const int m1 = 10;
const int m2 = 11;
const int m3 = 12;
const int m4 = 13;

void setup() {
  Serial.begin(9600);
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);}

void loop() {
  if (Serial.available())
    if(Serial.readString() == "p\n")
      avanzar_paso();}

void avanzar_paso(){
  if (subpaso == 0){
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
    delay(10);}
  if (subpaso == 1){
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, HIGH);
    delay(10);}
  if (subpaso == 2){
    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, LOW);
    digitalWrite(m4, HIGH);
    delay(10);}
  if (subpaso == 3){
    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
    delay(10);}
  subpaso++;
  subpaso = subpaso%4;}
