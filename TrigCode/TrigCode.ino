#include <MatrixMath.h>
#include <Servo.h>
Servo servoBase;
Servo servoLinkage;

#define lOne 100 //REMEMBER lONE and lTwo must be equal to eachother
#define lTwo 100 //REMEMBER lONE and lTwo must be equal to eachother

double xdis = 60;
double ydis = 40;
float c = sqrt(sq(xdis) + sq(ydis));
float gamma = acos((sq(lOne) + sq(c) - sq(lTwo)) / (2 * lOne * c));
float beta = 180 - (2 * gamma);
void setup()
{
    Serial.begin(115200);
    while (!Serial){
        ;
    }
    // put your setup code here, to run once:
    servoBase.attach(9);
    servoLinkage.attach(8);
    servoBase.write(0);
    servoLinkage.write(0);
}

void loop()
{
    // put your main code here, to run repeatedly:
    if (xdis >= 0 && ydis >= 0)
    {
        //then do alexanders code
        c = sqrt(sq(xdis) + sq(ydis));
        gamma = acos((sq(lOne) + sq(c) - sq(lTwo)) / (2 * lOne * c));
        beta = 180 - (2 * gamma);
        Serial.println(gamma);
        Serial.println(beta);
        servoBase.write(gamma);
        servoLinkage.write(beta);
    }
}