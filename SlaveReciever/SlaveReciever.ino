#include <Wire.h>
#define SLAVE_ADDR 4
#define ANSWERSIZE 4

int lukaval = 1;
boolean doingcode = false;
double xval = 0;
double yval = 0;
double zval = 0;
short numberofrequest = 0;

/*Alexanders Values */

#include <Stepper.h>
#include <Servo.h>
Servo servoy;

int Bedheight = 60;//the height of the centerpoint of the rotating on the Y servo from the print bed
double xValue = 20;// the numbers followed after G1  (example G1 X___ Y)
double yValue = 20;// the numbers followed after G1 X (example G1 X Y___)
int time = 1;

//  ↑ varibles used by evreything

int stepsPerRevolution = 2038;

double stepperNewdeg = 0;
double stepperCalculateddeg = 0;
double stepperPreviousdeg = 0;
double stepperCurrentpos = 0;

//  ↑ varibles used by the stepper motors

double servoNewsdeg = 0 ;// the new degree for the servo,formaly called yD
double servoCalculateddeg = 0;
double servoPreviousdeg = 0;
double servoCurrentpos = 0;
//  ↑ varibles used by the spinnig servomotor










void setup() {
  Wire.begin(SLAVE_ADDR);                // join i2c bus with address #4
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent); // register event
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  delay(500);
  digitalWrite(9, HIGH);    // turn the LED off by making the voltage LOW
  digitalWrite(8, HIGH);
  delay(500);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);


  /* Alexanders setup code */

  Stepper1.setSpeed(5); //rpms
  servoy.attach(9);

  servoy.write(0);
  servoCurrentpos = 0;


  
}


void loop() {

}
void receiveEvent(int howmany) {
  while (Wire.available()) {
    if (lukaval == 1) {
      String lukastring = String(Wire.read());
      lukastring += ".";
      lukastring += String(Wire.read());
      xval = lukastring.toDouble();
      lukaval = 2;
      digitalWrite(8, HIGH);   // turn the LED on (HIGH is the voltage level)

    }
    else {
      String lukastring = String(Wire.read());
      lukastring += ".";
      lukastring += String(Wire.read());
      yval = lukastring.toDouble();
      lukaval = 1;
      digitalWrite(9, HIGH);
    }

    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
  }
  //Alexanders Code
  
}
