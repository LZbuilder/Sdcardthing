#include <SPI.h>
#include <SD.h>

File myFile;



//work in progres
String strstuff = "G23 X42 Y54.245   Z4; E31; ";
String g;
String gval = "";
String xval = "";
String yval = "";
double x; //end result of what comes after x
double y; //end result of what comes after y
char singleletterchar; int singleletterint;
String multiple[] = {};
int i;
int lengthstr;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  while (!Serial) {
    ; //Wait for serial monitor to be opened
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }

  Serial.println("initialization done.");

  //open file for reading
  myFile = SD.open("gcode.txt");

  if (myFile) {
    Serial.println("gcode.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {

      singleletterint = myFile.read();
      singleletterchar = char(singleletterint);
      

    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  //nothing!


}
