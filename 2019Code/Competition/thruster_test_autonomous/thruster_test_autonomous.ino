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
//Orientation is behind the auv, opposite of cameras. Front is toward cameras, top is toward hull.

//dealy(1000); ==> THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)

byte servoPin1 = 13; // Left Front   - black   - a1
byte servoPin2 = 12; // Left Top     - white   - a2
byte servoPin3 = 11; // Left Bottom  - red     - a3
byte servoPin4 = 10; // Left Back   - orange  - a4
byte servoPin5 = 5;  // Right Bottom - yellow  - m1
byte servoPin6 = 7;  // Right Bottom - green   - m2
byte servoPin7 = 6;  // Right Back   - blue    - m3
byte servoPin8 = 8;  // Right Top    - purple  - m4

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
  
  delay(1000); // delay to allow the ESC to recognize the stopped signal
  Serial.begin(9600);
  Serial.println("Main Directions (f=forward,d=Down,u=Up,r=Right,l=Left)");
  Serial.println("Other Directions (s=slightleft,t=slightright,b=Backwards, g=Straight)");
  //Serial.println("Individual Directions forward (a1, a2, a3, a4, m1, m2, m3 , m4)");
}

void loop() {
  // put your main code here, to run repeatedly:
    
  Mission = digitalRead(MissionSwitch); // read Mission Switch input 
  char dir;//='t' //direction
  if (Mission== LOW)
  {
        //Run loop with individual thrusters
        a1_test();
        delay(4000);
        a2_test();
        delay(4000);
        a3_test();
        delay(4000);
        a4_test();
        delay(4000);
        m1_test();
        delay(4000);
        m2_test();
        delay(4000);
        m3_test();
        delay(4000);
        m4_test();
        delay(4000);

        
        //run functions
//        forward();
//        Serial.println("forward");
//        delay(4000);
//        left();
//        Serial.println("left");
//        delay(4000);
//        right();
//        Serial.println("right");
//        delay(4000);
//        backwards();
//        Serial.println("backwards");
//        delay(4000);

        straight();
        Serial.println("straight");
        delay(4000);
        
        up();
        Serial.println("up");
        delay(4000);
        
        down();
        Serial.println("down");
        delay(4000);

        hover();
        Serial.println("hover");
        delay(4000);
        
//        slightLeft();
//        Serial.println("slight left");
//        delay(4000);
//        slightRight();
//        Serial.println("slight right");
//        delay(4000);
        
       
    
}
}


////////////// Main Functions /////////////////////
void hover()
{
  m4.writeMicroseconds(1650);
  m1.writeMicroseconds(1350);
  a1.writeMicroseconds(1650);
  a4.writeMicroseconds(1350);
}

void forward()//Hovering in plane while moving forward-
{
    a2.writeMicroseconds(1650); // Send signal to ESC.  MOVE FORWARD
    m2.writeMicroseconds(1650); // Send signal to ESC.  Top move forward
    m3.writeMicroseconds(1650); // Send signal to ESC.  then bottom
    a3.writeMicroseconds(1650); // Send signal to ESC.
    
    a1.writeMicroseconds(1350); // Send signal to ESC.  HOVER DOWN
    m1.writeMicroseconds(1350); // Send signal to ESC.  from moves down
    a4.writeMicroseconds(1350); // Send signal to ESC.  then back
    m4.writeMicroseconds(1350); // Send signal to ESC.

    delay(5000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)

    a2.writeMicroseconds(stop); // Send signal to ESC.
    m2.writeMicroseconds(stop); // Send signal to ESC.
    m3.writeMicroseconds(stop); // Send signal to ESC.
    a3.writeMicroseconds(stop); // Send signal to ESC.
    a1.writeMicroseconds(stop); // Send signal to ESC.
    m1.writeMicroseconds(stop); // Send signal to ESC.
    a4.writeMicroseconds(stop); // Send signal to ESC.
    m4.writeMicroseconds(stop); // Send signal to ESC.
}

void down()
{
  a1.writeMicroseconds(1650); // Send signal to ESC.
  a4.writeMicroseconds(1650); // Send signal to ESC.
  m1.writeMicroseconds(1650); // Send signal to ESC.
  m4.writeMicroseconds(1650); // Send signal to ESC.
  delay(5000);
  a1.writeMicroseconds(stop); // Send signal to ESC.
  a4.writeMicroseconds(stop); // Send signal to ESC.
  m1.writeMicroseconds(stop); // Send signal to ESC.
  m4.writeMicroseconds(stop); // Send signal to ESC.  
}

void up()
{
  a1.writeMicroseconds(1350); // Send signal to ESC.
  a4.writeMicroseconds(1350); // Send signal to ESC.
  m1.writeMicroseconds(1350); // Send signal to ESC.
  m4.writeMicroseconds(1350); // Send signal to ESC.
  delay(5000);
}

