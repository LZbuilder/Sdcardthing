#include <Wire.h>

char lukaval;
boolean doingcode = false;
double xval = 0;
double yval = 0;
String x = "";
String y = "";
char character;

/*Alexanders Values */

void setup()
{
    Wire.begin(4);                // join i2c bus with address #4
    Wire.onReceive(receiveEvent); // register event
    Serial.begin(9600);
    /* Alexanders setup code */
    delay(100);
    Serial.println("Slave Ready To Print!!!");
}

void loop() {}

void receiveEvent(int howmany)
{
    Serial.println("Recieved");
    character = Wire.read();
    switch (character)
    {
    case 'G':
        Serial.println("G found");
        break;
    case 'X':
        Serial.println("X found");
        break;
    case 'Y':
        Serial.println("Y found");
        break;
    case 'Z':
        Serial.println("Z found");
        break;
        if (isDigit(character))
        {
            Serial.println("Digit found");
            break;
        }
    }
}
