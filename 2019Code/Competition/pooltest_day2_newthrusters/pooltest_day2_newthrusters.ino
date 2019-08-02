
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
byte servoPin1 = 13; // Left Front-black - a1
byte servoPin2 = 12; // Left Top-white - a2
byte servoPin3 = 11; // Left Bottom - red
byte servoPin4 = 10; // Left Front - orange- a4
byte servoPin5 = 5; // Right Bottom- yellow - m1
byte servoPin6 = 7; // Left Bottom- green
byte servoPin7 = 6; // Left Back - blue
byte servoPin8 = 8; // Left Top - purple - m4

int MissionSwitch = 34;
int Mission = 0; 


int signal = 1650; // Set signal value, which should be between 1100 and 1900
int stop = 1500; // Stop thruster //1500-1900 positive 1100-1499 negative


Servo a1; 
Servo a2;
Servo a3;
Servo a4;
Servo m1;
Servo m2;
Servo m3;
Servo m4;

void setup() 
{
  
  //flush(MissionSwitch);
  
  a1.attach(servoPin1); 
  a2.attach(servoPin2); 
  a3.attach(servoPin3); 
  a4.attach(servoPin4); 
  m1.attach(servoPin5); 
  m2.attach(servoPin6); 
  m3.attach(servoPin7); 
  m4.attach(servoPin8); 

  //stop them all
  a1.writeMicroseconds(1500); // send "stop" signal to ESC.
  a2.writeMicroseconds(1500); // send "stop" signal to ESC.
  a3.writeMicroseconds(1500); // send "stop" signal to ESC.
  a4.writeMicroseconds(1500); // send "stop" signal to ESC.
  m1.writeMicroseconds(1500); // send "stop" signal to ESC.
  m2.writeMicroseconds(1500); // send "stop" signal to ESC.
  m3.writeMicroseconds(1500); // send "stop" signal to ESC.
  m4.writeMicroseconds(1500); // send "stop" signal to ESC.

  pinMode(MissionSwitch, INPUT_PULLUP); //Mission switch connection as input
  //PULLUP is a function that -- and LOW on mission switch will mean it is on
  delay(1000); // delay to allow the ESC to recognize the stopped signal
  Serial.begin(9600);
  Serial.println("Directions (d=Down,h=hover,f=Forward,l=Left,s=slightleft,r=Right,t=slightright,u=Up,b=Backward)");
  
  

}

void loop() 
{
   // Serial.println("l");
  Mission = digitalRead(MissionSwitch); // read Mission Switch input 
  char dir; //direction
  if (Mission== LOW)
  {
     // Serial.println("MISSION ON");
    //CHOOSE WHICH MOTIONS YOU WANT TO RUN HERE, COMMENT OUT THE ONES YOU DON'T WANT TO USE BY PLACING // IN FRONT OF IT
    //THE ACTUAL CODE FOR EACH FUNCTION IS FURTHER DOWN
//    float sensorValue = analogRead(A0);
//    float pressure = sensorValue/15.0;
//    dir= Serial.read();
//    switch(dir){
//      case 'd':
//        down();
//        Serial.println("down");
//        break;
//      case 'h':
//        hover();
//        Serial.println("hover");
//        break;  
//      case 'f':
//        forward();
//        Serial.println("forward");
//        break;
//      case 'v':
//        //slighback();
//        break;  
//      case 'l':
//        left();
//        Serial.println("left");
//        break;
//      case 's':
//        slightleft();
//        Serial.println("slight left");
//        break; 
//      case 't':
//        slightright();
//        Serial.println("slight right");
//        break; 
//      case 'r':
//        right();
//        Serial.println("right");
//        break;
//      case 'u':
//        up();
//        Serial.println("up");
//        break;
//      case 'b':
//        backward();
//        Serial.println("backward");
//        break;
//      case 'e':
//        each();
//        Serial.println("each");
//        break;
//      case 'm':
//        Serial.print("Value: ");
//        Serial.println(pressure);
//        break;
//      case 'p':
//        Serial.println("dice");
//        break;
//      case 'g':
//        straight();
//        Serial.println("straight");
//        break;
//      default:
//        //hover();
//        break;  
//   }

    forward();
    forward();
    down();
    slightright();
    forward();
    right();
    forward();
    forward();
    forward();

  }
 

}

