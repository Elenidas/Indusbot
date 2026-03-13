#include <Servo.h>
Servo servos[13];
int servo_der=9;
int servo_izq=10;
int central = 0;
int der1 = 0;
int izq1 = 0;
int der2 = 0;
int izq2 = 0;
int NEGRO =0;
int COCHE =0;
int VACIO=1;
int delanted=0;
int delantei=0;
int detras=0;
int izquierda=0;
int derecha=0;
int girod=90;
int giroi=90;
int giro90=850;    //introducir el tiempo que tarda el robot en dar un giro de 90 grados  
int giro180=1120;   //introducir el tiempo que tarda el robot en dar un giro de 180 grados
int absolutanada=0;
int control=0;
int radio=5500;     //introducir aquí el "tiempo" que tarda en recorrer 55 cm con este sistema de medida
int trabajo;
int empuje=700;
void setup() {
  // put your setup code here, to run once:
pinMode(4,INPUT);                       //siguelineas primero derecha
pinMode(2,INPUT);                       // siguelineas primero izquierda
pinMode(5,INPUT);                       //siguelineas segundo derecha
pinMode(1,INPUT);                       //siguelineas segundo izquierda
pinMode(6,INPUT);                       //sensor delantero
pinMode(7,INPUT);                       //sensor izquierda
pinMode(8,INPUT);                       //sensor derecha
pinMode(11,INPUT);                      //sensor trasero
pinMode(12,INPUT);
servos[servo_der].attach(servo_der);    //motor derecho
servos[servo_izq].attach(servo_izq);  
}

void loop() {
  // put your main code here, to run repeatedly:
  central = digitalRead(3);
der1 = digitalRead(4);
izq1 = digitalRead(2);
der2 = digitalRead(5);
izq2 = digitalRead(1);
delanted = digitalRead(6);
delantei= digitalRead(12);        //cambiar los imput para que funcionen mejor
detras = 1;//digitalRead(11);
izquierda = digitalRead(8);
derecha = digitalRead(7);
espiral();
atacafrented();
atacafrentei();
atacafrente();
atacadcha();
atacaizq();
atacadetras();
lineaizq();
lineadcha();
lineadelante();
motores();
}
void motores(){
servos[servo_der].write(girod);
servos[servo_izq].write(giroi); 
}
void atacafrente(){
  if (delanted+delantei==COCHE){
    girod=180;
    giroi=0;
  }
}
void atacafrented(){
  if (delanted==COCHE){
    girod=girod-20;
    giroi=0;
  }
}
void atacafrentei(){
  if (delantei==COCHE){
    girod=180;
    giroi=giroi+20;
  }
}
void lineadcha(){
  if (der2==NEGRO || der1==NEGRO){
    if (delanted==COCHE || delantei==COCHE){
      delay(empuje);
      girod=0;
      giroi=180;
      motores();
      delay(empuje +50);
    }
    girod=180;
    giroi=180;
    motores();
    if (derecha+izquierda+delanted+delantei+detras==5){
      delay(random(100,750));
    }else{
    delay(giro90);
  }
 } 
}
void lineaizq(){
  if (izq2==NEGRO || izq1==NEGRO){
    if (delanted==COCHE || delantei==COCHE){
      delay(empuje);
      girod=0;
      giroi=180;
      motores();
      delay(empuje  +50);
    }
    girod=0;
    giroi=0;
    motores();
    if (derecha+izquierda+delanted+delantei+detras==5){
      delay(random(100,750));
    }else{
    delay(giro90);
  }
 }  
}
void lineadelante(){
  if(central==NEGRO){
    if (delanted==COCHE || delantei==COCHE){
      delay(empuje);
      girod=0;
      giroi=180;
      delay(empuje +50);
    }
    girod=180;
    giroi=180;
    motores();
    delay(giro180);
  }
}
void atacadcha(){
  if (derecha==COCHE){
    girod=0;
    giroi=0;
    motores();
    delay(giro90);
  }
}
void atacaizq(){
if (izquierda==COCHE){
  girod=180;
  giroi=180;
  motores();
  delay(giro90);
}
}
void atacadetras(){
  if (detras==COCHE){
    girod=180;
    giroi=180;
    motores();
    delay(giro180);
  }
}
void espiral(){
  if(delanted+delantei+derecha+izquierda+detras+der1+der2+izq1+izq2+central==10){
  girod=145;
  giroi=35;
  }
}
