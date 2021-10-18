String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

boolean recieveval = false;

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


void setup() {
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()){
    gcodereader();
  }
}

void gcodereader() {
  Serial.println("gcodereader was inicated");


  //Before we do ANY Of the code below we must find what file we want until we press the switch!
  inputString = byte(Serial.read());

  if (inputString) {
    Serial.println("Opening ");

    // read from the file until there's nothing else in it:
    while (Serial.available()) {
      recieveval = false;
      gval = "";
      xval = "";
      yval = "";
      singleletterint = byte(Serial.read()); //gets a byte
      singleletterchar = char(singleletterint); //makes byte to char

      switch (singleletterchar) {
        case 'G':
          singleletterint = byte(Serial.read()); //gets a byte
          singleletterchar = char(singleletterint);

          if (isDigit(singleletterchar)) {
            while (isDigit(singleletterchar)) {
              gval += singleletterchar;
              singleletterint = byte(Serial.read()); //gets a byte
              singleletterchar = char(singleletterint);
            }
            Serial.println("Gval:");
            Serial.println(gval);
            g = gval.toDouble();

            if (g == 1) {
              while (singleletterchar != 'X') {
                singleletterint = byte(Serial.read()); //gets a byte
                singleletterchar = char(singleletterint);
              }
              singleletterint = byte(Serial.read()); //gets a byte
              singleletterchar = char(singleletterint);
              if (isDigit(singleletterchar)) {
                while (isDigit(singleletterchar) || singleletterchar == '.') {
                  xval += singleletterchar;
                  singleletterint = byte(Serial.read()); //gets a byte
                  singleletterchar = char(singleletterint);
                }
                //Serial.println(xval);
                x = xval.toDouble();
                Serial.println(x);
                xwholenumber = int(x); // or you can just send it over a byte
                delay(1);
                xremainder = rem(x, xwholenumber); // I made a function to find what is after the decimal point!
                delay(1);
                //.beginTransmission(4); // transmit to device #4
                delay(1);
                Serial.println("XWhole");
                Serial.println(xwholenumber);
                delay(1);
                //.endTransmission();
                delay(50);
                //.beginTransmission(4);
                Serial.println("Xremainder");
                Serial.println(xremainder);
                //.endTransmission();    // ends the transmission
                delay(delaytime);

                singleletterint = byte(Serial.read()); //gets a byte
                singleletterchar = char(singleletterint);

                if (singleletterchar == 'Y') {
                  singleletterint = byte(Serial.read()); //gets a byte
                  singleletterchar = char(singleletterint);
                  if (isDigit(singleletterchar)) {
                    while (isDigit(singleletterchar) || singleletterchar == '.') {
                      yval += singleletterchar;
                      singleletterint = byte(Serial.read());
                      singleletterchar = char(singleletterint);
                    }
                    //Serial.println(yval);
                    y = yval.toDouble();
                    ywholenumber = int(y); // or you can just send it over a byte
                    yremainder = rem(y, ywholenumber); // I made a function to find what is after the decimal point!
                    Serial.println(y);
                    delay(1);
                    //.beginTransmission(4); // transmit to device #4
                    delay(1);
                    Serial.println("ywholenumber");
                    Serial.println(ywholenumber);
                    delay(1);
                    //.endTransmission();
                    delay(50);
                    //.beginTransmission(4);
                    Serial.println("yremainder");
                    Serial.println(yremainder);
                    delay(1);
                    //.endTransmission();
                    delay(delaytime);
                    // This is where I could do lcd stuff.



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
