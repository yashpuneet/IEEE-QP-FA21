//Need to fill out all the pins according to circuit
//Need to test values if they are accurate (LDR and distance)
//If possible use motion sensor to trigger ultrasonic sensor
int led =;
int ldrPin = ;
int initialBright = 50;
int ldrInput;

int trigPin =;
int echoPin =;
int duration;
int distance;

void turnOnLight(){
  analogWrite(led, initialBright); 
  delay(50);
  if(ldrInput > 800 && ldrInput <= 1000){
    analogWrite(led, 0);
  }
  else if(ldrInput > 600 && ldrInput <= 800){
    analogWrite(led, 25 );
  }
  else if(ldrInput > 200 && ldrInput <= 400){
    analogWrite(led, 100); 
  }
  else if(ldrInput <= 200){
    analogWrite(led, 150);
  }
}
void turnOffLight(){
  analogWrite(led, 0);
}
void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
   pinMode(trigPin, OUTPUT);
   pinMode(echoPin, INPUT);
   pinMode(led, OUTPUT);
   pinMode(ldrPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    ldrInput = analogRead(ldrPin);
    digitalWrite(trigPin, LOW);
    delay(1);
    digitalWrite(trigPin, HIGH);
    delay(10);
    digitalWrite(trigPin,LOW);
    duration = pulseIn(echoPing, HIGH);
    distance = (duration/2) / 29.1;
    
  if(distance >= 20 && distance <= 75){
    turnOnLight();
  }
  else{
    turnOffLight();
  }
}
