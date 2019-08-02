  #include <Servo.h>
#include <SoftwareSerial.h>

//NOTE: Works for single thrusters test = all pins aligned properly


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
byte servoPin3 = 11; // Left Bottom - red - a3
byte servoPin4 = 10; // Left Front - orange- a4
byte servoPin5 = 5; // Right Bottom- yellow - m1
byte servoPin6 = 7; // Left Bottom- green - m2
byte servoPin7 = 6; // Left Back - blue - m3
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
  Serial.println("Directions (a=a1, s=a2, d=a3, f=a4, h=m1, j=m2,k=m3, l=m4)");
  

}


void loop() {
  // put your main code here, to run repeatedly:
    
  Mission = digitalRead(MissionSwitch); // read Mission Switch input 
  char dir; //direction
  if (Mission== LOW)
  {
    //Serial.print("MISSION ON");

    //CHOOSE WHICH MOTIONS YOU WANT TO RUN HERE, COMMENT OUT THE ONES YOU DON'T WANT TO USE BY PLACING // IN FRONT OF IT
    //THE ACTUAL CODE FOR EACH FUNCTION IS FURTHER DOWN
    
    dir= Serial.read();
   
    switch(dir){
      case 'a':
        Serial.println("BEFORE a1 forward");
        a1_test();
        Serial.println("a1 forward");
        break;
      case 's':
        a2_test();
        Serial.println("a2 forward");
        break;  
      case 'd':
        a3_test();
        Serial.println("a3 forward");
        break;
      case 'f':
        a4_test();
        Serial.println("a4 forward");
        break;
      case 'h':
        m1_test();
        Serial.println("m1 forward");
        break;
      case 'j':
        m2_test();
        Serial.println("m2 forward");
        break;
      case 'k':
        m3_test();
        Serial.println("m3 forward");
        break;
      case 'l':
        m4_test();
        Serial.println("m4 forward");
        break;
      default:
       // Serial.println` ("default");
        break;
}
}
}


//FUNCTIONS---------------
void a1_test()
{
  a1.writeMicroseconds(1550); // Send signal to ESC.
  delay(3000);
  a1.writeMicroseconds(stop);
}
void a2_test()
{
  a2.writeMicroseconds(1550); // Send signal to ESC.
  delay(3000);
  a2.writeMicroseconds(stop);
}
void a3_test()
{
  a3.writeMicroseconds(1550); // Send signal to ESC.
  delay(3000);
  a3.writeMicroseconds(stop);
}
void a4_test()
{
  a4.writeMicroseconds(1550); // Send signal to ESC.
  delay(1000);
  a4.writeMicroseconds(stop);
}
void m1_test()
{
  m1.writeMicroseconds(1700); // Send signal to ESC.
  delay(3000);
  m1.writeMicroseconds(stop);
}
void m2_test()
{
  m2.writeMicroseconds(1750); // Send signal to ESC.
  delay(3000);
  m2.writeMicroseconds(stop);
}
void m3_test()
{
  m3.writeMicroseconds(1750); // Send signal to ESC.
  delay(3000);
  m3.writeMicroseconds(stop);
}
void m4_test()
{
  m4.writeMicroseconds(1750); // Send signal to ESC.
  delay(3000);
  m4.writeMicroseconds(stop);
}
