#include <MatrixMath.h>
#include <Servo.h>
Servo servoBase;
Servo servoLinkage;

#define lOne 1000 //REMEMBER lONE and lTwo must be equal to eachother
#define lTwo 1000 //REMEMBER lONE and lTwo must be equal to eachother

double xpos = 60.13;
double ypos = 40.41;
float c = sqrt(sq(xpos) + sq(ypos));
float gamma = acos((sq(lOne) + sq(c) - sq(lTwo)) / (2 * lOne * c));
float beta = 180 - (2 * gamma);
void setup()
{
    Serial.begin(9600);
    while (!Serial){
        ;
    }
    // put your setup code here, to run once:
    servoBase.attach(2);
    servoLinkage.attach(3);
    servoBase.write(0);
    servoLinkage.write(0);
}

void loop()
{
    xpos = random(0, 499);
    ypos = random(0, 499);
    Serial.println(xpos);
    Serial.println(ypos);
    // put your main code here, to run repeatedly:
    if (xpos >= 0 && ypos >= 0)
    {
        //then do alexanders code
        c = sqrt(sq(xpos) + sq(ypos));
        gamma = acos(((sq(lOne) + sq(c)) - sq(lTwo)) / (2 * lOne * c));
        beta = 180 - (2 * gamma);
        Serial.println(gamma);
        Serial.println(beta);
        servoBase.write(gamma);
        servoLinkage.write(beta);
        delay(1000);    
    }
}