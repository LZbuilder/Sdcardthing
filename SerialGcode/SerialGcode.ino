#include <SPI.h> // Libary for SD card Reading and List files
#include <SD.h>
#include <Servo.h>
#include <MatrixMath.h>
Servo servoBase;
Servo servoLinkage;

const int chipSelect = 10;
File myFile;

#define lOne 500 // REMEMBER lONE and lTwo must be equal to eachother
#define lTwo 500 // REMEMBER lONE and lTwo must be equal to eachother

double xpos = 60;
double ypos = 40;
float c = sqrt(sq(xpos) + sq(ypos));
float gamma = acos((sq(lOne) + sq(c) - sq(lTwo)) / (2 * lOne * c));
float beta = 180 - (2 * gamma);
short delaytime = 1000;

String val = "";
double endresult = 0;
double xendresult = 0;
double yendresult = 0;

byte wholenumber;
byte remainder;
String mystring = "";
byte tester;
char singleletterchar;
short i;

String readInput = "";

void setup()
{
  // initialize serial:
  Serial.begin(9600);
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
  servoBase.attach(2);
  servoLinkage.attach(3);
  servoBase.write(0);
  servoLinkage.write(0);
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (Serial.available())
  {
    // gcodereader();
    readInput = "";

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
      gcodereaderSD(readInput); // Opens the File name on SD CARD MODULE
    }
    readInput = "";
  }
}

String calDigitsSD(char thisDigit)
{
  mystring = "";

  if (isDigit(thisDigit) || thisDigit == ' ')
  {
    mystring += thisDigit;
    while (isDigit(thisDigit) || thisDigit == '.')
    {

      tester = myFile.read();

      thisDigit = char(tester);
      Serial.println("thisDigit: " + String(thisDigit));
      mystring += thisDigit;
    }
    Serial.println("mystring Values");

    Serial.println(mystring);
    return mystring;
  }
  else
  {
    Serial.println("CalDigits error: " + mystring);
    return;
  }
  return;
}

int rem(double remainder, short whole)
{
  short wholelen = String(whole).length();
  short result = 0;
  String rema = String(remainder);
  short lengthrema = rema.length();
  String resultstring = "";

  for (short i = 0; i < lengthrema; i++)
  {
    while (i < wholelen)
    {
      i++;
    }
    if (rema[i] == "." || isDigit(rema[i]))
    {

      if (isDigit(rema[i]))
      {
        while (isDigit(rema[i]) || i < lengthrema)
        {
          resultstring += rema[i];
          i++;
        }

        result = resultstring.toInt();
      }
    }
  }

  // result = 2; //For degbugging

  return result;
}
void gcodereaderSD(String gcodefile)
{
  Serial.println("gcodereader was inicated ");
  Serial.println(gcodefile);
  // Before we do ANY Of the code below we must find what file we want until we press the switch!
  myFile = SD.open(gcodefile, FILE_READ);

  if (myFile)
  {
    Serial.println("Opening ");

    // read from the file until there's nothing else in it:
    while (myFile.available())
    {
      val = "";
      // gets a byte
      singleletterchar = char(myFile.read()); // makes byte to char
      // Serial.println("Singleletterchar:");
      // Serial.println(singleletterchar);
      gcodeSplitterSD(singleletterchar);
    }
    myFile.close();
  }
  else
  {
    Serial.println("myFile not available");
  }
}

void gcodeSplitterSD(char letter)
{ // Trying to make this function find what is after G1 or G0 and then if find
  val = "";
  endresult = 0;
  
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
        Serial.println(xpos);
        ypos = yendresult;
        Serial.println(ypos);
        if (xpos >= 0 && ypos >= 0)
        {
          // then do alexanders code
          c = sqrt(sq(xpos) + sq(ypos));
          gamma = acos((sq(lOne) + sq(c) - sq(lTwo)) / (2 * lOne * c));
          beta = 180 - (2 * gamma);
          Serial.println(gamma);
          Serial.println(beta);
          servoBase.write(gamma);
          servoLinkage.write(beta);
          delay(delaytime);
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
          // then do alexanders code
          c = sqrt(sq(xpos) + sq(ypos));
          gamma = acos((sq(lOne) + sq(c) - sq(lTwo)) / (2 * lOne * c));
          beta = 180 - (2 * gamma);
          Serial.println(gamma);
          Serial.println(beta);
          servoBase.write(gamma);
          servoLinkage.write(beta);
          delay(delaytime);
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
      // Serial.println(String(singleletterchar));
      singleletterchar = char(myFile.read());
      // Serial.println("Writing singleletterchar:");
      // Serial.println(singleletterchar);
      if (isDigit(singleletterchar))
      {

        val = calDigitsSD(singleletterchar);

        Serial.println(val);
        xendresult = val.toDouble();
        // Serial.println(String(xendresult));
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

        // Serial.println(xval);
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

        // Serial.println(xval);
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