void right()//Runs the thrusters on the left faster than those on the right to curve right,
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
    m2.writeMicroseconds(stop); // Send signal to ESC.
    m3.writeMicroseconds(stop); // Send signal to ESC. 
}
  void left()//Runs the thrusters on the right faster than those on the left to curve left,
{
  m2.writeMicroseconds(1750);
  a2.writeMicroseconds(1650);
  m3.writeMicroseconds(1750);
  a3.writeMicroseconds(1650);
  
  delay(5000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
  
  m2.writeMicroseconds(stop);
  a2.writeMicroseconds(stop);
  m3.writeMicroseconds(stop);
  a3.writeMicroseconds(stop);  

  //delay(100); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
}

  void slightLeft()
{ // Code is the same as Left(), but the values for the thrusters are not as high,
  // creating a wider arc for the auv to travel
  m2.writeMicroseconds(1600);
  a2.writeMicroseconds(1550);
  m3.writeMicroseconds(1600);
  a3.writeMicroseconds(1550);
  
  delay(5000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
  
  m2.writeMicroseconds(stop);
  a2.writeMicroseconds(stop);
  m3.writeMicroseconds(stop);
  a3.writeMicroseconds(stop);  

  //delay(100); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
}
void slightRight()//Runs the thrusters on the left faster than those on the right to curve right,
{ // Code is the same as Right(), but the values for the thrusters are not as high,
  // creating a wider arc for the auv to travel
  m2.writeMicroseconds(1550);
  a2.writeMicroseconds(1600);
  m3.writeMicroseconds(1550);
  a3.writeMicroseconds(1600);
  
  delay(5000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
  
  m2.writeMicroseconds(stop);
  a2.writeMicroseconds(stop);
  m3.writeMicroseconds(stop);
  a3.writeMicroseconds(stop);  

  //delay(100); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
}
void backwards()
{//Goes DIRECTLY backwards, DOES NOT HOVER
    a2.writeMicroseconds(1450); // Send signal to ESC.  MOVE FORWARD
    m2.writeMicroseconds(1450); // Send signal to ESC.  Top move forward
    m3.writeMicroseconds(1450); // Send signal to ESC.  then bottom
    a3.writeMicroseconds(1450); // Send signal to ESC.

    delay(5000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)

    a2.writeMicroseconds(stop); // Send signal to ESC.
    m2.writeMicroseconds(stop); // Send signal to ESC.
    m3.writeMicroseconds(stop); // Send signal to ESC.
    a3.writeMicroseconds(stop); // Send signal to ESC.
}
void straight()
{//Goes DIRECTLY straight, DOES NOT HOVER
    a2.writeMicroseconds(1650); // Send signal to ESC.  MOVE FORWARD
    m2.writeMicroseconds(1650); // Send signal to ESC.  Top move forward
    m3.writeMicroseconds(1650); // Send signal to ESC.  then bottom
    a3.writeMicroseconds(1650); // Send signal to ESC.

    delay(5000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)

    a2.writeMicroseconds(stop); // Send signal to ESC.
    m2.writeMicroseconds(stop); // Send signal to ESC.
    m3.writeMicroseconds(stop); // Send signal to ESC.
    a3.writeMicroseconds(stop); // Send signal to ESC.
}
void each()
{
    Serial.println("EACH() Loop running");
    Serial.println("a1");
    a1.writeMicroseconds(signal); // Send signal to ESC.
    delay(1500); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    a1.writeMicroseconds(stop); // Send signal to ESC.
    delay(2000); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    
    Serial.println("a2");
    a2.writeMicroseconds(signal); // Send signal to ESC.
    delay(1500); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    a2.writeMicroseconds(stop); // Send signal to ESC.
    delay(2000); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)

    Serial.println("a3");
    a3.writeMicroseconds(signal); // Send signal to ESC.
    delay(1500); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    a3.writeMicroseconds(stop); // Send signal to ESC.
    delay(2000); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    
    Serial.println("a4");
    a4.writeMicroseconds(signal); // Send signal to ESC.
    delay(1500); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    a4.writeMicroseconds(stop); // Send signal to ESC.
    delay(2000); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)

    Serial.println("m1");
    m1.writeMicroseconds(signal); // Send signal to ESC.
    delay(1500); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    m1.writeMicroseconds(stop); // Send signal to ESC.
    delay(2000); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)

    Serial.println("m2");
    m2.writeMicroseconds(signal); // Send signal to ESC.
    delay(1500); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    m2.writeMicroseconds(stop); // Send signal to ESC.
    delay(2000); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    
    Serial.println("m3");
    m3.writeMicroseconds(signal); // Send signal to ESC.
    delay(1500); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    m3.writeMicroseconds(signal); // Send signal to ESC.
    delay(2000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)

    Serial.println("m4");
    m4.writeMicroseconds(signal); // Send signal to ESC.
    delay(1500); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    m4.writeMicroseconds(stop); // Send signal to ESC.
    delay(2000); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
    Serial.println("DONE WITH each()");
}

void a1_test()
{
  a1.writeMicroseconds(1650); // Send signal to ESC.
  delay(5000);
  a1.writeMicroseconds(stop);
}
void a2_test()
{
  a2.writeMicroseconds(1650); // Send signal to ESC.
  delay(5000);
  a2.writeMicroseconds(stop);
}
void a3_test()
{
  a3.writeMicroseconds(1650); // Send signal to ESC.
  delay(5000);
  a3.writeMicroseconds(stop);
}
void a4_test()
{
  a4.writeMicroseconds(1650); // Send signal to ESC.
  delay(5000);
  a4.writeMicroseconds(stop);
}
void m1_test()
{
  m1.writeMicroseconds(1650); // Send signal to ESC.
  delay(5000);
  m1.writeMicroseconds(stop);
}
void m2_test()
{
  m2.writeMicroseconds(1650); // Send signal to ESC.
  delay(5000);
  m2.writeMicroseconds(stop);
}
void m3_test()
{
  m3.writeMicroseconds(1650); // Send signal to ESC.
  delay(5000);
  m3.writeMicroseconds(stop);
}
void m4_test()
{
  m4.writeMicroseconds(1650); // Send signal to ESC.
  delay(5000);
  m4.writeMicroseconds(stop);
}
