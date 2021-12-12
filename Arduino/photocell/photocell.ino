int photocellPin = 0;
int photocellReading;
int LEDpin = 11;
int LEDbrightness;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  //Serial.print("Analog read = ");
  //Serial.println(photocellReading);
  photocellReading = analogRead(photocellPin);
  photocellReading = 1023 - photocellReading;
  
  LEDbrightness = map(photocellReading, 0, 1023,0,255);
  analogWrite(LEDpin,LEDbrightness);

  if(Serial.available()>0){
    String data = Serial.readStringUntil('\n');
    Serial.println("arduino y thcin");
    Serial.println(photocellReading);  
  }
  
  delay(100);
}
