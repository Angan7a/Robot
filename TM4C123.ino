#include <Servo.h>

#define ServoPin 26 // PD3 servo

#define Trig 5 // PE4, distance sensor
#define Echo 6 // PE6, distance sensor

#define AxIN1 7 // PB4, motor 1
#define AxIN2 2 // PB5, motor 1
#define BxIN1 37 // PC4, motor 2
#define BxIN2 36 // PC5, motor 2
#define Mode 11 // PA2, mode 

#define B 8 // PA5  -> pin 5 on ESP8266, communication
#define B1 9 // PA6  -> pin 14 on ESP8266, communication
#define B2 10 // PA7  -> pin 16 on ESP8266, communication

int speed = 500;
bool forward = HIGH;
Servo servo;
int pos = 90;   

void setup() {                
      // initialise GPIO
     pinMode(AxIN1, OUTPUT);     
     pinMode(AxIN2, OUTPUT);     
     pinMode(BxIN1, OUTPUT);     
     pinMode(BxIN2, OUTPUT);     
     pinMode(Mode, OUTPUT);     
     digitalWrite(Mode, LOW);
     pinMode(B, INPUT);
     pinMode(B1, INPUT);
     pinMode(B2, INPUT);
     pinMode(Trig, OUTPUT);
     pinMode(Echo, INPUT);
     servo.attach(ServoPin);
     stop();
}

void loop() {
    controlByRobot();
}


void stop(void)
{
    digitalWrite(AxIN1, 1);
    digitalWrite(AxIN2, 1);
    digitalWrite(BxIN1, 1);
    digitalWrite(BxIN2, 1);
}
void drive(void)
{
    analogWrite(AxIN1, speed);
    digitalWrite(AxIN2, 0);
    analogWrite(BxIN1, speed);
    digitalWrite(BxIN2, 0);
}
void reverse(void)
{
    digitalWrite(AxIN1, 0);
    analogWrite(AxIN2, speed);
    digitalWrite(BxIN1, 0);
    analogWrite(BxIN2, speed);
}
void left(int time = 500)
{
    if (forward == HIGH)
    {
        analogWrite(AxIN1, speed );
        digitalWrite(AxIN2, 0);
        digitalWrite(1);
        digitalWrite(1);
    } else {
        digitalWrite(1);
        digitalWrite(1);
        digitalWrite(BxIN1, 0);
        analogWrite(BxIN2, speed);
    }
    delay(time);
}
void right(int time = 500)
{
    if (forward == HIGH)
    {
        digitalWrite(1);
        digitalWrite(1);
        analogWrite(BxIN1, speed);
        digitalWrite(BxIN2, 0);
    } else {
        digitalWrite(AxIN1, 0);
        analogWrite(AxIN2, speed);
        digitalWrite(1);
        digitalWrite(1);
    }
    delay(time);
}
void clockwise(int time)
{
    digitalWrite(1);
    digitalWrite(1);
    digitalWrite(BxIN1, 0);
    analogWrite(BxIN2, speed);
    delay(time);
    stop();
}

void cClockwise(int time)
{
    digitalWrite(1);
    digitalWrite(1);
    analogWrite(BxIN1, speed);
    digitalWrite(BxIN2, 0);
    delay(time);
    stop();
}

int rotate(int z, int step = 10)
{
    int min = 1800;
    int posMin = 90;
    while (pos > 90 - z)
    {
        pos = pos - step;
        servo.write(pos);
        delay(50);
        int d = distance();
        if (d < min)
        {
          min = d;
          posMin = pos;
        }
        //delay(150);
    }
    while (pos < 90 + z)
    {
        pos = pos + step;
        servo.write(pos);
        delay(50);
        int d = distance();
        if (d < min)
        {
          min = d;
          posMin = pos;
        }
        //delay(150);
    }
    return posMin;
}
int distance(void)
{
    digitalWrite(Trig, LOW);
    delayMicroseconds(2);
    digitalWrite(Trig, HIGH);
    delayMicroseconds(15);
    digitalWrite(Trig, LOW);
    digitalWrite(Echo, HIGH); 
    return pulseIn(Echo, HIGH) / 58;
}
void controlByWiFi(void)
{
    while(1)
    {
        bool b0 = digitalRead(B);
        bool b1 = digitalRead(B1);
        bool b2 = digitalRead(B2);
        if (b2 == LOW && b1 == LOW && b0 == LOW)
        {
            stop();
        } else if (b2 == LOW && b1 == LOW && b0 == HIGH)
        {
            //Slower
            speed -= 100;
        } else if (b2 == LOW && b1 == HIGH && b0 == LOW)
        {
            //Faster
            speed += 100;
        } else if (b2 == LOW && b1 == HIGH && b0 == HIGH)
        {
            right();
        } else if (b2 == HIGH && b1 == HIGH && b0 == LOW)
        {
            left();
        } else if (b2 == HIGH && b1 == LOW && b0 == HIGH)
        {
            revers(speed);
            forward = LOW;
        } else if (b2 == HIGH && b1 == LOW && b0 == LOW)
        {
            drive(speed);
            forward = HIGH;
        }
        stop();
    }
}
void controlByRobot(void)
{
    while(1)
    {
        do
        {
            stop();
            reverse();
            delay(100);
            clockwise(500);
            int r = rotate(90);
            servo.write(r);
            int time = 500;
            while (80 > r && r > 100)
            {
                if (r < 90)
                {
                    clockwise(time); 
                    r = rotate(90);
                    servo.write(r);
                    time /= 2;
                }
                if (r > 90)
                {
                    cClockwise(time); 
                    r = rotate(90);
                    servo.write(r);
                    time /= 2;
                }
            }
            servo.write(90);
            drive();
        }
        while(rotate(30, 5) > 50);
}
