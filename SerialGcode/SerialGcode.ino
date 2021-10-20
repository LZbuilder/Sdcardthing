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

  
    Serial.println("Opening ");

    // read from the file until there's nothing else in it:
    while (Serial.available()) {
      gval = "";
      xval = "";
      yval = "";
      Serial.println("We Made it to the while loop");
      singleletterchar = char(Serial.read()); //makes byte to char

      switch (singleletterchar) {
        case 'G':
          
         singleletterchar = char(Serial.read());

          if (isDigit(singleletterchar)) {
            while (isDigit(singleletterchar)) {
              gval += singleletterchar;
              
             singleletterchar = char(Serial.read());
            }
            Serial.println("Gval:");
            Serial.println(gval);
            g = gval.toDouble();
            delay(1);
            if (g == 1) {
              while (singleletterchar != 'X') {
                
               singleletterchar = char(Serial.read());
              }
              delay(1);
             singleletterchar = char(Serial.read());
              if (isDigit(singleletterchar)) {
                while (isDigit(singleletterchar) || singleletterchar == '.') {
                  xval += singleletterchar;
                  
                 singleletterchar = char(Serial.read());
                }
                delay(1);
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

                
               singleletterchar = char(Serial.read());

                if (singleletterchar == 'Y') {
                  
                 singleletterchar = char(Serial.read());
                  if (isDigit(singleletterchar)) {
                    while (isDigit(singleletterchar) || singleletterchar == '.') {
                      yval += singleletterchar;
                      singleletterint = byte(Serial.read());
                     singleletterchar = char(Serial.read());
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
