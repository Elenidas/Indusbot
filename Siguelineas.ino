#include <Servo.h>

Servo servos[13];

/***   Global variables   ***/
int servo_derecho=9;
int servo_izquierdo=6;
int NEGRO=0;

/***   Function declaration   ***/

void setup()
{



  pinMode( 2 , INPUT);

  pinMode( 3 , INPUT);

}


void loop()
{
  int ir_derecho=digitalRead(2);
  int ir_izquierdo=digitalRead(3);
  if (ir_derecho == NEGRO) {
    servos[servo_izquierdo].attach(servo_izquierdo);
    servos[servo_izquierdo].write(180);
    delay(10);
   }else {
    servos[servo_izquierdo].attach(servo_izquierdo);
    servos[servo_izquierdo].write(90);
    delay(10);
   }
  if (ir_izquierdo == NEGRO) {
    servos[servo_derecho].attach(servo_derecho);
    servos[servo_derecho].write(0);
    delay(10);
   }else {
    servos[servo_derecho].attach(servo_derecho);
    servos[servo_derecho].write(90);
    delay(10);
   }

}

/***   Function definition   ***/
