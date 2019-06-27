#include <SoftwareSerial.h>

int red = 10;
int yellow = 9;
int green = 8;

void setup() {
    pinMode(red, OUTPUT);
    pinMode(yellow, OUTPUT);
    pinMode(green, OUTPUT);

    Serial.begin(9600);
    Serial.println("r = red, y = yellow, g = green, o = off");
}

void loop() {
    char color = 'b'; //initialize as non-option
    color = Serial.read();
    switch(color) {
      case 'r':
        redLight();
        Serial.println("red");
        break;
      case 'y':
        yellowLight();
        Serial.println("yellow");
        break;
      case 'g':
        greenLight();
        Serial.println("green");
        break;
      case 'o':
        lightsOff();
        break;
    }
}

void redLight() {
    //turn red light on and others off
    digitalWrite(green, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(red, HIGH);
}

void greenLight() {
    //turn green light on and others off
    digitalWrite(green, HIGH);
    digitalWrite(yellow, LOW);
    digitalWrite(red, LOW);
}

void yellowLight() {
    //turn yellow light on and others off
    digitalWrite(green, LOW);
    digitalWrite(yellow, HIGH);
    digitalWrite(red, LOW);
}
void lightsOff() {
    //turn yellow light on and others off
    digitalWrite(green, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(red, LOW);
}

