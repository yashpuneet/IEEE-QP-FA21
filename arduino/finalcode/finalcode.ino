#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>

#define DATA_PIN 3
#define SENSOR_RESOLUTION 9
#define SENSOR_INDEX 0

int led = 13;
int fan = 12;
int ldrPin = A0;
int pump = 11;

int initialBright = 25;
int ldrInput;

int trigPin = 9;
int echoPin = 6;
int duration;
int distance;

OneWire oneWire(DATA_PIN);
DallasTemperature sensors(&oneWire);
DeviceAddress sensorDeviceAddress;

LiquidCrystal_I2C lcd(0x27,20,4);

void setup() 
{
  Serial.begin(115200);
  sensors.begin();
  sensors.getAddress(sensorDeviceAddress, 0);
  sensors.setResolution(sensorDeviceAddress, SENSOR_RESOLUTION);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(ldrPin, INPUT);
  pinMode(fan,OUTPUT);
  pinMode(pump, OUTPUT);

  lcd.init(); 
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("8");
}

void loop() 
{
  temp_check();
  light_check();
  dist_check();
  //delay(1000);
}

void temp_check()
{
  sensors.requestTemperatures();
  float temperatureInCelsius = sensors.getTempCByIndex(SENSOR_INDEX);
  float temperatureInFahrenheit = sensors.getTempFByIndex(SENSOR_INDEX);

  lcd.clear();

  lcd.print("Temperature:");

  lcd.setCursor(0,1);
  lcd.print(temperatureInCelsius);
  //Serial.println(temperatureInCelsius);
  lcd.setCursor(5,1);
  lcd.print((char)223);
  lcd.setCursor(6,1);
  lcd.print("C,");

  lcd.setCursor(9,1);
  lcd.print(temperatureInFahrenheit);
  //Serial.println(temperatureInFahrenheit);
  lcd.setCursor(14,1);
  lcd.print((char)223);
  lcd.setCursor(15,1);
  lcd.print("F");

  if(temperatureInCelsius > 28)
  {
    FanOn();
  }
  else
  {
    FanOff();
  }
}

void turnOnLight(){
  analogWrite(led, initialBright); 
  //delay(50);
  if(ldrInput > 100){
    analogWrite(led, 0);
  }
  //else if(ldrInput > 40 && ldrInput <= 70){
  //  analogWrite(led, 100); 
  //}
  else if(ldrInput <= 100){
    analogWrite(led, 255);
    FanOn();
  }
}

void turnOffLight(){
  analogWrite(led, 0);
  FanOff();
}

void light_check()
{
  ldrInput = analogRead(ldrPin);
  Serial.println(ldrInput);
  turnOnLight();
}

void dist_check()
{
    digitalWrite(trigPin, LOW);
    delay(10);
    digitalWrite(trigPin, HIGH);
    delay(50);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration/2) / 29.1;
    Serial.println(distance);
}

void FanOff(){
      digitalWrite(fan, HIGH);
}

void FanOn(){
      digitalWrite(fan, LOW);
}

void dispense_water()
{
  digitalWrite(pump, HIGH);
  delay(5000);
  digitalWrite(pump, LOW);
}
