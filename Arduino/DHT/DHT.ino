// Librairies
#include <DHT.h>

// Constants

  // DHT
#define DHTPIN 7 // what pin we are connected to
#define DHTTYPE DHT22 // what sensor we use DHT22 (AM2302)
DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor for nomal 16mhz Arduinos

  // Serial Communication
#define ledPin 13
#define numChars 64


// Variables
  // DHT
int chk;
float humidity;
float temperature;
float lastHum; // to send in the serial communication
float lastTemp; // to send in the serial communication

  // Serial Communication
char receivedChars[numChars];
boolean newData = false;
String commandString;


void setup() {
  Serial.begin(9600);
  Serial.println("<Arduino is ready>");
  dht.begin();
}

void loop() {
  delay(2000);
  checkDHT();
  if(Serial.available()> 0 && newData == false)
  {
    //recvWithStartEndMarkers();
    recvMessage();
  }
  if(newData)
  {
    replyToPython();
  }
}

void checkDHT(){
   // Read data and store it to variables humidity and temperature
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  lastHum = humidity;
  lastTemp = temperature;
}

void recvMessage(){
  commandString = Serial.readStringUntil('$');
  newData = true;
}


void replyToPython(){
    ledBlink();
    delay(200);
    if(commandString == "<Monitor>"){
      Serial.println("<");
      Serial.println(lastHum);
      Serial.println(lastTemp);
      Serial.println(";");
      Serial.println(2);
      Serial.println(22);
      Serial.println(";");
      Serial.println(3);
      Serial.println(33);
      Serial.println(";");
      Serial.println(4);
      Serial.println(44);
      Serial.println(";");
      Serial.println(5);
      Serial.println(55);
      Serial.println(">");
    }

    else{
      Serial.println("<");
      Serial.println("ERROR!");
      Serial.println("arduino received: " + commandString);
      Serial.println(">");
    }
    newData = false;

}


void ledBlink(){
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin, HIGH);
  delay(200);
  digitalWrite(ledPin, LOW);
  delay(200);
  digitalWrite(ledPin, HIGH);
  delay(200);
  digitalWrite(ledPin, LOW);
}