//CHANGE THE CODE FOR EACH MOTION FUNCTION HERE; THE 'SIGNAL' REFERS TO THE VALUE YOU SET TOWARDS THE TOP
//YOU CAN CHANGE THAT VALUE TO EFFECT ALL OF THEM, OR SIMPLY PUT THE NUMBER VALUE IN PARANTHESIS TO CHANGE AN INDIVIDUAL VALUE IF NECESSARY
void down()
{

   m1.writeMicroseconds(stop+125);
   m4.writeMicroseconds(stop-125);
   a1.writeMicroseconds(stop+125);
   a4.writeMicroseconds(stop+125);
    delay(700); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    a1.writeMicroseconds(stop); // Send signal to ESC.
    a4.writeMicroseconds(stop); // Send sign
    m1.writeMicroseconds(stop); // Send signal to ESC.
    m4.writeMicroseconds(stop); // Send signal to ESC.
}
void hover()
{
    m2.writeMicroseconds(stop+170);
}
void up()
{
   m4.writeMicroseconds(stop+170);

//
    delay(1000); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
}
void backward()
{
    m4.writeMicroseconds(1625); // Send signal to ESC.  HOVER DOWN
    a1.writeMicroseconds(1675); // Send signal to ESC.
    a4.writeMicroseconds(1375); // Send signal to ESC.
    m3.writeMicroseconds(1625); // Send signal to ESC.
    
    m4.writeMicroseconds(stop); // Send signal to ESC.
    a1.writeMicroseconds(stop); // Send signal to ESC.
    a4.writeMicroseconds(stop); // Send signal to ESC.
    m3.writeMicroseconds(stop); // Send signal to ESC.
    
    delay(2000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)

    m2.writeMicroseconds(stop); // Send signal to ESC.
    m1.writeMicroseconds(stop); // Send signal to ESC.
    a3.writeMicroseconds(stop); // Send signal to ESC.
    a2.writeMicroseconds(stop); // Send signal to ESC.
    m4.writeMicroseconds(stop); // Send signal to ESC.
    a1.writeMicroseconds(stop); // Send signal to ESC.
    a4.writeMicroseconds(stop); // Send signal to ESC.
    m3.writeMicroseconds(stop); // Send signal to ESC.

    delay(3000); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND) 
}

void slightback()
{
    m4.writeMicroseconds(1625); // Send signal to ESC.  HOVER DOWN
    a1.writeMicroseconds(1675); // Send signal to ESC.
    a4.writeMicroseconds(1375); // Send signal to ESC.
    m3.writeMicroseconds(1625); // Send signal to ESC.
    
    a3.writeMicroseconds(1350); // Send signal to ESC.  MOVE BACK
    m2.writeMicroseconds(1365); // Send signal to ESC.
    m1.writeMicroseconds(1365); // Send signal to ESC.
    a2.writeMicroseconds(1350); // Send signal to ESC.
    
    delay(1000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)

    m2.writeMicroseconds(stop); // Send signal to ESC.
    m1.writeMicroseconds(stop); // Send signal to ESC.
    a3.writeMicroseconds(stop); // Send signal to ESC.
    a2.writeMicroseconds(stop); // Send signal to ESC.
    m4.writeMicroseconds(stop); // Send signal to ESC.
    a1.writeMicroseconds(stop); // Send signal to ESC.
    a4.writeMicroseconds(stop); // Send signal to ESC.
    m3.writeMicroseconds(stop); // Send signal to ESC.

    delay(3000); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND) 
}

