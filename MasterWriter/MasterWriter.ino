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
    1. The Switch on The Rotary encoder connected to Anolag pin 0
    2. CLK goes to Pin 2
    3. DT goes to Pin 3
   Instuctions for Slave and Master Arduino:
    1. Connect the A4 pin of Master to A4 pin on Slave
    2. Connect the A5 pin of Master to A5 pin on Slave
    3. Connect the GND pin of Master to GND pin on Slave
*/

#define swre A0   // The Switch on The Rotary encoder connected to Anolag pin 0
#define outputA 2 // Fuck this
#define outputB 3 // Fuck this

#include <Wire.h>                                         // Wire Libary inorder for the two arduinos to communicate they use Anolag Pins 4 and 5
#include <LiquidCrystal.h>                                // The Library for lcd
#include <SPI.h>                                          // Libary for SD card Reading and List files
#include <SD.h>                                           // Libary for SD card Reading and List files
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7; // Defining Variables for the lcd
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);                // Setting up the lcd

const int chipSelect = 10;
File myFile;
File root;
//String gcodefile = "gcode.txt";
const int delaytime = 1000; // important

String val;

double endresult;
double xendresult;
double yendresult;


byte wholenumber;
byte remainder;

char singleletterchar;
short i;
int lengthstr;

int counter = 0;
int aState;
int aLastState;
uint8_t sensorValA0_prev;

String files[1];

String readInput = "";

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial)
  {
    ;
  }
  Serial.println("Initializing SD card...");
  delay(100);
  if (!SD.begin(chipSelect))
  {
    Serial.println("NOPE");
    while (true)
      ;
  }

  Serial.println("initialization done.");

  Wire.begin(); // join i2c bus with address Master
  lcd.begin(16, 2);
  pinMode(outputA, INPUT);
  pinMode(outputB, INPUT);
  pinMode(swre, INPUT_PULLUP);
  aLastState = digitalRead(outputA);
  sensorValA0_prev = digitalRead(swre);

  //
  maingui();
}

void loop()
{
}

void maingui()
{

  delay(10);
  counter = 0;
  boolean truefalse = true;
  int selected = 0;
  char *text[] = {"Print           ", "Settings        ", "About           ", "----------------"};
  lcd.clear();

  lcd.println(text[0]);

  lcd.setCursor(15, 0); // Sets to the last collum on the first row.

  lcd.write(byte(0)); // the up arrow

  lcd.setCursor(0, 1);

  lcd.println(text[1]);

  lcd.setCursor(15, 1);

  lcd.write(byte(1)); // the down arrow
  boolean whiletrue = true;
  while (true)
  { // While on the main screen you do this...
    readInput = "";
    if (Serial.available())
    {

      readInput = Serial.readString();
      Serial.println(readInput);

      if (readInput == "Sugma")
      {
        Serial.println("Enter your file name:");
        while (!Serial.available())
        {
          ;
        }
        readInput = Serial.readString();
        Serial.println("readInput = " + readInput);
        gcodereader(readInput); // Opens the File name on SD CARD MODULE
      }
      readInput = "";
    }
    
    aState = digitalRead(outputA); // Reads the "current" state of the outputA
    // If the previous and the current state of the outputA are different, that means a Pulse has occured
    if (aState != aLastState)
    {
      // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
      if (digitalRead(outputB) != aState)
      {
        if (truefalse)
        {
          counter--;
          truefalse = false;
        }
        else
        {

          truefalse = true;
        }
        if (counter > 2)
        {
          counter = 0;
        }
        if (counter < 0)
        {
          counter = 2;
        }
      }
      else
      {
        if (truefalse)
        {
          counter++;
          truefalse = false;
        }
        else
        {

          truefalse = true;
        }
        if (counter < 0)
        {
          counter = 2;
        }
        if (counter > 2)
        {
          counter = 0;
        }
      }
      //Serial.print("Position: ");
      //Serial.println(counter);
      aLastState = aState;
      //Now we do to scrolling up and down
      lcd.clear();

      lcd.println(text[int(counter)]);
      lcd.setCursor(0, 1);

      lcd.println(text[int(counter + 1)]);
    }

    uint8_t sensorValA0 = digitalRead(swre);
    if (sensorValA0 == LOW && sensorValA0_prev == HIGH)
    {
      Serial.println("Buttonpressed");
      if (int(counter) == 0)
      {
        //Clicked Print
        //Serial.println("PrintGui");

        lcd.clear();
        lcd.setCursor(0, 1);

        lcd.println("Loading...      ");
        gcodefinder();
        delay(300);
        while (true)
        {
          delay(10);
          counter = 0;
          boolean truefalse = true;
          int selected = 0;
          char *text[] = {"Prints:         "};
          lcd.clear();

          lcd.println(text[0]);

          lcd.setCursor(15, 0); // Sets to the last collum on the first row.

          lcd.setCursor(0, 1);

          lcd.println(files[0]);

          while (true)
          { // While on the Print screen you do this...

            aState = digitalRead(outputA); // Reads the "current" state of the outputA
            // If the previous and the current state of the outputA are different, that means a Pulse has occured
            if (aState != aLastState)
            {
              // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
              if (digitalRead(outputB) != aState)
              {
                if (truefalse)
                {
                  counter--;

                  truefalse = false;
                }
                else
                {

                  truefalse = true;
                }
                if (counter > 10)
                {
                  counter = -1;
                }
                if (counter < -1)
                {
                  counter = 10;
                }
              }
              else
              {
                if (truefalse)
                {
                  counter++;
                  truefalse = false;
                }
                else
                {

                  truefalse = true;
                }
                if (counter < -1)
                {
                  counter = 10;
                }
                if (counter > 10)
                {
                  counter = -1;
                }
              }
              Serial.print("Position: ");
              Serial.println(counter);
              aLastState = aState;
              //PrintGui
              //Now we do to scrolling up and down
              lcd.clear();

              lcd.println(text[0]);
              lcd.setCursor(0, 1);

              lcd.println(files[int(counter)]);
              if (counter == -1)
              {
                lcd.setCursor(0, 1); // Sets to the last collum on the first row.

                lcd.write("<-- Back"); // the dot
              }
              else
              {
                lcd.setCursor(15, 0); // Sets to the last collum on the first row.

                lcd.write(" "); // the dot
              }
            }
            // Code that makes the buttonpressed work
            uint8_t sensorValA0 = digitalRead(swre);
            if (sensorValA0 == LOW && sensorValA0_prev == HIGH)
            {
              Serial.println("Buttonpressed");
              if (counter == -1)
              {
                //Go Back To main screen
                sensorValA0_prev = digitalRead(swre);
                maingui();
                break;
              }
              else if (files[0] != "" && counter > -1)
              {
                sensorValA0_prev = digitalRead(swre);
                //gcodefile = files[counter];

                //Serial.println(gcodefile);

                gcodereader(files[counter]);
                break;
              }
            }

            sensorValA0_prev = digitalRead(swre);
          }
          break;
        }
        break;
      }
      else if (int(counter) == 1)
      {
        //Clicked Settings
        Serial.println("SettingsGui");
        //SettingGui
        break;
      }
      else if (int(counter) == 2)
      {
        //Clicked About
        Serial.println("AboutGui");
        //AboutGui
        break;
      }
    }

    sensorValA0_prev = digitalRead(swre);
  }
}

