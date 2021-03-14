

/* Instuctions for SD Card:
    1. Connect - ground and 3.3v or 5v
    2. CS - pin 10
    3. MOSI - pin 11
    4. SCK - 13
    5. MISO - pin 12

   Instructions for lcd:
    (RS, E, D4, D5, D6, D7)
    (8, 9, 4, 5, 6, 7)
   Test and see if the LCD works!! with your own code!

   Instructions for Rotary Encoder:
     
   

*/

#define swre A0 // The Switch on The Rotary encoder connected to Anolag pin 0
#define outputA 2 // Fuck this
#define outputB 3 // Fuck this

#include <Wire.h> // Wire Libary inorder for the two arduinos to communicate they use Anolag Pins 4 and 5
#include <LiquidCrystal.h> // The Library for lcd
#include <SPI.h> // Libary for SD card Reading and List files
#include <SD.h> // Libary for SD card Reading and List files
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7; // Defining Variables for the lcd
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);// Setting up the lcd

const short chipSelect = 10;
File myFile;
File root;

boolean recieveval = false;
String gcodefile = "gcode.txt";

const int delaytime = 1000; // important

double g = 0;
String gval = "";
String xval = "";
String yval = "";


double x = 0; //end result of what comes after x
double y = 0; //end result of what comes after y
byte xwholenumber = 0;
byte xremainder;
byte ywholenumber;
byte yremainder;


char singleletterchar; int singleletterint;
String multiple[] = {};
short i;
int lengthstr;



int counter = 0;
int aState;
int aLastState;
uint8_t sensorValA0_prev;

String files[1];




void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  delay(10);



  Serial.println("Initializing SD card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("NOPE");
    while (true);
  }


  Serial.println("initialization done.");
  Wire.begin();                // join i2c bus with address Master
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode (outputA, INPUT);
  pinMode (outputB, INPUT);
  pinMode (swre, INPUT_PULLUP);
  aLastState = digitalRead(outputA);
  sensorValA0_prev = digitalRead(swre);



  //
  maingui();
  //open file for reading
  //gcodefinder();
  //use file
  //gcodereader();


}

void loop() {



}

