//----This code is just for turning on 4 ESCs at a time percent wise.
 
#include <Servo.h>

#define MAX_SIGNAL 2000
#define MIN_SIGNAL 1000
#define MOTOR_PIN1 4
#define MOTOR_PIN2 5
#define MOTOR_PIN3 6
#define MOTOR_PIN4 7
int DELAY = 1000;

Servo motor1,motor2,motor3,motor4;
void setup() {
  // put your setup code here, to run once:
motor1.attach(MOTOR_PIN1);
motor2.attach(MOTOR_PIN2);
motor3.attach(MOTOR_PIN3);
motor4.attach(MOTOR_PIN4);

motor1.writeMicroseconds(MIN_SIGNAL);
motor2.writeMicroseconds(MIN_SIGNAL);
motor3.writeMicroseconds(MIN_SIGNAL);
motor4.writeMicroseconds(MIN_SIGNAL);

Serial.begin(9600);

 

}

void loop() {
  // put your main code here, to run repeatedly:
if (Serial.available() > 0)
  {
    int DELAY = Serial.parseInt();
    if (DELAY > 999)
    {
      
      motor1.writeMicroseconds(DELAY);
      motor2.writeMicroseconds(DELAY);
      motor3.writeMicroseconds(DELAY);
      motor4.writeMicroseconds(DELAY);

      
      float SPEED = (DELAY-1000)/10;
      Serial.print("\n");
      Serial.println("Motor speed:"); Serial.print("  "); Serial.print(SPEED); Serial.print("%"); 
    }     
  }
}
