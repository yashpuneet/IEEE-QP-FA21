/* 
 *  This portion of code is used for the ultrasonic sensor and the light dependent resistor.
 *  The ultrasonic sensor will pick up the distance between the sensor and the person. If the distance is 
 *  an appropriate amount, then the ldr will activate and dim the lights depending on the amount of light
 *  around the ldr.
 */
 
//Need to test values if they are accurate (distance)
//If possible use motion sensor to trigger ultrasonic sensor
int led = 13;
int ldrPin = A0;
int initialBright = 25;
int ldrInput;

int trigPin = 3;
int echoPin = 2;
int duration;
int distance;
int average;
void turnOnLight(){
  analogWrite(led, initialBright); 
  if(ldrInput > 100){
    analogWrite(led, 0);
  }
  else if(ldrInput > 40 && ldrInput <= 70){
    analogWrite(led, 100); 
  }
  else if(ldrInput <= 15){
    analogWrite(led, 255);
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
    delay(10);
    digitalWrite(trigPin, HIGH);
    delay(50);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration/2) / 29.1;
    
    Serial.println(distance);
  if(distance >= 60 && distance <= 80){
    turnOnLight();
  }
  else{
    turnOffLight();
  }
  delay(100);
}
