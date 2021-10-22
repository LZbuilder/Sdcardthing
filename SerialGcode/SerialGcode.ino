#include <MatrixMath.h>
#include <Servo.h>
Servo servoBase;
Servo servoLinkage;

#define lOne 250 //REMEMBER lONE and lTwo must be equal to eachother
#define lTwo 250 //REMEMBER lONE and lTwo must be equal to eachother

double xpos = 60;
double ypos = 40;
float c = sqrt(sq(xpos) + sq(ypos));
float gamma = acos((sq(lOne) + sq(c) - sq(lTwo)) / (2 * lOne * c));
float beta = 180 - (2 * gamma);

String val = "";

double endresult = 0;

byte wholenumber;
byte remainder;

char singleletterchar;
short i;

void setup()
{
  // initialize serial:
  Serial.begin(115200);
  while (!Serial)
  {
    ;
  }
  Serial.println("Booting up!");
  servoBase.attach(9);
  servoLinkage.attach(8);
  servoBase.write(0);
  servoLinkage.write(0);
  Serial.println("Servos Written!");
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (Serial.available())
  {
    gcodereader();
  }
}

void gcodereader()
{
  Serial.println("gcodereader was inicated");
  //Before we do ANY Of the code below we must find what file we want until we press the switch!
  Serial.println("Opening ");

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
      while (singleletterchar != 'X' && singleletterchar != 'Y' && singleletterchar != 'Z')
      {
        delay(1);
        singleletterchar = char(Serial.read());
      }
      delay(1);
      //Do Alexanders code now!
      if (xpos >= 0 && ypos >= 0)
      {
        //then do alexanders code
        Serial.println("Doing Alexanders Code");
        c = sqrt(sq(xpos) + sq(ypos));
        gamma = acos((sq(lOne) + sq(c) - sq(lTwo)) / (2 * lOne * c));
        beta = 180 - (2 * gamma);
        Serial.println(gamma);
        Serial.println(beta);
        servoBase.write(gamma);
        servoLinkage.write(beta);
        delay(1000);
      }
      gcodeSplitter(singleletterchar);
    }
    else if (endresult == 0)
    {
      Serial.println("YoU dUmB fUcKeR");
      while (singleletterchar != 'X' && singleletterchar != 'Y' && singleletterchar != 'Z')
      {
        delay(1);
        singleletterchar = char(Serial.read());
      }
      delay(1);
      //Do Alexanders code now!
      if (xpos >= 0 && ypos >= 0)
      {
        //then do alexanders code
        Serial.println("Doing Alexanders Code");
        c = sqrt(sq(xpos) + sq(ypos));
        gamma = acos((sq(lOne) + sq(c) - sq(lTwo)) / (2 * lOne * c));
        beta = 180 - (2 * gamma);
        Serial.println(gamma);
        Serial.println(beta);
        servoBase.write(gamma);
        servoLinkage.write(beta);
        delay(1000);
      }
      gcodeSplitter(singleletterchar);
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
    break;
  }
}

String calDigits(char thisDigit)
{
  String mystring = "";
  if (isDigit(thisDigit))
  {
    while (isDigit(thisDigit) || thisDigit == '.')
    {
      mystring += thisDigit;
      thisDigit = char(Serial.read());
    }
  }
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
