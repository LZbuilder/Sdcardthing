#include <Wire.h>


int lukaval = 1;
boolean doingcode = false;
double xval = 0;
double yval = 0;

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
// Stepper1.step((i/5.661111)*96);     set i to the value that you want the stepper to rotate when it is in the assambly, when using just the stepper devide i by three


void loop() {

}
void receiveEvent(int howmany) {
  Serial.println("Recieved");
  while (Wire.available()) {
    if (lukaval == 1) {
      String lukastring = "";
      lukastring = String(Wire.read());
      lukastring += ".";
      lukastring += String(Wire.read());
      xval = lukastring.toDouble();
      lukaval = 2;

    }
    else {
      String lukastring = "";
      lukastring = String(Wire.read());
      lukastring += ".";
      lukastring += String(Wire.read());
      yval = lukastring.toDouble();
      lukaval = 1;
    }

  }
  //Alexanders Code
  xValue = xval;
  yValue = yval;
  double stepperNewdeg = ((atan(xValue / yValue) * 180 / 3.14159265) + 0); // caclulate how much the stepper neews t move
  double servoNewdeg = (atan(Bedheight / yValue) * 180 / 3.14159265); // caclulate how much the servo needs to move
  stepperCalculateddeg = stepperNewdeg - stepperPreviousdeg; // how far the stepper needs to move in degrees
  servoCalculateddeg = servoNewdeg - servoPreviousdeg;
  Serial.println(stepperNewdeg - stepperPreviousdeg);

  // their are four possibilitys,
  //the stepper rotates clockwise and the servo degree of the servo decrespperCalculateddeg<0 & servoCalculateddeg<servoPreviousdeg
  //the stepper rotates clockwise and the degree of the servo increses,                       stepperCalculateddeg<0 & servoCalculateddeg>servoPreviousdeg
  //the stepper rotates counterclockwise and the degree of the servo increses         stepperCalculateddeg<0 & servoCalculateddeg<servoPreviousdeg
  //the stepper rotates counterclockwise and the degree of the servo decreses

  if (stepperCalculateddeg > 0 && servoCalculateddeg > servoPreviousdeg); { // the calculated value for the stepper is more than 0 go forwards,the calculated value for the stepper is more than the last value make the angle more
    Serial.println("stepper moving counter clock wise");
    Serial.println("degree of the servo should eb getting higher");
    // speed = distance/time
    // do the formula so the stepper arrives to stepperCalculateddeg the same time the servo arrives to servoCalculateddeg

  }
  //  servoy.write(yD);
  stepperPreviousdeg = stepperNewdeg; // sets the steppers previous degre to the last degre used
  servoPreviousdeg = servoNewdeg; // does the same but for the servo
  
}
