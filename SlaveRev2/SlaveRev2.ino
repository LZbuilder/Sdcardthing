#include <Wire.h>


int lukaval = 1;
boolean doingcode = false;
double xval = 0;
double yval = 0;
String x = "";
String y = "";
char character = "";

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

Stepper Stepper1(stepsPerRevolution, 7, 5, 6, 8);

void setup() {
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);
  /* Alexanders setup code */
  delay(100);
  Serial.println("Slave Ready To Print!!!");
  Stepper1.setSpeed(5); //rpms
  servoy.attach(9);

  servoy.write(0);
  servoCurrentpos = 0;
}

void loop() {}

void receiveEvent(int howmany) {
    Serial.println("Recieved");
    character = Wire.read();
    switch (character){
        case 'G':
            
            break;
        case 'X':
        break;
        case 'Y':
        break;
        case 'Z':
        break;

    }







}
