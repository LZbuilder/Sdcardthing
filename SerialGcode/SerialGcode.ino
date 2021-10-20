String inputString = "";         // a String to hold incoming data

boolean recieveval = false;

double g = 0;

String gval = "";
String xval = "";
String yval = "";
String zval = "";

double x = 0; //end result of what comes after x
double y = 0; //end result of what comes after y
double z = 0;
byte xwholenumber = 0;
byte xremainder;
byte ywholenumber;
byte yremainder;
byte zwholenumber = 0;
byte zremainder;


char singleletterchar;
short i;


void setup() {
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    gcodereader();
  }
}

void gcodereader() {
  Serial.println("gcodereader was inicated");
  //Before we do ANY Of the code below we must find what file we want until we press the switch!
  Serial.println("Opening ");

  // read from the file until there's nothing else in it:
  while (Serial.available()) {
    gval = "";
    xval = "";
    yval = "";
    zval = "";
    Serial.println("We Made it to the while loop");
    singleletterchar = ""; 
    singleletterchar = char(Serial.read()); //reads int then converts to char
    gcodeSplitter(singleletterchar); 
  }
}


void gcodeSplitter(char letter) {  // Trying to make this function find what is after G1 or G0 and then if find
  switch (letter){
    case 'G':
      singleletterchar = char(Serial.read());
        
        gval = calDigits(singleletterchar); // My function that finds a String value of what comes after G
        Serial.println("Gval: " + String(gval));
        delay(1);
        g = gval.toInt();
        delay(1);
        if (g == 1) {
          while (singleletterchar != 'X' && singleletterchar != 'Y' && singleletterchar != 'Z') {
            delay(1);
            singleletterchar = char(Serial.read());
          }
          delay(1);
          gcodeSplitter(singleletterchar);
        } else if (g == 0){
          Serial.println("YoU dUmB fUcKeR");
        }
      break;
    case 'X':
          singleletterchar = char(Serial.read());
          if (isDigit(singleletterchar)) {
            
            xval = calDigits(singleletterchar); 

            delay(1);
            //Serial.println(xval);
            x = xval.toDouble();
            Serial.println("X Entire Number: " + String(x));
            xwholenumber = int(x); // or you can just send it over a byte
            delay(1);
            xremainder = rem(x, xwholenumber); // I made a function to find what is after the decimal point!
            delay(1);
            Serial.println("xWhole: " + String(xwholenumber));
            delay(1);
            Serial.println("xRemainder: " + String(xremainder));
            delay(1);
            gcodeSplitter(singleletterchar = char(Serial.read())); // assuming!! the next letter is Y but could be Z or E 
          }
      break;
    case 'Y':
          singleletterchar = char(Serial.read());
          if (isDigit(singleletterchar)) {
            
            yval = calDigits(singleletterchar); 

            delay(1);
            //Serial.println(xval);
            y = yval.toDouble();
            Serial.println("Y Entire Number: " + String(y));
            ywholenumber = int(y); // or you can just send it over a byte
            delay(1);
            yremainder = rem(y, ywholenumber); // I made a function to find what is after the decimal point!
            delay(1);
            Serial.println("yWhole: " + String(ywholenumber));
            delay(1);
            Serial.println("yRemainder: " + String(yremainder));
            delay(1);
            gcodeSplitter(singleletterchar = char(Serial.read())); // assuming!! the next letter is Y but could be Z or E
          }
      break;
    case 'Z':
          singleletterchar = char(Serial.read());
          if (isDigit(singleletterchar)) {
            
            zval = calDigits(singleletterchar); 

            delay(1);
            //Serial.println(xval);
            z = zval.toDouble();
            Serial.println("Z Entire Number: " + String(z));
            zwholenumber = int(z); // or you can just send it over a byte
            delay(1);
            zremainder = rem(z, zwholenumber); // I made a function to find what is after the decimal point!
            delay(1);
            Serial.println("zWhole: " + String(zwholenumber));
            delay(1);
            Serial.println("zRemainder: " + String(zremainder));
            delay(1);
            gcodeSplitter(singleletterchar = char(Serial.read())); // assuming!! the next letter is Y but could be Z or E
          } 
      break;
  }

} 

String calDigits(char thisDigit) {
  String mystring = "";
  if (isDigit(thisDigit)) {
    while (isDigit(thisDigit) || thisDigit == '.') {
      mystring += thisDigit;
      thisDigit = char(Serial.read());
    }
  }
  return String(mystring);
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
