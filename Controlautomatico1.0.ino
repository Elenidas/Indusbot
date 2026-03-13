#include <Servo.h>
//#include <EasyBuzzer.h>         esta en formato texto porque no esta la libreria descargada
Servo servos[13];
int servo_der=7;
int servo_izq=8;
int central = 0;
int der1 = 0;
int izq1 = 0;
int der2 = 0;
int izq2 = 0;
int NEGRO =0;
int COCHE =0;
int OBSTACULO=0;
int VACIO=1;
int delante=0;
int detras=0;
int izquierda=0;
int derecha=0;
int girod=90;
int giroi=90;
int giro90=15;    //introducir el tiempo que tarda el robot en dar un giro de 90 grados  
int giro180=30;   //introducir el tiempo que tarda el robot en dar un giro de 180 grados
int escapa=0;
int desviaciond=0;
int desviacioni=0;
void setup() {
  // put your setup code here, to run once:
pinMode(3,INPUT);
  //siguelineas central
pinMode(4,INPUT);
  //siguelineas primero derecha
pinMode(2,INPUT);
  // siguelineas primero izquierda
pinMode(5,INPUT);
  //siguelineas segundo derecha
pinMode(1,INPUT);
  //siguelineas segundo izquierda
pinMode(6,INPUT);
  //sensor delantero
pinMode(7,INPUT);
  //sensor izquierda
pinMode(8,INPUT);
  //sensor derecha
pinMode(11,INPUT);
  //sensor trasero
servos[servo_der].attach(servo_der);
  //motor derecho
servos[servo_izq].attach(servo_izq);
  //motor izquierdo
delay(50);
servos[servo_der].write(135);
servos[servo_izq].write(135);
delay(random(0,100));
}
void loop() {
  // put your main code here, to run repeatedly:
central = digitalRead(3);
der1 = digitalRead(4);
izq1 = digitalRead(2);
der2 = digitalRead(5);
izq2 = digitalRead(1);
delante = digitalRead(6);
detras = digitalRead(11);
izquierda = digitalRead(7);
derecha = digitalRead(8);
avanzamos();
obstaculodelante();
marchaatras();
obstaculoderecha();
regresoderecha();
obstaculoizquierda();
regresoizquierda();
servos[servo_der].write(girod);
servos[servo_izq].write(giroi);
}
void avanzamos(){
  if (delante==VACIO){
    girod=135;              //comprobar a que velocidades arregladas va recto el robot
    giroi=45;               //sin ir demasiado rapido
  }
}
void obstaculodelante(){    //se puede hacer que gire aleatoriamente a derecha u izquierda
  if (delante==OBSTACULO){
    //EasyBuzzer.beep(200,2);
    giro90der();
    while(derecha==OBSTACULO){    //no funciona bien, se puede estrellar por delante sin notarlo
      servos[servo_der].write(135);   //al estar en un ciclo while
      servos[servo_izq].write(45);
    }
    giro90izq();
  }
}
void marchaatras(){
  if (delante+derecha+izquierda==OBSTACULO){
    //EasyBuzzer.beep(200,2);
    girod=45;
    giroi=135;
    while (escapa==0){
    escapad();
    escapai();
    }
    escapa=0;  
  }
}
void escapad(){
  if (derecha==VACIO){
    giro90der();
    escapa=1;
  }
}
void escapai(){
 if (izquierda==VACIO){
  giro90izq();
  escapa=1; 
 }
}
void giro90der(){
    servos[servo_der].write(0);
    servos[servo_izq].write(0);
    delay(giro90);
}
void giro90izq(){
    servos[servo_der].write(180);
    servos[servo_izq].write(180);
    delay(giro90);
}
void obstaculoderecha(){
  if (derecha==OBSTACULO){
    //EasyBuzzer.beep(200,2);
    girod=min(girod +15,150);   //se usa minimos y maximos para que si detecta de los dos lados la
    giroi=45;                   //respuesta sea seguir hacia delante entre ambos obstaculos sin tener
    desviaciond=desviaciond +1; //paradas nimovimientos raros
  }
}
void regresoderecha(){          //de esta forma intenta volver a su linea recta inicial
  if (derecha==VACIO){
    if (desviaciond>>0){
      girod=135;
      giroi=max(30,giroi -15);
      desviaciond=desviaciond -1;
    }
  }
}
void obstaculoizquierda(){
  if (izquierda==OBSTACULO){
    //EasyBuzzer.beep(200,2);
    girod=135;
    giroi=max(30,giroi -15);
    desviacioni=desviacioni +1;
  }
}
void regresoizquierda(){
  if (derecha==VACIO){
    if (desviacioni>>0){
      girod=min(girod +15,150);
      giroi=45;
      desviacioni=desviacioni -1;
    }
  }
}
