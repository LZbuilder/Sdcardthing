

/* Instuctions for SD Card:
    1. Connect - ground and 3.3v or 5v
    2. CS - pin 10
    3. MOSI - pin 11
    4. SCK - 13
    5. MISO - pin 12

   Instructions for lcd?
    (RS, E, D4, D5, D6, D7)
    (8, 9, 4, 5, 6, 7)
   Test and see if the LCD works!! with your own code!

   Instructions for Rotary Encoder!!
    We need three digital pins for this

*/




#include <Wire.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <SD.h>

const int chipSelect = 10;
File myFile;

boolean recieveval = false;

int amountrecived = 0;

const int delaytime = 4000; // important
//work in progres
String strstuff = "G23 X42 Y54.245   Z4; E31; ";
double g = 0;
String gval = "";
String xval = "";
String yval = "";

String gcodefile = "gcode.txt";


double x = 0; //end result of what comes after x
double y = 0; //end result of what comes after y
byte xwholenumber = 0;
byte xremainder;
byte ywholenumber;
byte yremainder;


char singleletterchar; int singleletterint;
String multiple[] = {};
int i;
int lengthstr;



void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  /*while (!Serial) {
    ; //Wait for serial monitor  to be opened
    }
  */


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
  Wire.begin();                // join i2c bus with address Master
  Serial.begin(9600);






  
  //open file for reading

  //use file
  gcodereader();


}

void loop() {


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



      //delay(delaytime);
      recieveval = false;
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
            //Serial.println(gval);
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
                Serial.println(x);
                xwholenumber = int(x); // or you can just send it over a byte
                Serial.println(xwholenumber);
                xremainder = rem(x, xwholenumber); // I made a function to find what is after the decimal point!
                Serial.println(xremainder);
                delay(1);
                Wire.beginTransmission(4); // transmit to device #4
                delay(1);
                Wire.write(byte(xwholenumber));
                delay(1);
                Wire.endTransmission();
                delay(50);
                Wire.beginTransmission(4);
                Wire.write(byte(xremainder));
                Wire.endTransmission();    // ends the transmission
                delay(delaytime);

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
                    yremainder = rem(y, ywholenumber); // I made a function to find what is after the decimal point!
                    Serial.println(y);
                    delay(1);
                    Wire.beginTransmission(4); // transmit to device #4
                    delay(1);
                    Wire.write(byte(ywholenumber));
                    delay(1);
                    Wire.endTransmission();
                    delay(50);
                    Wire.beginTransmission(4);
                    Wire.write(byte(yremainder));
                    delay(1);
                    Wire.endTransmission();
                    delay(delaytime);




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
  }
}


int rem(double remainder, int whole) {
  int wholelen = String(whole).length();
  int result = 0;
  String rema = String(remainder);
  int lengthrema = rema.length();
  String resultstring = "";



  for (int i = 0; i < lengthrema; i++) {
    while (i < wholelen) {
      i++;
    }
    if (rema[i] == "." || isDigit(rema[i])) {

      if (isDigit(rema[i])) {
        while (isDigit(rema[i]) || i < lengthrema) {
          resultstring += rema[i];
          i++;
        }

        result = resultstring.toInt();
      }
    }
  }

  //result = 2; //For degbugging

  return result;
}
