#include <Wire.h>
#include <Stepper.h>
#include <Servo.h>

boolean lukaval = true;

Servo servoy;
int stepsPerRevolution = 2038;
int Bedheight = 60;//the height of the centerpoint of the rotating on the Y servo from the print bed
double xValue = 20;// the numbers followed after G1  (example G1 X Y)
double yValue = 20;// the numbers followed after G1 X (example G1 X Y)
double rawdeg = 0;
double calculateddeg = 0;
double previousdeg = 0;
double degdiff = 0;  //degree diffrence,useful for calculating if we need to move slow or fast,also the ablsoute value of calculateddeg
Stepper Stepper1(stepsPerRevolution, 7, 5, 6, 8);
void setup() {
  Stepper1.step(0);
  // put your setup code here, to run once:
  Serial.begin(9600);

<<<<<<< HEAD
<<<<<<< Updated upstream
Stepper1.setSpeed(5);
servoy.attach(9);

servoy.write(0);
servoCurrentpos = 0;
=======
  Stepper1.setSpeed(5);
  servoy.attach(9);
  servoy.write(90);
>>>>>>> parent of 8f49a83... Update SlaveReciever.ino
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);
}

void loop() {
<<<<<<< HEAD
  double stepperNewdeg = ((atan(xValue/yValue)*180/3.14159265)+0);// caclulate how much the stepper neews t move
  double servoNewdeg = (atan(Bedheight / yValue)*180 / 3.14159265); // caclulate how much the servo needs to move
  stepperCalculateddeg = ((((stepperNewdeg-stepperPreviousdeg)/5.661111)*32)*3); // how far the stepper needs to move in degrees
  servoCalculateddeg = servoNewdeg - servoPreviousdeg;
  Serial.println(stepperNewdeg-stepperPreviousdeg);
   
    Stepper1.step(stepperCalculateddeg);
  if ((stepperCalculateddeg > 0 )&& (servoCalculateddeg > servopreviousdeg));{ // the calculated value for the stepper is more than 0 go forwards,the calculated value for the stepper is more than the last value make the angle more
  Serial.println("moving counter clock wise");
  // speed = distance/time 
<<<<<<< HEAD
    for (Steppercurrentpos = 0; pos <= 180; pos += 1){ //not sure how to make it work but,while the steppers current pos is less than the desired pos make it go up
    }
=======
void loop() {
  double rawdeg = ((atan(xValue / yValue) * 180 / 3.14159265) + 0);
  calculateddeg = rawdeg - previousdeg;
  degdiff = abs(calculateddeg);
  //Stepper1.setSpeed(pow((degdiff / ), 1.00001));
=======
  double rawdeg = ((atan(xValue / yValue) * 180 / 3.14159265) + 0);
  calculateddeg = rawdeg - previousdeg;
  degdiff = abs(calculateddeg);
  Stepper1.setSpeed(pow((degdiff / ), 1.00001));
>>>>>>> parent of 8f49a83... Update SlaveReciever.ino
  Stepper1.step(((calculateddeg / 5.661111) * 32) * 3);

  double yD = (atan(Bedheight / yValue) * 180 / 3.14159265);
  servoy.write(yD);
  //xValue = random(0,200);
  //yValue = random(0,200);
  previousdeg = calculateddeg;
<<<<<<< HEAD
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
    lukastring += String(Wire.read());
    yValue = lukastring.toDouble();
    lukaval = true;
>>>>>>> Stashed changes
=======
    for (Steppercurrentpos = 0; pos <= 180; pos += 1) //not sure how to make it work but,while the steppers current pos is less than the desired pos make it go up
>>>>>>> parent of 65dd970... Update SlaveReciever.ino
  }
//  servoy.write(yD);
  xValue = random(0,200);
  yValue = random(0,200);
 stepperPreviousdeg = stepperNewdeg; // sets the steppers previous degre to the last degre used
 servoPreviousdeg = servoNewdeg; // does the same but for the servo
=======
>>>>>>> parent of 8f49a83... Update SlaveReciever.ino
}

void receiveEvent() {
  if (lukaval) {
    String lukastring = Wire.read();
    lukastring += Wire.read();
    xValue = lukastring.toDouble();
    lukaval = false;
  }
  if (!lukaval) {
    String lukastring = Wire.read();
    lukastring += Wire.read();
    yValue = lukastring.toDouble();
    lukaval = true;
  }
}
