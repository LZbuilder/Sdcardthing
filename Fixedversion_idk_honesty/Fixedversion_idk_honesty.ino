String strstuff = "G23 X42 Y54.245   Z4; E31; ";
String G;
double x; double y; //end result of what comes after x
String xval = ""; String yval = ""; String zval = "";//for computing stuff and combing numbers :)
int i; //simple integer used for what specific character in the string we are using!
int lengthstr; // The length of the string entered!

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  while (!Serial) {

  }
  Serial.println("Code is starting!");



}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(strstuff[0]);
  if (Serial.available()) {
    //now you run code after you've entered that dumb string.
    lengthstr = strstuff.length();
    i = 0;
    x = 0;
    y = 0;

    while (i < lengthstr) {
      if (strstuff[i] == 'G') {
        //the character is G

        if (isDigit(strstuff[i + 1])) {
          //There is a digit after G
          

        }
        else {
          i++;
        }

      }
      else if (strstuff[i] == 'X') {
        if (isDigit(strstuff[i + 1])) {
          i++;
          while (isDigit(strstuff[i]) || strstuff == '.') {
            xval += strstuff[i];
            i++;
          }

        }
      }

      else if (strstuff[i] == 'Y') {
        if (isDigit(strstuff[i + 1])) {
          i++;
          while (isDigit(strstuff[i]) || strstuff == '.') {
            yval += strstuff[i];
            i++;
          }
        }

        else if (strstuff[i] == 'Z') {
          if (isDigit(strstuff[i + 1])) {
            i++;
            while (isDigit(strstuff[i]) || strstuff == '.') {
              zval += strstuff[i];
              i++;
            }
          }
        }



      }


    }
  }
}
