#include <Servo.h>
//#include <EasyBuzzer.h>
Servo servos[13];
int servo_der=9;
int servo_izq=10;
int delante=0;
int detras=0;
int izquierda=0;
int derecha=0;
int giro90=15;        //introducir el tiempo que tarda el robot en dar un giro de 90 grados
int giro180=30;       //introducir el tiempo que tarda el robot en dar un giro de 180 grados
float girod=90;
float giroi=90;
int comprobante=0;
int cuentaatras=0;
int dato=0;
int programa=0;
int filas=0;
int filash=0;
byte movimiento[500][2];
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
introduceprograma();
programarun();
interrupcion();
}
void introduceprograma(){       
  if (programa==0){             
    nparado();
    nadelante();
    natras();
    ngiroderecha();
    ngiroizquierda();
    ndiagonaldar();
    ndiagonaldab();
    ndiagonaliar();
    ndiagonaliab();
    servos[servo_der].write(girod);               
    servos[servo_izq].write(giroi);
    movimiento[filas][0]=girod;
    movimiento[filas][1]=giroi;
    filas++;
    if(dato==9){
      programa=1;
      dato=0;
    }
  }
}
void nadelante(){
  if (dato==1){
    girod=180;
    giroi=0;
    dato=0;
  }
}
void ngiroderecha(){
  if (dato==2){
    girod=180;
    giroi=90;
    dato=0;
  }
}
void ngiroizquierda(){
  if (dato==3){
    girod=90;
    giroi=0;
    dato=0;
  }
}
void natras(){
  if (dato==4){
    girod=0;
    giroi=180;
    dato=0;
  }
}
void ndiagonaldar(){
  if (dato==5){
    girod=180;
    giroi=45;
    dato=0;;
  }
}
void ndiagonaldab(){
  if (dato==6){
    girod=135;
    giroi=180;
    dato=0;
  }
}
void ndiagonaliar(){
  if (dato==7){
    girod=135;
    giroi=0;
    dato=0;
  }
}
void ndiagonaliab(){
  if (dato==8){
    girod=180;
    giroi=135;
    dato=0;
  }
}
void nparado(){
  if (dato==0){
    comprobante++;
    if (comprobante==10){
      girod=90;
      giroi=90;
      comprobante=0;
    }
  }
}
void programarun(){          
  if(programa==1){
    if (filash<filas){
    servos[servo_der].write(movimiento[filash][0]);
    servos[servo_izq].write(movimiento[filash][1]);
    filash++;
    }else{
      servos[servo_der].write(90);
      servos[servo_izq].write(90);
      //EasyBuzzer.beep(200,3);
      delay(500);
      filash=0;
    }
  }
}
void interrupcion(){          
  if (dato==10){
    programa=0;
    dato=0;
    filas=0;
  }
}
