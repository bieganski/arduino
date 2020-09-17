const int potPin = 14;
const int enablePin = 12;
int potValue = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);

  digitalWrite(enablePin, HIGH);
}

void loop() {
  // Reading potentiometer value
  potValue = analogRead(potPin);
  Serial.println(potValue);
  delay(500);
}
