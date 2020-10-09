/*
 * Now I must make an
 * annoying ass piece of
 * code for my friend
 * 
 * to begin I need to look
 */

/*
 * https://www.arduino.cc/en/Reference/SDCardNotes
 * Notes: 
 *  here are the pins a nano uses digital pins 11, 12, and 13.
 *  While the Mega uses 50, 51, and 52
 *  Arduino Micro uses pins 14, 15, and 16.
 *  Additionally, another pin must be used to select the SD card
 *  You must use the 8.3 format when naming the sd card!!!
 *    EXAMPLE "NAME001.EXT" where “NAME001” is an 
 *    8 character or fewer string, and “EXT” is a 3 
 *    character extension
 *  
 */

#include <SPI.h>
#include <SD.h>
File myFile;
 

void setup() {
  // put your setup code here, to run once:


  
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect
    
  }
  Serial.println("Starting shit");

  if (!SD.begin(4)){ // you can add a parameter to specify the chipselect-pin which is defaulted as 10
    Serial.println("true");
  }
  if(SD.exists("gcode.txt")){
    Serial.println("gcode.txt exists!!");
    
  }

  //read from file
  myfile = SD.open("gcode.txt", FILE_READ);
  Serial.println("trying to read this shit.");
  while (myFile.available()){
    Serial.write(myFile.read());
    
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
