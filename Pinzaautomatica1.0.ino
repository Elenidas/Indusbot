#include <Servo.h>
Servo servos[13];
int servo_der=9;
int servo_izq=10;
int servo_caja=12;
int central = 0;
int der1 = 0;
int izq1 = 0;
int der2 = 0;
int izq2 = 0;
int NEGRO =0;
int COCHE =0;
int VACIO=1;
int BLANCO=1;
int delante=0;
int detras=0;
int izquierda=0;
int derecha=0;
int girod=90;
int giroi=90;
int giro90=15;    //introducir el tiempo que tarda el robot en dar un giro de 90 grados  
int giro180=30;   //introducir el tiempo que tarda el robot en dar un giro de 180 grados
int absolutanada=0;
int control=0;
int caja=0;
void setup() {
  // put your setup code here, to run once:
pinMode(3,INPUT);                       //siguelineas central
pinMode(4,INPUT);                       //siguelineas primero derecha
pinMode(2,INPUT);                       // siguelineas primero izquierda
pinMode(5,INPUT);                       //siguelineas segundo derecha
pinMode(1,INPUT);                       //siguelineas segundo izquierda
pinMode(6,INPUT);                       //sensor delantero
pinMode(7,INPUT);                       //sensor izquierda
pinMode(8,INPUT);                       //sensor derecha
pinMode(11,INPUT);                      //sensor trasero
servos[servo_der].attach(servo_der);    //motor derecho
servos[servo_izq].attach(servo_izq);    //motor izquierdo
servos[servo_caja].attach(servo_caja);  //servo caja

}

void loop() {
  // put your main code here, to run repeatedly:
avanza();
giroderecha();          //cuidado con el siguelineas se puede poner el mismo programa pero no hace el giro      
giroizquierda();       //brusco de 90 grados en las esquinas
girobruscod();
girobruscoi();
descarga();
}
void avanza(){
  if (central == NEGRO){
    girod = 180;
    giroi = 0;
  }
}
void giroderecha(){
  if(der1 == NEGRO){
   giroi= constrain(giroi +0.08,0,180);
 }
}
void giroizquierda() {
  if(izq1==NEGRO){
   girod= constrain(girod -0.08,0,180);
    }
}
void girobruscod(){
  if(der1+der2==NEGRO){
    delay(5);             //para que se salga un poco y al girar vuelva a dentro del circuito
    giroi=45;
    girod=45;
    while(central==BLANCO){
     servos[servo_der].write(girod);
     servos[servo_izq].write(giroi);
  }
 } 
}
void girobruscoi(){
  if (izq1+izq2==NEGRO){
    delay(5);
    giroi=135;
    girod=135;
    while(central==BLANCO){
      servos[servo_der].write(girod);
      servos[servo_izq].write(giroi);
  }
 }  
}
void descarga(){
  if (der1+izq1+central==NEGRO){
      girod=90;
      giroi=90;
      servos[servo_der].write(girod);
      servos[servo_izq].write(giroi);
    //EasyBuzzer.beep(3,200);
    servos[servo_caja].write(90);
    delay(100);
    caja=10;
    while (caja/=0){
       servos[servo_caja].write(80);
       servos[servo_caja].write(90);
       caja=caja -1;
    }
  }
}
void objeto(){
  if (izquierda==COCHE){        //debería ser objeto pero no quiero metero otra variable, darle una vuelta
    girod=90;
    giroi=90;
    servos[servo_der].write(girod);       
    servos[servo_izq].write(giroi);         //Aquí poner deteccion de color
    //EasyBuzer.beep(1,200);
  }
}