void forward()
{
    
    //KEEPING DOWN
    m1.writeMicroseconds(1625);
    m4.writeMicroseconds(1375);
    a1.writeMicroseconds(1625);
    a4.writeMicroseconds(1625);
    delay(1500); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    //FORWARD MOTION
    
    
    
    a1.writeMicroseconds(stop); // Send signal to ESC.
    a4.writeMicroseconds(stop); // Send sign
    m1.writeMicroseconds(stop); // Send signal to ESC.
    m4.writeMicroseconds(stop); // Send signal to ESC.

    a3.writeMicroseconds(1670); // Send signal to ESC.  MOVE FORWARD
    a2.writeMicroseconds(1360); // Send signal to ESC.
    m2.writeMicroseconds(1670); // Send signal to ESC.
    m3.writeMicroseconds(1360); // Send signal to ESC.
    //hover
    m1.writeMicroseconds(1550);
    m4.writeMicroseconds(1400);
    a1.writeMicroseconds(1600);
    a4.writeMicroseconds(1600);
    delay(9000);
    
    m2.writeMicroseconds(stop); // Send signal to ESC.
    m3.writeMicroseconds(stop); // Send signal to ESC.
    a3.writeMicroseconds(stop); // Send signal to ESC.
    a2.writeMicroseconds(stop); // Send signal to ESC.
    a1.writeMicroseconds(stop); // Send signal to ESC.
    a4.writeMicroseconds(stop); // Send sign
    m1.writeMicroseconds(stop); // Send signal to ESC.
    m4.writeMicroseconds(stop); // Send signal to ESC.
    Serial.println("done forward");

}
void straight()
{
    a3.writeMicroseconds(1650); // Send signal to ESC.  MOVE FORWARD
    a2.writeMicroseconds(1350); // Send signal to ESC.
    m2.writeMicroseconds(1650); // Send signal to ESC.
    m3.writeMicroseconds(1360); // Send signal to ESC.
    

    delay(9000);

    m2.writeMicroseconds(stop); // Send signal to ESC.
    m3.writeMicroseconds(stop); // Send signal to ESC.
    a3.writeMicroseconds(stop); // Send signal to ESC.
    a2.writeMicroseconds(stop); // Send signal to ESC.

    
}
void left()
{
    a3.writeMicroseconds(1650); // Send signal to ESC.  MOVE FORWARD
    a2.writeMicroseconds(1380); // Send signal to ESC.
    m2.writeMicroseconds(1665); // Send signal to ESC.
    m3.writeMicroseconds(1350); // Send signal to ESC.
    //hover
    m1.writeMicroseconds(1600);
    m4.writeMicroseconds(1400);
    a1.writeMicroseconds(1600);
    a4.writeMicroseconds(1600);
    delay(15000);
    

}  
void slightleft()
{
    a3.writeMicroseconds(1640); // Send signal to ESC.  MOVE FORWARD
    a2.writeMicroseconds(1390); // Send signal to ESC.
    m2.writeMicroseconds(1630); // Send signal to ESC.
    m3.writeMicroseconds(1370); // Send signal to ESC.
    //hover
    m1.writeMicroseconds(1600);
    m4.writeMicroseconds(1400);
    a1.writeMicroseconds(1600);
    a4.writeMicroseconds(1600);
    delay(5000);
    
    m2.writeMicroseconds(stop); // Send signal to ESC.
    m3.writeMicroseconds(stop); // Send signal to ESC.
    a3.writeMicroseconds(stop); // Send signal to ESC.
    a2.writeMicroseconds(stop); // Send signal to ESC.
    a1.writeMicroseconds(stop); // Send signal to ESC.
    a4.writeMicroseconds(stop); // Send sign
    m1.writeMicroseconds(stop); // Send signal to ESC.
    m4.writeMicroseconds(stop); // Send signal to ESC.
  
}  
void right()
{
   
    a3.writeMicroseconds(1715); // Send signal to ESC.  MOVE FORWARD
    a2.writeMicroseconds(1315); // Send signal to ESC.
    m2.writeMicroseconds(1580); // Send signal to ESC.
    m3.writeMicroseconds(1415); // Send signal to ESC.
    //hover
    m1.writeMicroseconds(1600);
    m4.writeMicroseconds(1400);
    a1.writeMicroseconds(1600);
    a4.writeMicroseconds(1600);
    delay(5000);

    m1.writeMicroseconds(stop); // Send signal to ESC.
    m4.writeMicroseconds(stop); // Send signal to ESC.
    a3.writeMicroseconds(stop); // Send signal to ESC.
    a2.writeMicroseconds(stop); // Send signal to ESC.
    a1.writeMicroseconds(stop); // Send signal to ESC.
    a4.writeMicroseconds(stop); // Send sign
    m2
    .writeMicroseconds(stop); // Send signal to ESC.
    m3.writeMicroseconds(stop); // Send signal to ESC.    
    
    
}  
void slightright()
{
    a3.writeMicroseconds(1645); // Send signal to ESC.  MOVE FORWARD
    a2.writeMicroseconds(1385); // Send signal to ESC.
    m2.writeMicroseconds(1625); // Send signal to ESC.
    m3.writeMicroseconds(1375); // Send signal to ESC.
    //hover
    m1.writeMicroseconds(1600);
    m4.writeMicroseconds(1400);
    a1.writeMicroseconds(1600);
    a4.writeMicroseconds(1600);
    delay(5000);
    
    m2.writeMicroseconds(stop); // Send signal to ESC.
    m3.writeMicroseconds(stop); // Send signal to ESC.
    a3.writeMicroseconds(stop); // Send signal to ESC.
    a2.writeMicroseconds(stop); // Send signal to ESC.
    a1.writeMicroseconds(stop); // Send signal to ESC.
    a4.writeMicroseconds(stop); // Send sign
    m1.writeMicroseconds(stop); // Send signal to ESC.
    m4.writeMicroseconds(stop); // Send signal to ESC.
}  
void each()
{
    a1.writeMicroseconds(signal); // Send signal to ESC.
    delay(2000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    a1.writeMicroseconds(stop); // Send signal to ESC.
    delay(5000); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    a2.writeMicroseconds(signal); // Send signal to ESC.
    delay(2000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    a2.writeMicroseconds(stop); // Send signal to ESC.
    delay(5000); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    a3.writeMicroseconds(signal); // Send signal to ESC.
    delay(2000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    a3.writeMicroseconds(stop); // Send signal to ESC.
    delay(5000); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    a4.writeMicroseconds(signal); // Send signal to ESC.
    delay(2000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    a4.writeMicroseconds(stop); // Send signal to ESC.
    delay(5000); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    m1.writeMicroseconds(signal); // Send signal to ESC.
    delay(2000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    m1.writeMicroseconds(stop); // Send signal to ESC.
    delay(5000); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    m1.writeMicroseconds(signal); // Send signal to ESC.
    delay(2000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    m2.writeMicroseconds(stop); // Send signal to ESC.
    delay(5000); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    m3.writeMicroseconds(signal); // Send signal to ESC.
    delay(2000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    m4.writeMicroseconds(stop); // Send signal to ESC.
    delay(5000); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    m4.writeMicroseconds(signal); // Send signal to ESC.
    delay(2000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    m4.writeMicroseconds(stop); // Send signal to ESC.
    delay(5000); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
}


//M1 AND M2 are switched- m1 runs m4 and m4 runs m1
