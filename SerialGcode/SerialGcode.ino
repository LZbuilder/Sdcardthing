#include <SPI.h> // Libary for SD card Reading and List files
#include <SD.h>
const int chipSelect = 10;
File myFile;

#define lOne 250 //REMEMBER lONE and lTwo must be equal to eachother
#define lTwo 250 //REMEMBER lONE and lTwo must be equal to eachother

double xpos = 60;
double ypos = 40;
float c = sqrt(sq(xpos) + sq(ypos));
float gamma = acos((sq(lOne) + sq(c) - sq(lTwo)) / (2 * lOne * c));
float beta = 180 - (2 * gamma);

String val = "";
String mystring = "";
double endresult = 0;

byte wholenumber;
byte remainder;

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
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (Serial.available())
  {
    gcodereader();
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

void gcodereader()
{
  Serial.println("gcodereader was inicated");
  //Before we do ANY Of the code below we must find what file we want until we press the switch!
  Serial.println("Reading Serial...");

  // read from the file until there's nothing else in it:
  while (Serial.available())
  {
    Serial.println("We Made it to the while loop");
    singleletterchar = "";
    singleletterchar = char(Serial.read()); //reads int then converts to char
    gcodeSplitter(singleletterchar);
  }
}

void gcodeSplitter(char letter)
{ // Trying to make this function find what is after G1 or G0 and then if find
  if (Serial.available())
  {
    switch (letter)
    {
    case 'G':
      singleletterchar = char(Serial.read());

      val = calDigits(singleletterchar); // My function that fines a String value of what comes after G
      Serial.println("Gval: " + String(val));
      delay(1);
      endresult = val.toInt();
      Serial.println("Endresult: " + String(endresult));
      delay(1);
      if (endresult == 1)
      {
        while (singleletterchar != 'X' && singleletterchar != 'Y' && singleletterchar != 'Z' && singleletterchar != 'E' && singleletterchar != 'F')
        {
          delay(1);
          Serial.println("In G1 While Loop: " + String(singleletterchar));
          singleletterchar = char(Serial.read());
        }
        delay(1);
        //Do Alexanders code now!
        if (xpos >= 0 && ypos >= 0)
        {
          //then do alexanders code
          /*Serial.println("Doing Alexanders Code");
          c = sqrt(sq(xpos) + sq(ypos));
          gamma = acos((sq(lOne) + sq(c) - sq(lTwo)) / (2 * lOne * c));
          beta = 180 - (2 * gamma);
          Serial.println(String(gamma));
          Serial.println(String(beta));
          delay(1000);
        */
        }
        gcodeSplitter(singleletterchar);
      }
      else if (endresult == 0)
      {
        Serial.println("YoU dUmB fUcKeR");
        while (singleletterchar != 'X' && singleletterchar != 'Y' && singleletterchar != 'Z' && singleletterchar != 'E' && singleletterchar != 'F')
        {
          delay(1);
          singleletterchar = char(Serial.read());
        }
        delay(1);
        //Do Alexanders code now!
        if (xpos >= 0 && ypos >= 0)
        {
          //then do alexanders code
          /* Serial.println("Doing Alexanders Code");
          c = sqrt(sq(xpos) + sq(ypos));
          gamma = acos((sq(lOne) + sq(c) - sq(lTwo)) / (2 * lOne * c));
          beta = 180 - (2 * gamma);
          Serial.println(String(gamma));
          Serial.println(String(beta));
          delay(1000);
          */
        }
        gcodeSplitter(singleletterchar = Serial.read());
      }
      else
      {
        Serial.println("Case G but unknow digit: " + String(singleletterchar));
        gcodeSplitter(singleletterchar = Serial.read());
      }
      break;
    case 'X':
      singleletterchar = char(Serial.read());
      if (isDigit(singleletterchar))
      {

        val = calDigits(singleletterchar);

        delay(1);
        //Serial.println(xval);
        endresult = val.toDouble();
        xpos = endresult;
        Serial.println("X Entire Number: " + String(endresult));
        wholenumber = int(endresult); // or you can just send it over a byte
        delay(1);
        remainder = rem(endresult, wholenumber); // I made a function to find what is after the decimal point!
        delay(1);
        Serial.println("xWhole: " + String(wholenumber));
        delay(1);
        Serial.println("xRemainder: " + String(remainder));
        delay(1);
        gcodeSplitter(singleletterchar = char(Serial.read())); // assuming!! the next letter is Y but could be Z or E
      }
      else
      {
        Serial.println("Case X but no digit: " + String(singleletterchar));
        gcodeSplitter(singleletterchar = Serial.read());
      }
      break;
    case 'Y':
      singleletterchar = char(Serial.read());
      if (isDigit(singleletterchar))
      {

        val = calDigits(singleletterchar);

        delay(1);
        //Serial.println(xval);
        endresult = val.toDouble();
        ypos = endresult;
        Serial.println("Y Entire Number: " + String(endresult));
        wholenumber = int(endresult); // or you can just send it over a byte
        delay(1);
        remainder = rem(endresult, wholenumber); // I made a function to find what is after the decimal point!
        delay(1);
        Serial.println("yWhole: " + String(wholenumber));
        delay(1);
        Serial.println("yRemainder: " + String(remainder));
        delay(1);
        gcodeSplitter(singleletterchar = char(Serial.read())); // assuming!! the next letter is Y but could be Z or E
      }
      else
      {
        Serial.println("Case Y but no digit: " + String(singleletterchar));
        gcodeSplitter(singleletterchar = Serial.read());
      }
      break;
    case 'Z':
      singleletterchar = char(Serial.read());
      if (isDigit(singleletterchar))
      {

        val = calDigits(singleletterchar);

        delay(1);
        //Serial.println(xval);
        endresult = val.toDouble();
        Serial.println("Z Entire Number: " + String(endresult));
        wholenumber = int(endresult); // or you can just send it over a byte
        delay(1);
        remainder = rem(endresult, wholenumber); // I made a function to find what is after the decimal point!
        delay(1);
        Serial.println("zWhole: " + String(wholenumber));
        delay(1);
        Serial.println("zRemainder: " + String(remainder));
        delay(1);
        gcodeSplitter(singleletterchar = char(Serial.read())); // assuming!! the next letter is Y but could be Z or E
      }
      else
      {
        Serial.println("Case Z but no digit: " + String(singleletterchar));
        gcodeSplitter(singleletterchar = Serial.read());
      }
      break;
      case ' ':
      Serial.println("Case Was blank or space");
      gcodeSplitter(singleletterchar = char(Serial.read()));
      break;
    default:
      Serial.println("Default Executed: ");
      Serial.println(String(singleletterchar));
      gcodeSplitter(singleletterchar = char(Serial.read()));
      break;
    }
  }
  else
  {
    Serial.println("Finished!");
  }
}

String calDigits(char thisDigit)
{
  String mystring = "";
  if (isDigit(thisDigit))
  {
    while (isDigit(thisDigit) || thisDigit == '.')
    {
      mystring += String(thisDigit);
      Serial.println(mystring);
      thisDigit = char(Serial.read());
      Serial.println(mystring);
    }
  }
  else
  {
    Serial.println("CalDigits error: " + String(mystring));
  }
  Serial.println(String(mystring));
  return String(mystring);
}

String calDigitsSD(char thisDigit)
{
  mystring = "";
  if (isDigit(thisDigit))
  {
    while (isDigit(thisDigit) || thisDigit == '.')
    {
      mystring += String(thisDigit);
      Serial.println(mystring);
      thisDigit = char(myFile.read());
      Serial.println(mystring);
    }
  }
  else
  {
    Serial.println("CalDigits error: " + String(mystring));
  }
  Serial.println(String(mystring));
  return String(mystring);
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

  //result = 2; //For degbugging

  return result;
}
void gcodereaderSD(String gcodefile)
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
      singleletterchar = char(myFile.read());

      val = calDigitsSD(singleletterchar); // My function that finds a String value of what comes after G
      Serial.println("Gval:");
      Serial.println(String(val));

      endresult = val.toInt();

      if (endresult == 1)
      {
        while (singleletterchar != 'X' && singleletterchar != 'Y' && singleletterchar != 'Z' && singleletterchar != 'E' && singleletterchar != 'F')
        {
          delay(1);
          Serial.println("In G1 While Loop: ");
          Serial.println(String(singleletterchar));
          singleletterchar = char(myFile.read());
        }

        //('G', 1, 0);
        Serial.println(String(singleletterchar));
        gcodeSplitterSD(singleletterchar);
      }
      else if (endresult == 0)
      {
        Serial.println("YoU dUmB fUcKeR");
        while (singleletterchar != 'X' && singleletterchar != 'Y' && singleletterchar != 'Z' && singleletterchar != 'E' && singleletterchar != 'F')
        {
          delay(1);
          Serial.println("In G0 While Loop: " + String(singleletterchar));
          singleletterchar = char(myFile.read());
        }

        //('G', 0, 0);
        Serial.println(String(singleletterchar));
        gcodeSplitterSD(singleletterchar);
      }
      else
      {
        Serial.println("Case G but unknow digit: " + String(singleletterchar));
        gcodeSplitterSD(singleletterchar);
      }
      break;
    case 'X':
      Serial.println(String(singleletterchar));
      singleletterchar = char(myFile.read());
      Serial.println(String(singleletterchar));
      if (isDigit(singleletterchar))
      {

        val = calDigitsSD(singleletterchar);

        Serial.println(String(val));
        endresult = val.toDouble();
        Serial.println(String(endresult));
        Serial.println("X Entire Number: " + String(endresult));
        wholenumber = int(endresult); // or you can just send it over a byte

        remainder = rem(endresult, wholenumber); // I made a function to find what is after the decimal point!

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
      singleletterchar = char(myFile.read());
      if (isDigit(singleletterchar))
      {

        val = calDigitsSD(singleletterchar);

        //Serial.println(xval);
        endresult = val.toDouble();
        Serial.println("Y Entire Number: " + String(endresult));
        wholenumber = int(endresult); // or you can just send it over a byte

        remainder = rem(endresult, wholenumber); // I made a function to find what is after the decimal point!

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
    default:

      Serial.println("Default Executed: ");
      Serial.println(String(singleletterchar));
      gcodeSplitterSD(singleletterchar = char(myFile.read()));
      break;
    }
  }
  else
  {
    Serial.println("Finished!");
  }
}
