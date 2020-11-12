#include <Wire.h>
#include <Stepper.h>
#include <Servo.h>
Servo servoy;
boolean lukaval = true;
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
  Serial.begin(9600);
  Stepper1.setSpeed(5);
  servoy.attach(9);
  servoy.write(0);
  servoCurrentpos = 0;
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
}


void loop() {
  double stepperNewdeg = ((atan(xValue / yValue) * 180 / 3.14159265) + 0); // caclulate how much the stepper neews t move
  double servoNewdeg = (atan(Bedheight / yValue) * 180 / 3.14159265); // caclulate how much the servo needs to move
  stepperCalculateddeg = ((((stepperNewdeg - stepperPreviousdeg) / 5.661111) * 32) * 3); // how far the stepper needs to move in degrees
  servoCalculateddeg = servoNewdeg - servoPreviousdeg;
  Serial.println(stepperNewdeg - stepperPreviousdeg);

  Stepper1.step(stepperCalculateddeg);
  if ((stepperCalculateddeg > 0 ) && (servoCalculateddeg > servoPreviousdeg)); { // the calculated value for the stepper is more than 0 go forwards,the calculated value for the stepper is more than the last value make the angle more
    Serial.println("moving counter clock wise");
    // speed = distance/time
    for (stepperCurrentpos = 0; stepperCurrentpos <= 180; stepperCurrentpos += 1) //not sure how to make it work but,while the steppers current pos is less than the desired pos make it go up
    {


    }
  }
  //  servoy.write(yD);
  //xValue = random(0, 200);
  //yValue = random(0, 200);
  stepperPreviousdeg = stepperNewdeg; // sets the steppers previous degre to the last degre used
  servoPreviousdeg = servoNewdeg; // does the same but for the servo
}
void receiveEvent() {
  if (lukaval) {
    String lukastring = String(Wire.read());
    lukastring += ".";
    lukastring += Wire.read();
    xValue = lukastring.toDouble();
    lukaval = false;
  }
  if (!lukaval) {
    String lukastring = String(Wire.read());
    lukastring += ".";
    lukastring += Wire.read();
    yValue = lukastring.toDouble();
    lukaval = true;

  }
}
