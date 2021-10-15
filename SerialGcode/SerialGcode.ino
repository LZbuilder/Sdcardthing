void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

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
