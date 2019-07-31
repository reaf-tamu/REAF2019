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
byte servoPin1 = 13; // Left Front-black - A1
byte servoPin2 = 12; // Left Top-white
byte servoPin3 = 11; // Left Bottom - red
byte servoPin4 = 10; // Left Front - orange- A4
byte servoPin5 = 8; // Right Bottom- yellow - M1
byte servoPin6 = 7; // Left Bottom- green
byte servoPin7 = 6; // Left Back - blue
byte servoPin8 = 5; // Left Top - purple - M4

int MissionSwitch = 34;
int Mission = 0; 


int signal = 1650; // Set signal value, which should be between 1100 and 1900
int stop = 1500; // Stop thruster //1500-1900 positive 1100-1499 negative


Servo A1; 
Servo A2;
Servo A3;
Servo A4;
Servo M1;
Servo M2;
Servo M3;
Servo M4;

void setup() 
{
  
  A1.attach(servoPin1); 
  A2.attach(servoPin2); 
  A3.attach(servoPin3); 
  A4.attach(servoPin4); 
  M1.attach(servoPin5); 
  M2.attach(servoPin6); 
  M3.attach(servoPin7); 
  M4.attach(servoPin8); 

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
  Serial.println("Directions (d=Down,h=hover,f=Forward,l=Left,s=slightleft,r=Right,t=slightright,u=Up,b=Backward)");
  

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
      case 'd':
        down();
        Serial.println("down");
        break;
      case 'h':
        hover();
        Serial.println("hover");
        break;  
      case 'f':
        forward();
        Serial.println("forward");
        break;
      case 'v':
        //slighback();
        break;  
      case 'l':
        left();
        Serial.println("left");
        break;
      case 's':
        slightleft();
        Serial.println("slight left");
        break; 
      case 't':
        slightright();
        Serial.println("slight right");
        break; 
      case 'r':
        right();
        Serial.println("right");
        break;
      case 'u':
        up();
        Serial.println("up");
        break;
      case 'b':
        backward();
        Serial.println("backward");
        break;
      case 'e':
        each();
        Serial.println("each");
        break;
      case 'm':
        Serial.print("Value: ");
        Serial.println(pressure);
        break;
      case 'p':
        Serial.println("dice");
        break;
      case 'g':
        straight();
        Serial.println("straight");
        break;
      default:
        //hover();
        break;  
   }

  }
 

}

