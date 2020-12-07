#include <Wire.h>

int lukaval = 1;
double xval = 0;
double yval = 0;
double zval = 0;


void setup() {


  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
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
  }
  if (lukaval == 2) {
    String lukastring = String(Wire.read());
    lukastring += ".";
    lukastring += Wire.read();
    yval = lukastring.toDouble();
    lukaval = 3;

  }
  if (lukaval == 3) {
    String lukastring = String(Wire.read());
    lukastring += ".";
    lukastring += Wire.read();
    zval = lukastring.toDouble();
    lukaval = 1;

  }
}
