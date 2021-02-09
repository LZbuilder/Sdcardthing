
#include <Stepper.h>
#include <Servo.h>
Servo servoy;

int Bedheight = 60;//the height of the centerpoint of the rotating on the Y servo from the print bed
double xValue = 20;// the numbers followed after G1  (example G1 X___ Y)
double yValue = 20;// the numbers followed after G1 X (example G1 X Y___)
int repeatamount = 1;
int i = 0;

//  ↑ varibles used by evreything

int stepsPerRevolution = 2038;

double stepperNewdeg = 0;
double stepperCalculateddeg = 0;
double stepperPreviousdeg = 0;
double stepperCurrentpos = 0;
double steppersteps = 0; //im not sure what else to call this var but its the one that is divided by repeatamount to make the stepper and servo arrive to their disired degress at the same time

//  ↑ varibles used by the stepper motors

double servoNewsdeg = 0 ;// the new degree for the servo,formaly called yD
double servoCalculateddeg = 0;
double servoPreviousdeg = 0;
double servoCurrentpos = 0;
double servosteps = 0; //im not sure what else to call this var but its the one that is divided by repeatamount to make the stepper and servo arrive to their disired degress at the same time
//  ↑ varibles used by the spinnig servomotor


Stepper Stepper1(stepsPerRevolution, 7, 5, 6, 8);

void setup() {


  Serial.begin(9600);

  Stepper1.setSpeed(5); //rpms
  servoy.attach(9);

  servoy.write(0);
  servoCurrentpos = 0;
}


// Stepper1.step((i/5.661111)*96);     set i to the value that you want the stepper to rotate when it is in the assambly, when using just the stepper devide i by three


void loop() {
  double stepperNewdeg = ((atan(xValue / yValue) * 180 / 3.14159265) + 0); // caclulate how much the stepper neews t move
  double servoNewdeg = (atan(Bedheight / yValue) * 180 / 3.14159265); // caclulate how much the servo needs to move
  stepperCalculateddeg = stepperNewdeg - stepperPreviousdeg; // how far the stepper needs to move in degrees
  servoCalculateddeg = servoNewdeg - servoPreviousdeg;
  Serial.println(stepperNewdeg - stepperPreviousdeg);

  // their are four possibilitys,
  //the stepper rotates clockwise and the servo rotates counterclockwise              stepperCalculateddeg>0 & servoCalculateddeg<servoPreviousdeg
  //the stepper rotates clockwise and the servo rotates clockwise                     stepperCalculateddeg>0 & servoCalculateddeg>servoPreviousdeg
  //the stepper rotates counterclockwise and the servo rotates counterclockwise       stepperCalculateddeg<0 & servoCalculateddeg<servoPreviousdeg
  //the stepper rotates counterclockwise and the servo rotates clockwise              stepperCalculateddeg<0 & servoCalculateddeg>servoPreviousdeg

  if (stepperCalculateddeg > 0 && servoCalculateddeg > servoPreviousdeg); { // the calculated value for the stepper is more than 0 go forwards,the calculated value for the stepper is more than the last value make the angle more
    Serial.println("stepper moving clock wise");
    Serial.println("servo moving clockwise");

// this is the part i need you to do for me
    steppersteps = (stepperCalculateddeg/repeatamount); // not a problem
    servosteps = (servoCalculatedgeg/repeatamount); //all good
    for(int i = 0; i < repeatamount; i++){
      // i dont want to learn how to use one of these 
    
    
    Stepper1.step((steppersteps/5.661111)*96);
    servoy.write()//i dont know how to make this work but its sopposed to be servo steps times i

      
    
    
    // speed = distance/time


    //end the loop and set i to zero. What its sopposed to do is repeat that loop repeatamount times 
    }
  }
  xValue = random(0, 200);
  yValue = random(0, 200);



  // dont touch 
  stepperPreviousdeg = stepperNewdeg; // sets the steppers previous degre to the last degre used
  servoPreviousdeg = servoNewdeg; // does the same but for the servo
}
