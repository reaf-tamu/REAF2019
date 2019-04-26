#include <Servo.h>
#include <SoftwareSerial.h>

//TO COMPILE THE SKETCH AND CHECK FOR ERRORS, CLICK THE CHECK MARK ABOVE
//TO RUN THE SKETCH, CLICK THE RIGHT POINTING ARROW BUTTON ABOVE TO UPLOAD THE CODE TO THE NUC
//WHEN IT SAYS UPLOAD COMPLETE AT THE BOTTOM OF THE SCREEN, TURN ON THE THRUSTERS AND CLICK THE CHECK BUTTON TO RUN IT

//TO TEST THE THRUSTER SPEEDS IN THE POOL, TRY RUNNING ONE FUNCTION AT A TIME
//TRY SEEING HOW THE STARTING 1600 SPEED WORKS AND IF IT IS TOO SLOW OR FAST, ALTAR THE VALUE A FEW LINES DOWN
//YOU CAN ALSO CHANGE THE DELAY TIME IN EACH FUNCTION WHICH WILL ALLOW THE THRUSTERS TO RUN FOR LONGER OR SHORTER AMOUNTS OF TIME
//BE CAREFUL NOT TO RUN THEM FOR TOO LONG SO IT DOESN'T RUN INTO ANYTHING
//IF THE AUV NEEDS TO BE STOPPED IMMEDIATLY, RUN THE STOP SKETCH IN THE STOP FOLDER OR HIT THE KILL SWITCH

//HERE YOU CAN SEE WHICH SERVO NUMBER REPRESENTS EACH THRUSTER
byte servoPin1 = 13; // Right Front   - pink
byte servoPin2 = 12; // Right Top          - red
byte servoPin3 = 11; // Right Back     - orange
byte servoPin4 = 10; // Left Front          - yellow
byte servoPin5 = 9; // Right Bottom              - green
byte servoPin6 = 7; // Left Bottom       - purple
byte servoPin7 = 6; // Left Back              - blue
byte servoPin8 = 5; // Left Top        - white

int MissionSwitch = 34;
int Mission = 0; 


int signal = 1650; // Set signal value, which should be between 1100 and 1900
int stop = 1500; // Stop thruster //1500-1900 positive 1100-1499 negative


Servo servo1; 
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
Servo servo7;
Servo servo8;

void setup() 
{
  
  servo1.attach(servoPin1); 
  servo2.attach(servoPin2); 
  servo3.attach(servoPin3); 
  servo4.attach(servoPin4); 
  servo5.attach(servoPin5); 
  servo6.attach(servoPin6); 
  servo7.attach(servoPin7); 
  servo8.attach(servoPin8); 

  //stop them all
  servo1.writeMicroseconds(1500); // send "stop" signal to ESC.
  servo2.writeMicroseconds(1500); // send "stop" signal to ESC.
  servo3.writeMicroseconds(1500); // send "stop" signal to ESC.
  servo4.writeMicroseconds(1500); // send "stop" signal to ESC.
  servo5.writeMicroseconds(1500); // send "stop" signal to ESC.
  servo6.writeMicroseconds(1500); // send "stop" signal to ESC.
  servo7.writeMicroseconds(1500); // send "stop" signal to ESC.
  servo8.writeMicroseconds(1500); // send "stop" signal to ESC.

  pinMode(MissionSwitch, INPUT); //Mission switch connection as input
  
  delay(1000); // delay to allow the ESC to recognize the stopped signal
  Serial.begin(9600);
  Serial.println("Directions (d=Down,h=hover,f=Forward,l=Left,s=slightleft,r=Right,t=slightright,u=Up,b=Backward,p=dice,g=straight)");
  

}

void loop() 
{
    
  Mission = digitalRead(MissionSwitch); // read Mission Switch input 
  char dir='t'; //direction
  if (Mission== HIGH)
  {

    //CHOOSE WHICH MOTIONS YOU WANT TO RUN HERE, COMMENT OUT THE ONES YOU DON'T WANT TO USE BY PLACING // IN FRONT OF IT
    //THE ACTUAL CODE FOR EACH FUNCTION IS FURTHER DOWN
    float sensorValue = analogRead(A0);
    float pressure = sensorValue/15.0;
    dir= Serial.read();
    switch(dir){
      case 'a':
        thruster1();
        Serial.println("1");
        break;
      case 'b':
         thruster2();
        Serial.println("2");
        break;
      case 'c':
        thruster3();
        Serial.println("3");
        break;
      case 'd':
        thruster4();
        Serial.println("4");
        break;
      case 'e':
        thruster5();
        Serial.println("5");
        break;
        
      case 'f':
        thruster6();
        Serial.println("6");
        break;
         
      case 'g':
        thruster7();
        Serial.println("7");
        break; 
      case 'h':
        thruster8();
        Serial.println("8");
        break;
      default:
        //hover();
        break;  
   }

  }
 

}

//CHANGE THE CODE FOR EACH MOTION FUNCTION HERE; THE 'SIGNAL' REFERS TO THE VALUE YOU SET TOWARDS THE TOP
//YOU CAN CHANGE THAT VALUE TO EFFECT ALL OF THEM, OR SIMPLY PUT THE NUMBER VALUE IN PARANTHESIS TO CHANGE AN INDIVIDUAL VALUE IF NECESSARY

 
void each()
{
    servo1.writeMicroseconds(signal); // Send signal to ESC.
    delay(2000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    servo1.writeMicroseconds(stop); // Send signal to ESC.
    delay(5000); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    servo2.writeMicroseconds(signal); // Send signal to ESC.
    delay(2000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    servo2.writeMicroseconds(stop); // Send signal to ESC.
    delay(5000); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    servo3.writeMicroseconds(signal); // Send signal to ESC.
    delay(2000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    servo3.writeMicroseconds(stop); // Send signal to ESC.
    delay(5000); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    servo4.writeMicroseconds(signal); // Send signal to ESC.
    delay(2000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    servo4.writeMicroseconds(stop); // Send signal to ESC.
    delay(5000); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    servo5.writeMicroseconds(signal); // Send signal to ESC.
    delay(2000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    servo5.writeMicroseconds(stop); // Send signal to ESC.
    delay(5000); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    servo6.writeMicroseconds(signal); // Send signal to ESC.
    delay(2000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    servo6.writeMicroseconds(stop); // Send signal to ESC.
    delay(5000); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    servo7.writeMicroseconds(signal); // Send signal to ESC.
    delay(2000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    servo7.writeMicroseconds(stop); // Send signal to ESC.
    delay(5000); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    servo8.writeMicroseconds(signal); // Send signal to ESC.
    delay(2000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    servo8.writeMicroseconds(stop); // Send signal to ESC.
    delay(5000); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    
}
