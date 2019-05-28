#include <Servo.h>
#include <NewPing.h>

const int ECHOPIN = A3;
const int TRIGPIN = A2;

const int MOTORLEFT = 12;
const int MOTORRIGHT = 13;
const int pwmLeft = 3;
const int pwmRight = 11;
const int brakeLeft = 9;
const int brakeRight = 8;

const int MAXSPEED = 180;
const int MAXDISTANCE = 200;

boolean start=true;
boolean goesForward = false;
int distance = 100;



NewPing sonar(A2, A3, MAXDISTANCE);
Servo servo_5;


void setup()
{
    pinMode(MOTORLEFT, OUTPUT);
    pinMode(MOTORRIGHT, OUTPUT);
    pinMode(pwmLeft, OUTPUT);
    pinMode(pwmRight, OUTPUT);
    pinMode(brakeLeft, OUTPUT);
    pinMode(brakeRight, OUTPUT);
    digitalWrite(brakeLeft, 0);
    digitalWrite(brakeRight, 0);
    
    servo_5.attach(5);
    
    
}

void loop()
{
    if(start)
    {
      start=false;
      servo_5.write(90);
      delay(2000);
      distance = readPing();
      delay(100);
      distance = readPing();
      delay(100);
      distance = readPing();
      delay(100);
      distance = readPing();
      delay(100);
    }
    
    int distanceRight = 0;
    int distanceLeft = 0;
    delay(40);

    if (distance <= 20)
    {
        moveStop();
        delay(100);
        moveBackwards();
        delay(300);
        moveStop();
        delay(200);
        distanceRight = lookRight();
        delay(200);
        distanceLeft = lookLeft();
        delay(200);

        if (distanceRight >= distanceLeft)
        {
            turnRight();
            moveStop();
        }
        else
        {
            turnLeft();
            moveStop();
        }
    }
    else
    {
        moveForward();
    }
    distance = readPing();
}

int readPing()
{
    delay(70);
    int cm = sonar.ping_cm();
    if (cm == 0)
    {
        cm = 250;
    }
    return cm;
}

void moveStop()
{
    analogWrite(pwmLeft, 0);
    analogWrite(pwmRight, 0);
}

void turnRight()
{
    digitalWrite(MOTORLEFT, HIGH);
    digitalWrite(MOTORRIGHT, HIGH);
    analogWrite(pwmLeft, MAXSPEED);
    analogWrite(pwmRight, MAXSPEED);
}

void turnLeft()
{
    digitalWrite(MOTORLEFT, LOW);
    digitalWrite(MOTORRIGHT, LOW);
    analogWrite(pwmLeft, MAXSPEED);
    analogWrite(pwmRight, MAXSPEED);
}

void moveForward()
{
    if (!goesForward)
    {
        goesForward = true;
        digitalWrite(MOTORLEFT, LOW);
        digitalWrite(MOTORRIGHT, HIGH);
        for (size_t speed = 0; speed < MAXSPEED; speed++)
        {
            analogWrite(pwmLeft, speed);
            analogWrite(pwmRight, speed);
            delay(5);
        }
    }
}

void moveBackwards()
{
    goesForward = false;
    digitalWrite(MOTORLEFT, HIGH);
    digitalWrite(MOTORRIGHT, LOW);

    for (size_t speed = 0; speed < MAXSPEED; speed++)
    {
        analogWrite(pwmLeft, speed);
        analogWrite(pwmRight, speed);
        delay(5);
    }
}

int lookLeft()
{
    servo_5.write(10);
    delay(500);
    distance = readPing();
    delay(100);
    servo_5.write(90);
    
    return distance;
}

int lookRight()
{
    servo_5.write(170);
    delay(500);
    distance = readPing();
    delay(100);
    servo_5.write(90);
    
    return distance;
}
