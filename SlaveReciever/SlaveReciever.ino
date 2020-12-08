#include <Wire.h>

int lukaval = 1;
double xval = 0;
double yval = 0;
double zval = 0;

#include <LiquidCrystal.h>
// lcd(RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

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
