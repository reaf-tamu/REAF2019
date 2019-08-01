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
byte servoPin1 = 10; // Left Front   - black   - a1
byte servoPin2 = 12; // Left Top     - white   - a2
byte servoPin3 = 11; // Left Bottom  - red     - a3
byte servoPin4 = 13; // Left Back   - orange  - a4
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
  //Serial.println("Other Directions (s=slightleft,t=slightright,b=Backward, g=Straight)");
  //Serial.println("Individual Directions forward (a1, a2, a3, a4, m1, m2, m3 , m4)");
}

void loop() {
  // put your main code here, to run repeatedly:
    
  Mission = digitalRead(MissionSwitch); // read Mission Switch input 
  char dir;//='t' //direction
  if (Mission== LOW)
  {
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
      case 'g':
        straight();
        Serial.println("straight");
        break;
      default:
        //hover();
        break;
}
}
void a1_test()
{
  a1.writeMicroseconds(1550); // Send signal to ESC.
  delay(1000);
}
void a2_test()
{
  a2.writeMicroseconds(1550); // Send signal to ESC.
  delay(1000);
}
void a3_test()
{
  a3.writeMicroseconds(1550); // Send signal to ESC.
  delay(1000);
}
void a4_test()
{
  a4.writeMicroseconds(1550); // Send signal to ESC.
  delay(1000);
}
void m1_test()
{
  m1.writeMicroseconds(1550); // Send signal to ESC.
  delay(1000);
}
void m2_test()
{
  m2.writeMicroseconds(1550); // Send signal to ESC.
  delay(1000);
}
void m3_test()
{
  m3.writeMicroseconds(1550); // Send signal to ESC.
  delay(1000);
}
void m4_test()
{
  m4.writeMicroseconds(1550); // Send signal to ESC.
  delay(1000);
}
////////////// Main Functions /////////////////////
void forward()//Hovering in plane while moving forward
{
    a2.writeMicroseconds(1550); // Send signal to ESC.  MOVE FORWARD
    m2.writeMicroseconds(1550); // Send signal to ESC.  Top move forward
    m3.writeMicroseconds(1550); // Send signal to ESC.  then bottom
    a3.writeMicroseconds(1550); // Send signal to ESC.
    
    a1.writeMicroseconds(1450); // Send signal to ESC.  HOVER DOWN
    m1.writeMicroseconds(1450); // Send signal to ESC.  from moves down
    a4.writeMicroseconds(1450); // Send signal to ESC.  then back
    m4.writeMicroseconds(1450); // Send signal to ESC.

    //delay(2000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)

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
  a1.writeMicroseconds(1450); // Send signal to ESC.
  a4.writeMicroseconds(1450); // Send signal to ESC.
  m1.writeMicroseconds(1450); // Send signal to ESC.
  m4.writeMicroseconds(1450); // Send signal to ESC.
  //delay(1000);
  a1.writeMicroseconds(stop); // Send signal to ESC.
  a4.writeMicroseconds(stop); // Send signal to ESC.
  m1.writeMicroseconds(stop); // Send signal to ESC.
  m4.writeMicroseconds(stop); // Send signal to ESC.  
}

void up()
{
  a1.writeMicroseconds(1550); // Send signal to ESC.
  a4.writeMicroseconds(1550); // Send signal to ESC.
  m1.writeMicroseconds(1550); // Send signal to ESC.
  m4.writeMicroseconds(1550); // Send signal to ESC.
}

void right()//Runs the thrusters on the left faster than those on the right to curve right,
{
  m2.writeMicroseconds(1550);
  a2.writeMicroseconds(1650);
  m3.writeMicroseconds(1550);
  a3.writeMicroseconds(1650);
  
  //delay(3000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
  
  m2.writeMicroseconds(stop);
  a2.writeMicroseconds(stop);
  m3.writeMicroseconds(stop);
  a3.writeMicroseconds(stop);  

  //delay(100); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
}

  void left()//Runs the thrusters on the right faster than those on the left to curve left,
{
  m2.writeMicroseconds(1650);
  a2.writeMicroseconds(1550);
  m3.writeMicroseconds(1650);
  a3.writeMicroseconds(1550);
  
  //delay(3000); //THIS IS HOW LONG THE THRUSTERS RUN IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
  
  m2.writeMicroseconds(stop);
  a2.writeMicroseconds(stop);
  m3.writeMicroseconds(stop);
  a3.writeMicroseconds(stop);  

  //delay(100); //THIS IS HOW LONG THE THRUSTERS ARE STOPPED IN MILLISECONDS (1000 MILLISECONDS = 1 SECOND)
}
