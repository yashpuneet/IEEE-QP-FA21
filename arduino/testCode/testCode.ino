int ledWPin = 2;
int ledRPin = 3;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(1);
  pinMode(ledWPin, OUTPUT);
  pinMode(ledRPin, OUTPUT);
}

void loop() {
  digitalWrite(ledWPin, HIGH);
  digitalWrite(ledRPin, LOW);
  delay(1000);
  digitalWrite(ledRPin, HIGH);
  digitalWrite(ledWPin, LOW);
  delay(1000);
  Serial.print(1);
}