//CHANGE THE CODE FOR EACH MOTION FUNCTION HERE; THE 'SIGNAL' REFERS TO THE VALUE YOU SET TOWARDS THE TOP
//YOU CAN CHANGE THAT VALUE TO EFFECT ALL OF THEM, OR SIMPLY PUT THE NUMBER VALUE IN PARANTHESIS TO CHANGE AN INDIVIDUAL VALUE IF NECESSARY
void dice() 
{
    //GO DOWN
    servo8.writeMicroseconds(1400); // Send signal to ESC.
    servo1.writeMicroseconds(1600); // Send signal to ESC.
    servo4.writeMicroseconds(1400); // Send signal to ESC.
    servo7.writeMicroseconds(1600); // Send signal to ESC.  
    delay(6000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    servo8.writeMicroseconds(stop); // Send signal to ESC.
    servo1.writeMicroseconds(stop); // Send signal to ESC.
    servo4.writeMicroseconds(stop); // Send signal to ESC.
    servo7.writeMicroseconds(stop); // Send signal to ESC.
    delay(100); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)

    //GO FORWARD
    servo3.writeMicroseconds(1690); // Send signal to ESC.  MOVE FORWARD
    servo6.writeMicroseconds(1675); // Send signal to ESC.
    servo5.writeMicroseconds(1675); // Send signal to ESC.
    servo2.writeMicroseconds(1690); // Send signal to ESC.  
    servo8.writeMicroseconds(1610); // Send signal to ESC.  HOVER DOWN
    servo1.writeMicroseconds(1390); // Send signal to ESC.
    servo4.writeMicroseconds(1390); // Send signal to ESC.
    servo7.writeMicroseconds(1610); // Send signal to ESC.
    delay(30000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    servo6.writeMicroseconds(stop); // Send signal to ESC.
    servo5.writeMicroseconds(stop); // Send signal to ESC.
    servo3.writeMicroseconds(stop); // Send signal to ESC.
    servo2.writeMicroseconds(stop); // Send signal to ESC.
    servo8.writeMicroseconds(stop); // Send signal to ESC.
    servo1.writeMicroseconds(stop); // Send signal to ESC.
    servo4.writeMicroseconds(stop); // Send signal to ESC.
    servo7.writeMicroseconds(stop); // Send signal to ESC.    
  
}
void down()
{

    M4.writeMicroseconds(1400); // Send signal to ESC.
    A1.writeMicroseconds(1600); // Send signal to ESC.
    A4.writeMicroseconds(1400); // Send signal to ESC.
    M3.writeMicroseconds(1600); // Send signal to ESC.
    
    delay(3000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    M4.writeMicroseconds(stop); // Send signal to ESC.
    A1.writeMicroseconds(stop); // Send signal to ESC.
    A4.writeMicroseconds(stop); // Send signal to ESC.
    M3.writeMicroseconds(stop); // Send signal to ESC.
//
    delay(100); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
}
void hover()
{
    M4.writeMicroseconds(1625); // Send signal to ESC.
    A1.writeMicroseconds(1675); // Send signal to ESC.
    A4.writeMicroseconds(1375); // Send signal to ESC.
    M3.writeMicroseconds(1625); // Send signal to ESC.
    
    delay(100); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)

    M4.writeMicroseconds(stop); // Send signal to ESC.
    A1.writeMicroseconds(stop); // Send signal to ESC.
    A4.writeMicroseconds(stop); // Send signal to ESC.
    M3.writeMicroseconds(stop); // Send signal to ESC.

    delay(100); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
}
void up()
{
    M4.writeMicroseconds(1675); // Send signal to ESC.
    A1.writeMicroseconds(1325); // Send signal to ESC.
    A4.writeMicroseconds(1675); // Send signal to ESC.
    M3.writeMicroseconds(1325); // Send signal to ESC.
    
    delay(2000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
//
//
    M4.writeMicroseconds(stop); // Send signal to ESC.
    A1.writeMicroseconds(stop); // Send signal to ESC.
    A4.writeMicroseconds(stop); // Send signal to ESC.
    M3.writeMicroseconds(stop); // Send signal to ESC.

//
    delay(100); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
}
void backward()
{
    M4.writeMicroseconds(1625); // Send signal to ESC.  HOVER DOWN
    A1.writeMicroseconds(1675); // Send signal to ESC.
    A4.writeMicroseconds(1375); // Send signal to ESC.
    M3.writeMicroseconds(1625); // Send signal to ESC.
    
    M4.writeMicroseconds(stop); // Send signal to ESC.
    A1.writeMicroseconds(stop); // Send signal to ESC.
    A4.writeMicroseconds(stop); // Send signal to ESC.
    M3.writeMicroseconds(stop); // Send signal to ESC.
    
    delay(2000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)

    M2.writeMicroseconds(stop); // Send signal to ESC.
    M1.writeMicroseconds(stop); // Send signal to ESC.
    A3.writeMicroseconds(stop); // Send signal to ESC.
    A2.writeMicroseconds(stop); // Send signal to ESC.
    M4.writeMicroseconds(stop); // Send signal to ESC.
    A1.writeMicroseconds(stop); // Send signal to ESC.
    A4.writeMicroseconds(stop); // Send signal to ESC.
    M3.writeMicroseconds(stop); // Send signal to ESC.

    delay(100); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND) 
}

void slightback()
{
    M4.writeMicroseconds(1625); // Send signal to ESC.  HOVER DOWN
    A1.writeMicroseconds(1675); // Send signal to ESC.
    A4.writeMicroseconds(1375); // Send signal to ESC.
    M3.writeMicroseconds(1625); // Send signal to ESC.
    
    A3.writeMicroseconds(1350); // Send signal to ESC.  MOVE BACK
    M2.writeMicroseconds(1365); // Send signal to ESC.
    M1.writeMicroseconds(1365); // Send signal to ESC.
    A2.writeMicroseconds(1350); // Send signal to ESC.
    
    delay(1000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)

    M2.writeMicroseconds(stop); // Send signal to ESC.
    M1.writeMicroseconds(stop); // Send signal to ESC.
    A3.writeMicroseconds(stop); // Send signal to ESC.
    A2.writeMicroseconds(stop); // Send signal to ESC.
    M4.writeMicroseconds(stop); // Send signal to ESC.
    A1.writeMicroseconds(stop); // Send signal to ESC.
    A4.writeMicroseconds(stop); // Send signal to ESC.
    M3.writeMicroseconds(stop); // Send signal to ESC.

    delay(100); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND) 
}

