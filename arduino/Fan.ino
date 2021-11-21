int temp=A0;
int fan=2;
//int trigPin=4;
//int echoPin=5;
long duration;
int distance;
void FanOn(){
      digitalWrite(fan, HIGH);
}

void FanOff(){
      digitalWrite(fan, LOW);
}
void setup() {
  pinMode(fan,OUTPUT);
  pinMode(temp,INPUT);
  //pinMode(trigPin,OUTPUT);
  //pinMode(echoPin,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int reading = analogRead(A0);
  float voltage  = reading*5.0;
  voltage/=1024.0;
  float TempC=(voltage-0.5)*100;
  Serial.println(TempC);Serial.println("Celsius");
  if(TempC>=20){
    FanOn();
  }
  else{
    FanOff();
  }

//  digitalWrite(trigPin, LOW);
//  delayMicroseconds(2);
//  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(trigPin, LOW);
//  duration = pulseIn(echoPin, HIGH);
//  distance = duration * 0.034 / 2;
//  Serial.println(distance);Serial.println("cm");
//  if(distance<=20)
//  {
//    Serial.println("too close to computer");
//  }

  delay(3000);
}
