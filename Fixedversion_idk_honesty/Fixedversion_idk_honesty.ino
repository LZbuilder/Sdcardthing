#include <SPI.h>
#include <SD.h>
File myFile;



//work in progres
String strstuff = "G23 X42 Y54.245   Z4; E31; ";
String g;
String gval;
String xval = "";
String yval = "";
double x; //end result of what comes after x
double y; //end result of what comes after y
int i;
int lengthstr;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  while (!Serial){
    
  }
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  //open file for reading
  if (myFile) {
    Serial.println("gcode.txt:");
 
    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening gcode.txt");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(strstuff[0]);
  if (Serial.available()){
    //now you run code after you've entered that dumb string.
    lengthstr = strstuff.length();
    i = 0;
    x = 0;
    y = 0;
    
    while (i<=lengthstr){
      if (strstuff[i] == 'G'){
        
        if (isDigit(strstuff[i + 1])){
          i++;
          while (isDigit(i)) {
            
            i++;
          }
        }
        else{
          i++;
        }
        
      }
      else if (strstuff[i] == 'X'){
        if (isDigit(strstuff[i + 1])){
          //the character after X is a digit
          i++;
          while (isDigit(i)){
            
          }
        }
      }
      else if (strstuff[i] == 'Y'){
        
      }
      
      
      
    }
  }
  

}
