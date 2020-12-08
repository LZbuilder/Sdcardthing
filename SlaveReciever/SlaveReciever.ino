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
    Wire.beginTransmission(4); // transmit to device #4

    Wire.write(1);  // sends one byte
    Wire.endTransmission();    // ends the transmission
  }
  if (lukaval == 2) {
    String lukastring = String(Wire.read());
    lukastring += ".";
    lukastring += Wire.read();
    yval = lukastring.toDouble();
    lukaval = 3;
    Wire.beginTransmission(4); // transmit to device #4

    Wire.write(1);  // sends one byte
    Wire.endTransmission();
  }
  if (lukaval == 3) {
    String lukastring = String(Wire.read());
    lukastring += ".";
    lukastring += Wire.read();
    zval = lukastring.toDouble();
    lukaval = 1;
    Wire.beginTransmission(4); // transmit to device #4

    Wire.write(1);  // sends one byte
    Wire.endTransmission();
  }

  lcd.setCursor(0, 0);
  lcd.print("Xval = ");
  lcd.setCursor(0, 1);
  lcd.print(xval);
  delay(500);
  lcd.setCursor(0, 0);
  lcd.print("Yval = ");
  lcd.setCursor(0, 1);
  lcd.print(yval);
  delay(500);
  lcd.setCursor(0, 0);
  lcd.print("Zval = ");
  lcd.setCursor(0, 1);
  lcd.print(zval);
  delay(500);



}
