#include <Wire.h>
#define SLAVE_ADDR 4
#define ANSWERSIZE 4

int lukaval = 1;
double xval = 0;
double yval = 0;
double zval = 0;
short numberofrequest = 0;


void setup() {
  Wire.begin(SLAVE_ADDR);                // join i2c bus with address #4
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent); // register event

  digitalWrite(9, HIGH);    // turn the LED off by making the voltage LOW
  delay(500);
  digitalWrite(9, LOW);
}


void loop() {

}
void receiveEvent(int howmany) {
  while (Wire.available()) {
    if (lukaval == 1) {
      String lukastring = String(Wire.read());
      lukastring += ".";
      lukastring += Wire.read();
      xval = lukastring.toDouble();
      lukaval = 2;
      digitalWrite(9, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(500);                       // wait for a second

    }
    else {
      String lukastring = String(Wire.read());
      lukastring += ".";
      lukastring += Wire.read();
      yval = lukastring.toDouble();
      lukaval = 1;
      digitalWrite(9, HIGH);
      delay(500);
    }
    
    digitalWrite(9, LOW);
  }








}

void requestEvent(int howmany) {
  //Alexanders code below...
  numberofrequest++;



  Wire.write("L");

}
