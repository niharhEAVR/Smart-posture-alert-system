#define MOTOR1 25
#define MOTOR2 26

void setup() {
  pinMode(MOTOR1, OUTPUT);
  pinMode(MOTOR2, OUTPUT);
}

void loop() {

  digitalWrite(MOTOR1, HIGH);
  delay(500);
  digitalWrite(MOTOR1, LOW);

  delay(500);

  digitalWrite(MOTOR2, HIGH);
  delay(500);
  digitalWrite(MOTOR2, LOW);

  delay(500);
}