void maingui() {
  delay(10);
  counter = 0;
  boolean truefalse = true;
  int selected = 0;
  char *text[] = {"Print           ", "Settings        ", "About           ", "----------------"};
  lcd.clear();
  delay(1);
  lcd.println(text[0]);
  delay(1);
  lcd.setCursor(15, 0); // Sets to the last collum on the first row.
  delay(1);
  lcd.write(byte(0)); // the up arrow
  delay(1);
  lcd.setCursor(0, 1);
  delay(1);
  lcd.println(text[1]);
  delay(1);
  lcd.setCursor(15, 1);
  delay(1);
  lcd.write(byte(1));// the down arrow
  boolean whiletrue = true;
  while (true) { // While on the main screen you do this...

    aState = digitalRead(outputA); // Reads the "current" state of the outputA
    // If the previous and the current state of the outputA are different, that means a Pulse has occured
    if (aState != aLastState) {
      // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
      if (digitalRead(outputB) != aState) {
        if (truefalse) {
          counter --;
          truefalse = false;

        } else {

          truefalse = true;

        }
        if (counter > 2) {
          counter = 0;
        }
        if (counter < 0) {
          counter = 2;
        }
      }
      else {
        if (truefalse) {
          counter ++;
          truefalse = false;
        } else {

          truefalse = true;

        }
        if (counter < 0) {
          counter = 2;
        }
        if (counter > 2) {
          counter = 0;
        }

      }
      Serial.print("Position: ");
      Serial.println(counter);
      aLastState = aState;
      //Now we do to scrolling up and down
      lcd.clear();
      delay(1);
      lcd.println(text[int(counter)]);
      lcd.setCursor(0, 1);
      delay(1);
      lcd.println(text[int(counter + 1)]);
    }

    uint8_t sensorValA0 = digitalRead(swre);
    if (sensorValA0 == LOW && sensorValA0_prev == HIGH)
    {
      Serial.println("Buttonpressed");
      if (int(counter) == 0) {
        sensorValA0_prev = digitalRead(swre);
        //Clicked Print
        Serial.println("PrintGui");

        lcd.clear();
        lcd.setCursor(0, 1);
        delay(1);
        lcd.println("Loading...      ");
        gcodefinder();
        delay(100);
        while (true) {
          delay(10);
          counter = 0;
          boolean truefalse = true;
          int selected = 0;
          char *text[] = {"Prints:         "};
          lcd.clear();
          delay(1);
          lcd.println(text[0]);
          delay(1);
          lcd.setCursor(15, 0); // Sets to the last collum on the first row.
          delay(1);
          lcd.setCursor(0, 1);
          delay(1);
          lcd.println(files[0]);
          delay(1);
          lcd.setCursor(15, 1);
          delay(1);

          while (true) { // While on the Print screen you do this...

            aState = digitalRead(outputA); // Reads the "current" state of the outputA
            // If the previous and the current state of the outputA are different, that means a Pulse has occured
            if (aState != aLastState) {
              // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
              if (digitalRead(outputB) != aState) {
                if (truefalse) {
                  counter --;

                  truefalse = false;

                } else {

                  truefalse = true;

                }
                if (counter > 10) {
                  counter = -1;
                }
                if (counter < -1) {
                  counter = 10;
                }

              }
              else {
                if (truefalse) {
                  counter ++;
                  truefalse = false;
                } else {

                  truefalse = true;

                }
                if (counter < -1) {
                  counter = 10;
                }
                if (counter > 10) {
                  counter = -1;
                }

              }
              Serial.print("Position: ");
              Serial.println(counter);
              aLastState = aState;
              //PrintGui
              //Now we do to scrolling up and down
              lcd.clear();
              delay(1);
              lcd.println(text[0]);
              lcd.setCursor(0, 1);
              delay(1);
              lcd.println(files[int(counter)]);
              if (counter == -1) {
                lcd.setCursor(0, 1); // Sets to the last collum on the first row.
                delay(1);
                lcd.write("<-- Back"); // the dot
              } else {
                lcd.setCursor(15, 0); // Sets to the last collum on the first row.
                delay(1);
                lcd.write(" "); // the dot
              }
            }
            // Code that makes the buttonpressed work
            uint8_t sensorValA0 = digitalRead(swre);
            if (sensorValA0 == LOW && sensorValA0_prev == HIGH)
            {
              Serial.println("Buttonpressed");
              if (counter == -1) {
                //Go Back To main screen
                sensorValA0_prev = digitalRead(swre);
                maingui();
                break;
              } else if (files[0] != "" && counter > -1) {
                sensorValA0_prev = digitalRead(swre);
                gcodefile = files[counter];
                delay(1);
                Serial.println(gcodefile);
                delay(1);
                gcodereader();
                break;
              }
            }

            sensorValA0_prev = digitalRead(swre);


          }
          break;
        }
        break;
      } else if (int(counter) == 1) {
        //Clicked Settings
        Serial.println("SettingsGui");
        //SettingGui
        break;

      } else if (int(counter) == 2) {
        //Clicked About
        Serial.println("AboutGui");
        //AboutGui
        break;

      }
    }

    sensorValA0_prev = digitalRead(swre);


  }
}


void gcodefinder() {

  // Use LCD and ROTARY Encoder to find a gcode file

  root = SD.open("/");
  delay(10);
  printDirectory(root);
  delay(10);
}
void printDirectory(File dir) { // I need to fix this
  int i = 0;

  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }

    if (i != 0) {
      files[i - 1] = entry.name();
      Serial.println(files[i - 1]);
    }

    entry.close();
    i++;
    delay(1);
  }
}

void gcodereader() {
  Serial.println("gcodereader was inicated");


  //Before we do ANY Of the code below we must find what file we want until we press the switch!
  myFile = SD.open(gcodefile);

  if (myFile) {
    Serial.println("Opening " + gcodefile);

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
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
                delay(1);
                xremainder = rem(x, xwholenumber); // I made a function to find what is after the decimal point!
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
                    // 
                    


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


int rem(double remainder, short whole) {
  short wholelen = String(whole).length();
  short result = 0;
  String rema = String(remainder);
  short lengthrema = rema.length();
  String resultstring = "";



  for (short i = 0; i < lengthrema; i++) {
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
