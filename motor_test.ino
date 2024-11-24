#include <Servo.h>
Servo servo_1 ;


void setup() {
  // put your setup code here, to run once:
  servo_1.attach(10);
 
}

void loop() {
  // put your main code here, to run repeatedly:
  servo_1.write(80);
  delay(100);

  servo_1.write (180);
  delay (100);

 
  

}
