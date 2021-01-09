#include <Wire.h>
#define SLAVE_ADDR 4
#define ANSWERSIZE 5

int lukaval = 1;
double xval = 0;
double yval = 0;
double zval = 0;
short numberofrequest = 0;


void setup() {
  Wire.begin(SLAVE_ADDR);                // join i2c bus with address #4
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent); // register event
  int numRows = 2;
  int numCols = 16;

}


void loop() {

}
void receiveEvent() {
  if (lukaval == 1) {
    String lukastring = String(Wire.read());
    lukastring += ".";
    lukastring += Wire.read();
    xval = lukastring.toDouble();
    lukaval = 2;
    digitalWrite(9, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100);                       // wait for a second
    
  }
  if (lukaval == 2) {
    String lukastring = String(Wire.read());
    lukastring += ".";
    lukastring += Wire.read();
    yval = lukastring.toDouble();
    lukaval = 1;

  }
  
    digitalWrite(9, LOW);    // turn the LED off by making the voltage LOW
    delay(100);
 









  
}

void requestEvent() {
  //Alexanders code below...
  numberofrequest++;
  

  Wire.write(byte(numberofrequest));

}
