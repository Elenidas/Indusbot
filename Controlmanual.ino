#include <Servo.h>
Servo servos[13];
int servo_der=9;
int servo_izq=10;
int delante=0;
int detras=0;
int izquierda=0;
int derecha=0;
int giro90=15;        //introducir el tiempo que tarda el robot en dar un giro de 90 grados
int giro180=30;       //introducir el tiempo que tarda el robot en dar un giro de 180 grados
int bluetooth1=0;
int bluetooth2=0;
int bluetooth3=0;
int bluetooth4=0;
int bluetooth5=0;
int bluetooth6=0;
int bluetooth7=0;
int bluetooth8=0;
int bluetooth9=0;
int bluetooth10=0;
int bluetooth11=0;
int bluetooth12=0;
int bluetooth13=0;
float girod=90;
float giroi=90;
int comprobante=0;
int cuentaatras=0;
int dato=0;
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
}
void loop() {
  // put your main code here, to run repeatedly:
parado();
adelante();
giroderecha();
giroizquierda();
atras();
diagonaldar();
diagonaldab();
diagonaliar();
diagonaliab();
servos[servo_der].write(girod);
servos[servo_izq].write(giroi);
}
void parado(){
  if (dato==0){
    comprobante++;
    if (comprobante==10){
    girod=90;
    giroi=0;
    comprobante=0;
    }
  }
}
void adelante(){
  if (dato==1){
    girod=180;
    giroi=0;
    dato=0;
  }
}
void giroderecha(){
  if (dato==2){
    girod=180;
    giroi=90;
    dato=0;
  }
}
void giroizquierda(){
  if (dato==3){
    girod=90;
    giroi=0;
    dato=0;
  }
}
void atras(){
  if (dato==4){
    girod=0;
    giroi=180;
    dato=0;
  }
}
void diagonaldar(){
  if (dato==5){
    girod=180;
    giroi=45;
    dato=0;
  }
}
void diagonaldab(){
  if (dato==6){
    girod=135;
    giroi=180;
    dato=0;
  }
}
void diagonaliar(){
  if (dato==7){
    girod=135;
    giroi=0;
    dato=0;
  }
}
void diagonaliab(){
  if (dato==8){
    girod=180;
    giroi=135;
    dato=0;
  }
}
