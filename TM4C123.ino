#define AxIN1 PE4
#define AxIN2 PE5
#define BxIN1 PC4
#define BxIN2 PC5

#define B PA5   // pin 5 on ESP8266
#define B1 PA6  // pin 14 on ESP8266
#define B2 PA7  // pin 16 on ESP8266

#define M PA2

int intenso = 500;
int delta = 100;

void setup() {                
      // initialise GPIO
     pinMode(AxIN1, OUTPUT);     
     pinMode(AxIN2, OUTPUT);     
     pinMode(BxIN1, OUTPUT);     
     pinMode(BxIN2, OUTPUT);     
     pinMode(M, OUTPUT);     
     digitalWrite(M, LOW);
     pinMode(B, INPUT_PULLUP);
     pinMode(B1, INPUT_PULLUP);
     pinMode(B2, INPUT_PULLUP);
}

void loop() {
    if (digitalRead(B2) == LOW &&
        digitalRead(B1) == LOW &&
        digitalRead(B) == LOW)
    {
        //stop
        digitalWrite(AxIN1, 1);
        digitalWrite(AxIN2, 1);
        digitalWrite(BxIN1, 1);
        digitalWrite(BxIN2, 1);
    } else if (digitalRead(B2) == LOW &&
        digitalRead(B1) == LOW &&
        digitalRead(B) == HIGH)
    {
        //Slower
        intenso -= delta;
    } else if (digitalRead(B2) == LOW &&
        digitalRead(B1) == HIGH &&
        digitalRead(B) == LOW)
    {
        //Faster
        intenso += delta;
    } else if (digitalRead(B2) == LOW &&
        digitalRead(B1) == HIGH &&
        digitalRead(B) == HIGH)
    {
        //Right
        digitalWrite(AxIN1, 0);
        analogWrite(AxIN2, intenso);
        digitalWrite(BxIN1, 1);
        digitalWrite(BxIN2, 1);

    } else if (digitalRead(B2) == HIGH &&
        digitalRead(B1) == HIGH &&
        digitalRead(B) == LOW)
    {
        //Left
        digitalWrite(AxIN1, 1);
        digitalWrite(AxIN2, 1);
        digitalWrite(BxIN1, 0);
        analogWrite(BxIN2, intenso);
    } else if (digitalRead(B2) == HIGH &&
        digitalRead(B1) == LOW &&
        digitalRead(B) == HIGH)
    {
        //Revers
        digitalWrite(AxIN1, 0);
        analogWrite(AxIN2, intenso);
        digitalWrite(BxIN1, 0);
        analogWrite(BxIN2, intenso);
    } else if (digitalRead(B2) == HIGH &&
        digitalRead(B1) == LOW &&
        digitalRead(B) == LOW)
    {
        //Drive
        analogWrite(AxIN1, intenso);
        digitalWrite(AxIN2, 0);
        analogWrite(BxIN1, intenso);
        digitalWrite(BxIN2, 0);
    }
    delay(1000);
}

