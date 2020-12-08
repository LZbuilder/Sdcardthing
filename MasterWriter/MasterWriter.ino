/* Instuctions for SD Card:
    1. Connect - ground and 3.3v or 5v
    2. CS - pin 10
    3. MOSI - pin 11
    4. SCK - 13
    5. MISO - pin 12

   Instructions for lcd?
    (RS, E, D4, D5, D6, D7)
    (8, 9, 4, 5, 6, 7)

   Instructions for Rotary Encoder!!
    We need two digital pins for this

*/




#include <Wire.h>
#include <LiquidCrystal.h>
// lcd(RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
#include <SPI.h>
#include <SD.h>

const int chipSelect = 10;
File myFile;

boolean rev = true;

int amountrecived = 0;

const int delaytime = 10;
//work in progres
String strstuff = "G23 X42 Y54.245   Z4; E31; ";
double g = 0;
String gval = "";
String xval = "";
String yval = "";
String zval = "";
String gcodefile = "gcode.txt";


double x = 0; //end result of what comes after x
double y = 0; //end result of what comes after y
double z = 0;
int xwholenumber;
int xremainder;
int ywholenumber;
int yremainder;
int zwholenumber;
int zremainder;


char singleletterchar; int singleletterint;
String multiple[] = {};
int i;
int lengthstr;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  while (!Serial) {
    ; //Wait for serial monitor to be opened
  }


  Serial.println("Initializing SD card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed. Things to check:");

    Serial.println("1. is a card inserted?");

    Serial.println("2. is your wiring correct?");

    Serial.println("3. did you change the chipSelect pin to match your shield or module?");

    Serial.println("Note: press reset or reopen this serial monitor after fixing your issue!");
    while (true);
  }

  Serial.println("initialization done.");
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);






  lcdsetup(); //Setup the LCD for Debugging
  //open file for reading

  //use file
  gcodereader();


}

void loop() {


}

void lcdsetup() {

  int numRows = 2;
  int numCols = 16;
  lcd.begin(numRows, numCols);
}

void gcodefinder() {

}

void gcodereader() {



  //Before we do ANY Of the code below we must find what file we want until we press the switch!
  myFile = SD.open("gcode.txt");

  if (myFile) {
    Serial.println("gcode.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      if (rev) {


        rev = false;
        delay(delaytime);
        gval = "";
        xval = "";
        yval = "";
        singleletterint = myFile.read(); //gets a byte
        singleletterchar = char(singleletterint); //makes byte to char

        switch (singleletterchar) {
          case 'G':
            singleletterint = myFile.read(); //gets a byte
            singleletterchar = char(singleletterint);

            if (isDigit(singleletterchar)) {
              while (isDigit(singleletterchar)) {
                gval += singleletterchar;
                singleletterint = myFile.read(); //gets a byte
                singleletterchar = char(singleletterint);
              }
              Serial.println(gval);
              g = gval.toDouble();

              if (g == 1) {
                while (singleletterchar != 'X') {
                  singleletterint = myFile.read(); //gets a byte
                  singleletterchar = char(singleletterint);
                }
                singleletterint = myFile.read(); //gets a byte
                singleletterchar = char(singleletterint);
                if (isDigit(singleletterchar)) {
                  while (isDigit(singleletterchar) || singleletterchar == '.') {
                    xval += singleletterchar;
                    singleletterint = myFile.read(); //gets a byte
                    singleletterchar = char(singleletterint);
                  }
                  //Serial.println(xval);
                  x = xval.toDouble();
                  xwholenumber = int(x); // or you can just send it over a byte
                  xremainder = rem(x); // I made a function to find what is after the decimal point!
                  //Serial.println(x);
                  Wire.beginTransmission(4); // transmit to device #4

                  Wire.write(xwholenumber); // sends one byte

                  Wire.write(xremainder);  // sends one byte
                  Wire.endTransmission();    // ends the transmission

                  singleletterint = myFile.read(); //gets a byte
                  singleletterchar = char(singleletterint);

                  if (singleletterchar == 'Y') {
                    singleletterint = myFile.read(); //gets a byte
                    singleletterchar = char(singleletterint);
                    if (isDigit(singleletterchar)) {
                      while (isDigit(singleletterchar) || singleletterchar == '.') {
                        yval += singleletterchar;
                        singleletterint = myFile.read(); //gets a byte
                        singleletterchar = char(singleletterint);
                      }
                      //Serial.println(yval);
                      y = yval.toDouble();
                      ywholenumber = int(y); // or you can just send it over a byte
                      yremainder = rem(y); // I made a function to find what is after the decimal point!
                      //Serial.println(y);
                      Wire.beginTransmission(4); // transmit to device #4
                      Wire.write(ywholenumber);              // sends one byte

                      Wire.write(yremainder);
                      Wire.endTransmission();    //
                      if (singleletterchar == 'Z') {
                        singleletterint = myFile.read(); //gets a byte
                        singleletterchar = char(singleletterint);
                        if (isDigit(singleletterchar)) {
                          while (isDigit(singleletterchar) || singleletterchar == '.') {
                            zval += singleletterchar;
                            singleletterint = myFile.read(); //gets a byte
                            singleletterchar = char(singleletterint);
                          }
                          //Serial.println(yval);
                          z = zval.toDouble();
                          zwholenumber = int(z); // or you can just send it over a byte
                          zremainder = rem(z); // I made a function to find what is after the decimal point!
                          //Serial.println(z);
                          Wire.beginTransmission(4); // transmit to device #4
                          Wire.write(zwholenumber);              // sends one byte

                          Wire.write(zremainder);
                          Wire.endTransmission();    //
                          //Wait to recieve something
                          while (!rev) {

                            Serial.println("waiting to receive G");
                          }



                        }
                      }


                    }
                  }


                }
                else {
                  break;
                }
                break;
              }
            }
        }
      }
      else {
        
      }
    }
  }
}


int rem(double remainder) {
  int result = 0;
  String rema = String(remainder);
  int lengthrema = rema.length();
  String resultstring = "";

  for (int i = 0; i < lengthrema; i++) {
    if (rema[i] == ".") {
      i++;
      if (isDigit(rema[i])) {
        while (isDigit(rema[i]) || i < lengthrema) {
          resultstring += rema[i];
          i++;
        }
        result = resultstring.toInt();
      }
    }
  }


  return result;
}

void receiveEvent() {
  rev = true; // this is for when it recieves anything from the slave arduino...
  // it will set rev to true meaning it is ok to send the next piece of gcode!
  lcd.setCursor(0, 1);
  lcd.print("Recived" + amountrecived);
  amountrecived++;
}