void gcodefinder()
{

  // Use LCD and ROTARY Encoder to find a gcode file

  root = SD.open("/");
  delay(10);
  printDirectory(root);
  delay(10);
}
void printDirectory(File dir)
{ // I need to fix this
  int i = 0;

  while (true)
  {

    File entry = dir.openNextFile();
    if (!entry)
    {
      // no more files
      break;
    }

    if (i != 0)
    {
      files[i - 1] = entry.name();
      Serial.println(files[i - 1]);
    }

    entry.close();
    i++;
  }
}

void gcodereader(String gcodefile)
{
  Serial.println("gcodereader was inicated ");
  Serial.println(gcodefile);
  //Before we do ANY Of the code below we must find what file we want until we press the switch!
  myFile = SD.open(gcodefile, FILE_READ);

  if (myFile)
  {
    Serial.println("Opening ");

    // read from the file until there's nothing else in it:
    while (myFile.available())
    {
      val = "";
      //gets a byte
      singleletterchar = char(myFile.read()); //makes byte to char
      gcodeSplitter(singleletterchar);
    }
    myFile.close();
  }
  else
  {
    Serial.println("myFile not available");
  }
}

void gcodeSplitter(char letter)
{ // Trying to make this function find what is after G1 or G0 and then if find
  val = "";
  endresult = 0;
  xendresult = 0;
  yendresult = 0;
  
  if (myFile.available())
  {
    delay(100);
    switch (letter)
    {
    case 'G':
      singleletterchar = ' ';
      singleletterchar = char(myFile.read());

      val = calDigitsSD(singleletterchar); // My function that finds a String value of what comes after G
      delay(5);
      Serial.println("Gval:");
      delay(5);
      Serial.println(val);

      endresult = val.toInt();

      if (endresult == 1)
      {
        while (singleletterchar != 'X' && singleletterchar != 'Y' && singleletterchar != 'Z' && singleletterchar != 'E')
        {
          delay(1);
          Serial.println("In G1 While Loop: ");
          Serial.println(String(singleletterchar));
          singleletterchar = char(myFile.read());
        }

        //('G', 1, 0);
        Serial.println(String(singleletterchar));
        xpos = xendresult;
        ypos = yendresult;
        if (xpos >= 0 && ypos >= 0)
    {
        //then do alexanders code
        c = sqrt(sq(xpos) + sq(ypos));
        gamma = acos((sq(lOne) + sq(c) - sq(lTwo)) / (2 * lOne * c));
        beta = 180 - (2 * gamma);
        Serial.println(gamma);
        Serial.println(beta);
        servoBase.write(gamma);
        servoLinkage.write(beta);
    }
        gcodeSplitterSD(singleletterchar);
      }
      else if (endresult == 0)
      {
        Serial.println("YoU dUmB fUcKeR");
        while (singleletterchar != 'X' && singleletterchar != 'Y' && singleletterchar != 'Z' && singleletterchar != 'E')
        {
          delay(1);
          Serial.println("In G0 While Loop: " + String(singleletterchar));
          singleletterchar = char(myFile.read());
        }

        //('G', 0, 0);
        Serial.println(String(singleletterchar));
        xpos = xendresult;
        ypos = yendresult;
        if (xpos >= 0 && ypos >= 0)
    {
        //then do alexanders code
        c = sqrt(sq(xpos) + sq(ypos));
        gamma = acos((sq(lOne) + sq(c) - sq(lTwo)) / (2 * lOne * c));
        beta = 180 - (2 * gamma);
        Serial.println(gamma);
        Serial.println(beta);
        servoBase.write(gamma);
        servoLinkage.write(beta);
    }
        gcodeSplitterSD(singleletterchar);
      }
      else
      {
        Serial.println("Case G but unknow digit: " + String(singleletterchar));
        gcodeSplitterSD(singleletterchar);
      }
      break;
    case 'X':
      singleletterchar = ' ';
      //Serial.println(String(singleletterchar));
      singleletterchar = char(myFile.read());
      //Serial.println("Writing singleletterchar:");
      //Serial.println(singleletterchar);
      if (isDigit(singleletterchar))
      {
        
        val = calDigitsSD(singleletterchar);

        Serial.println(val);
        xendresult = val.toDouble();
        //Serial.println(String(xendresult));
        Serial.println("X Entire Number: " + String(xendresult));
        wholenumber = int(xendresult); // or you can just send it over a byte

        remainder = rem(xendresult, wholenumber); // I made a function to find what is after the decimal point!

        Serial.println("xWhole: " + String(wholenumber));

        Serial.println("xRemainder: " + String(remainder));

        //('X', wholenumber, remainder);
        gcodeSplitterSD(singleletterchar = char(myFile.read())); // assuming!! the next letter is Y but could be Z or E
      }
      else
      {
        Serial.println("Case X but no digit: " + String(singleletterchar));
        gcodeSplitterSD(singleletterchar);
      }
      break;
    case 'Y':
      singleletterchar = ' ';
      singleletterchar = char(myFile.read());
      if (isDigit(singleletterchar))
      {

        val = calDigitsSD(singleletterchar);

        //Serial.println(xval);
        yendresult = val.toDouble();
        Serial.println("Y Entire Number: " + String(yendresult));
        wholenumber = int(yendresult); // or you can just send it over a byte

        remainder = rem(yendresult, wholenumber); // I made a function to find what is after the decimal point!

        Serial.println("yWhole: " + String(wholenumber));

        Serial.println("yRemainder: " + String(remainder));

        //('Y', wholenumber, remainder);
        gcodeSplitterSD(singleletterchar = char(myFile.read())); // assuming!! the next letter is Y but could be Z or E
      }
      else
      {
        Serial.println("Case Y but no digit: " + String(singleletterchar));
        gcodeSplitterSD(singleletterchar);
      }
      break;
    case 'Z':
      singleletterchar = ' ';
      singleletterchar = char(myFile.read());
      if (isDigit(singleletterchar))
      {

        val = calDigitsSD(singleletterchar);

        //Serial.println(xval);
        endresult = val.toDouble();
        Serial.println("Z Entire Number: " + String(endresult));
        wholenumber = int(endresult); // or you can just send it over a byte

        remainder = rem(endresult, wholenumber); // I made a function to find what is after the decimal point!

        Serial.println("zWhole: " + String(wholenumber));

        Serial.println("zRemainder: " + String(remainder));

        //('Z', wholenumber, remainder);
        gcodeSplitterSD(singleletterchar = char(myFile.read())); // assuming!! the next letter is Y but could be Z or E
      }
      else
      {
        Serial.println("Case Z but no digit: " + String(singleletterchar));
        gcodeSplitterSD(singleletterchar);
      }
      break;
    case ' ':
      Serial.println("Space");
    break;
    case '\n': 
      Serial.println("BackSlashN");
      break;
    default:

      Serial.println("Default Executed: ");
      Serial.println(String(singleletterchar));
      singleletterchar = ' ';
      singleletterchar = char(myFile.read());
      gcodeSplitterSD(singleletterchar);
      break;
    }
  }
  else
  {
    Serial.println("Finished!");
  }
}

