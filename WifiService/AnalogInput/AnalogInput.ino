#include <SoftwareSerial.h>

int sensorPin = A0;    // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor

SoftwareSerial mySerial(1, 0); // RX, TX

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);

  mySerial.begin(115200);
}

void loop() {

  sensorValue = analogRead(sensorPin);
  mySerial.println(sensorValue);
  
  delay(1000);
  digitalWrite(ledPin, HIGH);

  delay(1000);
  digitalWrite(ledPin, LOW);
}
