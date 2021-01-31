#include <Wire.h>
#define SLAVE_ADDR 4
#define ANSWERSIZE 4

int lukaval = 1;
boolean doingcode = false;
double xval = 0;
double yval = 0;
double zval = 0;
short numberofrequest = 0;


void setup() {
  Wire.begin(SLAVE_ADDR);                // join i2c bus with address #4
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent); // register event
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  delay(500);
  digitalWrite(9, HIGH);    // turn the LED off by making the voltage LOW
  digitalWrite(8, HIGH);
  delay(500);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
}


void loop() {

}
void receiveEvent(int howmany) {
  while (Wire.available()) {
    if (lukaval == 1) {
      String lukastring = String(Wire.read());
      lukastring += ".";
      lukastring += String(Wire.read());
      xval = lukastring.toDouble();
      lukaval = 2;
      digitalWrite(8, HIGH);   // turn the LED on (HIGH is the voltage level)

    }
    else {
      String lukastring = String(Wire.read());
      lukastring += ".";
      lukastring += String(Wire.read());
      yval = lukastring.toDouble();
      lukaval = 1;
      digitalWrite(9, HIGH);
    }

    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
  }
}

void requestEvent(int howmany) {
  //Alexanders code below...
  delay(2000);  //testing 2 second delay
  if (doingcode == false) {
    Wire.write("A");
  }



}
