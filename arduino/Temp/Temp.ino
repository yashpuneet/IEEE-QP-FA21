#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>

// Sensor input pin
#define DATA_PIN 3
// How many bits to use for temperature values: 9, 10, 11 or 12
#define SENSOR_RESOLUTION 9
// Index of sensors connected to data pin, default: 0
#define SENSOR_INDEX 0

OneWire oneWire(DATA_PIN);
DallasTemperature sensors(&oneWire);
DeviceAddress sensorDeviceAddress;

LiquidCrystal_I2C lcd(0x27,20,4);

void setup() {
  Serial.begin(9600);
  sensors.begin();
  sensors.getAddress(sensorDeviceAddress, 0);
  sensors.setResolution(sensorDeviceAddress, SENSOR_RESOLUTION);

  lcd.init(); 
  lcd.backlight();
  lcd.setCursor(0,0);
  //lcd.print("Hello, world!");
}


void loop() {
  sensors.requestTemperatures();
  float temperatureInCelsius = sensors.getTempCByIndex(SENSOR_INDEX);
  float temperatureInFahrenheit = sensors.getTempFByIndex(SENSOR_INDEX);

  lcd.clear();

  lcd.print("Temperature:");

  lcd.setCursor(0,1);
  lcd.print(temperatureInCelsius);
  lcd.setCursor(5,1);
  lcd.print((char)223);
  lcd.setCursor(6,1);
  lcd.print("C,");

  lcd.setCursor(9,1);
  lcd.print(temperatureInFahrenheit);
  lcd.setCursor(14,1);
  lcd.print((char)223);
  lcd.setCursor(15,1);
  lcd.print("F");
  
  delay(1000);
}
