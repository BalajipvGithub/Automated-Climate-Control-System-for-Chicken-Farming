#include <DHT.h>   // Include DHT library

#define DHTPIN 2       // Pin connected to the DHT sensor
#define DHTTYPE DHT11  // DHT11 or DHT22
DHT dht(DHTPIN, DHTTYPE);

#define FAN_PIN 3      // Pin for fan control
#define HEATER_PIN 4   // Pin for heater or light control

// Temperature thresholds (adjust based on your needs)
const float TEMP_HIGH = 30.0;  // Temperature in °C to turn the fan on
const float TEMP_LOW = 18.0;   // Temperature in °C to turn the heater on

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(FAN_PIN, OUTPUT);
  pinMode(HEATER_PIN, OUTPUT);
}

void loop() {
  float temperature = dht.readTemperature();  // Get temperature in Celsius
  
  if (isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C");

  // Control fan and heater based on temperature
  if (temperature >= TEMP_HIGH) {
    digitalWrite(FAN_PIN, HIGH);     // Turn on fan
    digitalWrite(HEATER_PIN, LOW);   // Turn off heater
    Serial.println("Fan ON, Heater OFF");
  } 
  else if (temperature <= TEMP_LOW) {
    digitalWrite(FAN_PIN, LOW);      // Turn off fan
    digitalWrite(HEATER_PIN, HIGH);  // Turn on heater
    Serial.println("Fan OFF, Heater ON");
  } 
  else {
    digitalWrite(FAN_PIN, LOW);      // Turn off fan
    digitalWrite(HEATER_PIN, LOW);   // Turn off heater
    Serial.println("Fan OFF, Heater OFF");
  }

  delay(2000);  // Wait for 2 seconds before reading again
}
