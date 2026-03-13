#include <Servo.h>
Servo servos[13];
float girod=90;
float giroi=90;
int servo_der=9;
int servo_izq=10;
int central = 0;
int der1 = 0;
int izq1 = 0;
int der2 = 0;
int izq2 = 0;
int NEGRO =0;
int BLANCO =1;
int espera =0;
int blancazo=0;
int suma=0;
int ultimalectura;
int contador=0;
int giro180=900;           //valor real
int deteccion=0;
int tiempo;
void setup() {
  // put your setup code here, to run once:
pinMode(3,INPUT);
  // central
pinMode(4,INPUT);
  //primero derecha
pinMode(2,INPUT);
  //primero izquierda
pinMode(5,INPUT);
  //segundo derecha
pinMode(1,INPUT);
  //segundo izquierda
servos[servo_der].attach(servo_der);
  //motor derecho
servos[servo_izq].attach(servo_izq);
  //motor izquierdo
}

void loop() {
  // put your main code here, to run repeatedly:
central=digitalRead(3);
der1=digitalRead(4);
izq1=digitalRead(2);
der2=digitalRead(5);
izq2=digitalRead(1);
suma=central+der1+der2+izq1+izq2;
inicio();
motor();
}
void inicio(){
  avanza();
  girodcha();
  giroizda();
  blanco();
}
void motor(){
  servos[servo_der].write(girod);
  servos[servo_izq].write(giroi);
  deteccion=0;
}
void avanza(){
 if(deteccion==0){ 
  if(central==NEGRO){
    girod=180;
    giroi=0;
    deteccion=1;
  }
 }
}
void girodcha(){
 if(deteccion==0){
  if(der1 == NEGRO){
    if(der2== NEGRO){
      girod= constrain(girod -10,0,180);           //dejo el 0 para que si necesita hacer un giro muy brusco pueda girar sobre sí mismo
  } else{
   girod= constrain(girod -5,0,180);
  }
  giroi=0;                //así evitamos el que vaya marcha atrás aunque giren las 2 ruedas a 0
  deteccion=1;
  ultimalectura=1;
}
}  
}
void giroizda() {
 if(deteccion==0){ 
  if(izq1==NEGRO){
    if(izq2==NEGRO){
      giroi= constrain(giroi +10,0,180);
    }else{
   giroi= constrain(giroi +5,0,180);
    }
    girod=180;
    deteccion=1;
    ultimalectura=2;
  }
}
}
void blanco(){
 if(deteccion==0){ 
  if (suma==5){
    blancazo++;
    if(blancazo==7000){
      if (ultimalectura==1){
        girod=180;
        giroi=135;
        contador=millis();
         while(central==BLANCO){
            servos[servo_der].write(girod);
            servos[servo_izq].write(giroi);
            central=digitalRead(3);
            tiempo=millis()-contador;
            if (tiempo>=giro180){
              central=NEGRO;
            }
         }
       if (tiempo>=giro180){
        girod=45;
        giroi=0;
         while(central==BLANCO){
            servos[servo_der].write(girod);
            servos[servo_izq].write(giroi);
            central=digitalRead(3);
         } 
       }
      }
      if (ultimalectura==2){
        girod=45;
        giroi=0;
        contador=millis();
        while(central==BLANCO){
          servos[servo_der].write(girod);
          servos[servo_izq].write(giroi);
          central=digitalRead(3);
          tiempo=millis()-contador;
          if (tiempo>=giro180){
            central=NEGRO;
          }
         }
       if (tiempo>=giro180){
        girod=180;
        giroi=135;
         while(central==BLANCO){
            servos[servo_der].write(girod);
            servos[servo_izq].write(giroi);
            central=digitalRead(3);
         } 
       }
      }
    }
  }else{
    blancazo=0;
  }
  deteccion=1;
}
}
