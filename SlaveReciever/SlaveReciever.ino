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

  Stepper1.setSpeed(5);
  servoy.attach(9);
  servoy.write(90);
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);
}

void loop() {
  double rawdeg = ((atan(xValue / yValue) * 180 / 3.14159265) + 0);
  calculateddeg = rawdeg - previousdeg;
  degdiff = abs(calculateddeg);
  Stepper1.setSpeed(pow((degdiff / ), 1.00001));
  Stepper1.step(((calculateddeg / 5.661111) * 32) * 3);

  double yD = (atan(Bedheight / yValue) * 180 / 3.14159265);
  servoy.write(yD);
  //xValue = random(0,200);
  //yValue = random(0,200);
  previousdeg = calculateddeg;
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
