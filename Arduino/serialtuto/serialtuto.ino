const byte numChars = 64;
char receivedChars[numChars];

boolean newData = false;

byte ledPin = 13;


void setup() {
  Serial.begin(9600);

  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin, HIGH);
  delay(200);
  digitalWrite(ledPin, LOW);
  delay(200);
  digitalWrite(ledPin, HIGH);

  Serial.println("<Arduino is ready>");
  

}

void loop() {
  recvWithStartEndMarkers();
  replyToPython();
  
}


void recvWithStartEndMarkers(){
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;

  while (Serial.available() > 0 && newData == false){
    rc = Serial.read();

    if(recvInProgress == true){
      if(rc != endMarker){
        receivedChars[ndx] = rc;
        ndx ++;
        if(ndx >= numChars){
          ndx = numChars - 1;
          
        }
      }

      else {
        receivedChars[ndx] = '\0'; // terminate the string
        recvInProgress = false;
        ndx = 0;
        newData = true;
      }
    }

    else if( rc == startMarker){
      recvInProgress = true;
    }
    
  }
}

void replyToPython(){
if(newData == true){
  Serial.print("<This just in...");
  Serial.print(receivedChars);
  Serial.print("  ");
  Serial.print(millis());
  Serial.print('>');
    // change the state of the LED everytime a replys is sent
  digitalWrite(ledPin, ! digitalRead(ledPin));
  newData = false;
}
}
