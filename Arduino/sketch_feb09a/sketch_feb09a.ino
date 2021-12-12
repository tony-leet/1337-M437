// Librairies
#include <DHT.h>

// Constants
#define DHTPIN 7 // what pin we are connected to
#define DHTTYPE DHT22 // what sensor we use DHT22 (AM2302)
DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor for nomal 16mhz Arduinos

// Variables
int chk;
float humidity;
float temperature;

void setup() {
  Serial.begin(9600);
  dht.begin();

}

void loop() {
  delay(5000);
  
  // Read data and store it to variables humidity and temperature
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  // Print temp and humidity values to serial monitor
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %, Temperature: ");
  Serial.print(temperature);
  Serial.print("Celsius");
  delay(10000); //Delay 2sec
}
