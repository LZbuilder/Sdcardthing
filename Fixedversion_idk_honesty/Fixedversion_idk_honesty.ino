/* Instuctions for SD Card:
 *  1. Connect - ground and 3.3v or 5v
 *  2. CS - pin 10
 *  3. MOSI - pin 11
 *  4. SCK - 13
 *  5. MISO - pin 12
 *  
 * Instructions for lcd?
 *  (RS, E, D4, D5, D6, D7)
 *  (8, 9, 4, 5, 6, 7)
 *  
 *  
 */



#include <Wire.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <SD.h>

File myFile;



//work in progres
String strstuff = "G23 X42 Y54.245   Z4; E31; ";
double g = 0;
String gval = "";
String xval = "";
String yval = "";
double x = 0; //end result of what comes after x
double y = 0; //end result of what comes after y
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


  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }

  Serial.println("initialization done.");

  //open file for reading
  
}



void loop() {


}


void lcdsetup(){
  // lcd(RS, E, D4, D5, D6, D7)
  LiquidCrystal lcd (8, 9, 4, 5, 6, 7);
  int numRows = 2;
  int numCols = 16;
}

void gcodereader(){
  myFile = SD.open("gcode.txt");

  if (myFile) {
    Serial.println("gcode.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
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
                //Serial.println(x);

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
                    //Serial.println(y);
                    
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