void forward()
{

    A3.writeMicroseconds(1690); // Send signal to ESC.  MOVE FORWARD
    M2.writeMicroseconds(1675); // Send signal to ESC.
    M1.writeMicroseconds(1675); // Send signal to ESC.
    A2.writeMicroseconds(1690); // Send signal to ESC.
    
    M4.writeMicroseconds(1375); // Send signal to ESC.  HOVER DOWN
    A1.writeMicroseconds(1625); // Send signal to ESC.
    A4.writeMicroseconds(1375); // Send signal to ESC.
    M3.writeMicroseconds(1625); // Send signal to ESC.

    delay(2000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)

    M2.writeMicroseconds(stop); // Send signal to ESC.
    M1.writeMicroseconds(stop); // Send signal to ESC.
    A3.writeMicroseconds(stop); // Send signal to ESC.
    A2.writeMicroseconds(stop); // Send signal to ESC.
    M4.writeMicroseconds(stop); // Send signal to ESC.
    A1.writeMicroseconds(stop); // Send signal to ESC.
    A4.writeMicroseconds(stop); // Send signal to ESC.
    M3.writeMicroseconds(stop); // Send signal to ESC.

}
void straight()
{
    A3.writeMicroseconds(1690); // Send signal to ESC.  MOVE FORWARD
    M2.writeMicroseconds(1675); // Send signal to ESC.
    M1.writeMicroseconds(1675); // Send signal to ESC.
    A2.writeMicroseconds(1690); // Send signal to ESC.

    delay(2000);

    M2.writeMicroseconds(stop); // Send signal to ESC.
    M1.writeMicroseconds(stop); // Send signal to ESC.
    A3.writeMicroseconds(stop); // Send signal to ESC.
    A2.writeMicroseconds(stop); // Send signal to ESC.

    delay(100);
    
}
void left()
{

  A3.writeMicroseconds(signal);
  A2.writeMicroseconds(signal);

  delay(3000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)

  A3.writeMicroseconds(stop);
  A2.writeMicroseconds(stop);

  delay(10000); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
}  
void slightleft()
{

  A3.writeMicroseconds(1650);
  A2.writeMicroseconds(1650);

  delay(1000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)

  A3.writeMicroseconds(stop);
  A2.writeMicroseconds(stop);

  delay(100); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
}  
void right()
{

  M1.writeMicroseconds(1650);
  M2.writeMicroseconds(1650);

  delay(3000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
  
  M1.writeMicroseconds(stop);
  M2.writeMicroseconds(stop);  

  delay(100); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
}  
void slightright()
{

  M1.writeMicroseconds(1650);
  M2.writeMicroseconds(1650);

  delay(1000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
  
  M1.writeMicroseconds(stop);
  M2.writeMicroseconds(stop);  

  delay(100); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
}  
void each()
{
    A1.writeMicroseconds(signal); // Send signal to ESC.
    delay(2000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    A1.writeMicroseconds(stop); // Send signal to ESC.
    delay(5000); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    A2.writeMicroseconds(signal); // Send signal to ESC.
    delay(2000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    A2.writeMicroseconds(stop); // Send signal to ESC.
    delay(5000); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    A3.writeMicroseconds(signal); // Send signal to ESC.
    delay(2000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    A3.writeMicroseconds(stop); // Send signal to ESC.
    delay(5000); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    A4.writeMicroseconds(signal); // Send signal to ESC.
    delay(2000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    A4.writeMicroseconds(stop); // Send signal to ESC.
    delay(5000); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    A5.writeMicroseconds(signal); // Send signal to ESC.
    delay(2000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    A5.writeMicroseconds(stop); // Send signal to ESC.
    delay(5000); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    M1.writeMicroseconds(signal); // Send signal to ESC.
    delay(2000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    M2.writeMicroseconds(stop); // Send signal to ESC.
    delay(5000); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    M3.writeMicroseconds(signal); // Send signal to ESC.
    delay(2000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    M4.writeMicroseconds(stop); // Send signal to ESC.
    delay(5000); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    M4.writeMicroseconds(signal); // Send signal to ESC.
    delay(2000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    M4.writeMicroseconds(stop); // Send signal to ESC.
    delay(5000); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    
