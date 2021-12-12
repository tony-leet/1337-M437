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
  #if(Serial.available()> 0 && newData == false)
  recvWithStartEndMarkers();
  replyToPython();
}

void checkDHT(){
   // Read data and store it to variables humidity and temperature
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  lastHum = humidity;
  lastTemp = temperature;
}

void recvWithStartEndMarkers(){
  static boolean recvInProgress = false;
  static byte ndx = 0; // index
  char startMarker = '<';
  char endMarker = '>';
  char rc;


  
  // loop trough all byte of the serial message to find the endMarker
  while (Serial.available()> 0 && newData == false){
    rc = Serial.read();
    
    if(recvInProgress == true){
      if(rc != endMarker){
        receivedChars[ndx] = rc;
        ndx++;
        if(ndx>= numChars){
          ndx = numChars -1;
        }
      }

      // when you get to the endMarker
      else{
        commandString = '\0';
        commandString = receivedChars;
        receivedChars[ndx] = '\0'; // terminate the string
        recvInProgress = false;
        ndx = 0;
        newData = true;
        
      }
    }

    // startMarker, new string beuber!!!
    else if( rc == startMarker){
      recvInProgress = true;
    }  
  }  
}

void replyToPython(){
  if (newData){
    ledBlink();
    delay(200);
    if(commandString == "This is test"){
      Serial.println("<");
      Serial.println("caca");
      Serial.println(commandString);
      Serial.println(">");
    }
    else if(commandString == "Mange dla Marde"){
      Serial.println("<");
      Serial.println("avec de la moutarde");
      Serial.println(commandString);
      Serial.println(">");
    }
    else{
      Serial.println("<");
      Serial.println("fuck all");
      Serial.println(commandString);
      Serial.println(">");
    }
    newData = false;
    //if(strcmp(commandString,"This is test") ==0){
    //  Serial.println("<cmd received master>");
    //}
    //else if(strcmp(commandString, "Tchin le")==0){
    //  Serial.println("<Ca tchin>");
    }
    //Serial.println("<");
    //Serial.println(lastHum);
    //Serial.println(lastTemp);
    //Serial.println(">");
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
