#include <SoftwareSerial.h>
#include <Servo.h>
#define servo_der 5
#define servo_izq 4
//#define servo_brotar 6
//#define servo_blevantar 7
//#define servo_bbrazo 8
//#define servo_protar 9
//#define servo_pabrir 10
#define sensor_central 16
#define sensor_der1 17
#define sensor_der2 18
#define sensor_izq1 15
#define sensor_izq2 14
#define sensor_delanterod 7
#define sensor_delanteroi 6
#define sensor_laterald 8
#define sensor_laterali 9
#define sensor_trasero 13
#define buzzer 12
#define pulsador1 2
#define pulsador2 3
#define COCHE 0
#define NEGRO 0
#define VACIO 1
#define BLANCO 1
#define giro90 650     //introducir el tiempo que tarda el robot en dar un giro de 90 grados
#define giro180 1120      //introducir el tiempo que tarda el robot en dar un giro de 180 grados
#define RADIO 55        //introducir el tiempo que tarda el robot en recorrer 55cm con este sistema de medida
Servo servos[13];
SoftwareSerial miBT(10,11);
String valor;
int dato=0;
volatile int programa=0;
int central=0;
int der1=0;
int der2=0;
int izq1=0;
int izq2=0;         //sensores de linea
int delante=0;
int derecha=0;
int izquierda=0;
int detras=0;     //sensores de objetos
int comprobante=0;
float girod=90;
float giroi=90; 
int cuentaatras=0;
int ultimalectura=0;
unsigned long ultimocomando=0;
int tiempomaximo=1000;
int delanted=0;
int delantei=0;
int empuje=700;
int suma=0;
int deteccion=0;
unsigned long blancazo=0;
int contador=0;
int tiempo=0;
unsigned long ultimainterrupcion=0;
unsigned long tiempoactual=0;
int tono=0;
void setup() {
  // put your setup code here, to run once:
attachInterrupt(digitalPinToInterrupt(2),cambio2,FALLING);
attachInterrupt(digitalPinToInterrupt(3),cambio3,FALLING);
miBT.begin(38400);
miBT.flush();
Serial.begin(9600);
pinMode(pulsador1,INPUT_PULLUP);
pinMode(pulsador2,INPUT_PULLUP);
pinMode(buzzer, OUTPUT);
pinMode(servo_der, OUTPUT);
pinMode(servo_izq, OUTPUT);
//pinMode(servo_brotar, OUTPUT);
//pinMode(servo_blevantar, OUTPUT);
//pinMode(servo_bbrazo, OUTPUT);
//pinMode(servo_protar, OUTPUT);
//pinMode(servo_pabrir, OUTPUT);
pinMode(sensor_central, INPUT);
pinMode(sensor_der1, INPUT);
pinMode(sensor_der2, INPUT);
pinMode(sensor_izq1, INPUT);
pinMode(sensor_izq2, INPUT);
pinMode(sensor_delanterod, INPUT);
pinMode(sensor_delanteroi, INPUT);
pinMode(sensor_laterald, INPUT);
pinMode(sensor_laterali, INPUT);
pinMode(sensor_trasero, INPUT);
servos[servo_der].attach(servo_der);
servos[servo_izq].attach(servo_izq);
//servos[servo_brotar].attach(servo_brotar);
//servos[servo_blevantar].attach(servo_blevantar);
//servos[servo_bbrazo].attach(servo_bbrazo);
//servos[servo_protar].attach(servo_protar);
//servos[servo_pabrir].attach(servo_pabrir);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
                //PROGRAMAS BLUETOOTH//
void bluetooth(){                                       //Hay dos formas para hacerlo, no sé cual funcionara, o funcionara  mejor
  if (miBT.available()){ 
   valor=miBT.readStringUntil('\n');
   dato=valor.toInt();
   ultimocomando=millis();
   Serial.println(dato);
   Serial.println(valor);
   cambiarprograma(dato);
  }
}
void cambiarprograma(int dato){
  if(dato>=30){
  programa=dato -30;
  tono=0;
  }
}
void cambio1(){
  programa=0;
}
void cambio2(){
  tone(buzzer,392,100);
    ultimainterrupcion=0;
  tiempoactual=millis();
  if((tiempoactual-ultimainterrupcion)>200){
  programa=1;
  }
  ultimainterrupcion=tiempoactual;

}
void cambio3(){
  tone(buzzer,392,100);
  ultimainterrupcion=0;
  tiempoactual=millis();
  if((tiempoactual-ultimainterrupcion)>200){
  programa=2;
  }
  ultimainterrupcion=tiempoactual;
}
void cambio4(){
  programa=6;
}
////////////////////////////////////////////////////////////////////////////////////////////
                    //PROGRAMAS GENERALES//
void lecturalinea(){
  central=digitalRead(sensor_central);
  der1=digitalRead(sensor_der1);
  der2=digitalRead(sensor_der2);
  izq1=digitalRead(sensor_izq1);
  izq2=digitalRead(sensor_izq2);
}
void lecturaobstaculo(){
  delanted=digitalRead(sensor_delanterod);
  delantei=digitalRead(sensor_delanteroi);
  derecha=digitalRead(sensor_laterald);
  izquierda=digitalRead(sensor_laterali);
  detras= 1; //digitalRead(sensor_trasero);
}
void motores(){
  servos[servo_der].write(girod);
  servos[servo_izq].write(giroi);
}
////////////////////////////////////////////////////////////////////////////////////////
                //SIGUELINEAS//
void inicio(){
  lectura();
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
void lectura(){
  if(der1==NEGRO || der2==NEGRO){
    ultimalectura=1;
  }
  if(izq1==NEGRO || izq2==NEGRO){
    ultimalectura=2;
  }
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
      girod= constrain(girod -20,0,180);           //dejo el 0 para que si necesita hacer un giro muy brusco pueda girar sobre sí mismo
  } else{
   girod= constrain(girod -10,0,180);
  }
  giroi=0;                //así evitamos el que vaya marcha atrás aunque giren las 2 ruedas a 0
  deteccion=1;
}
}  
}
void giroizda() {
 if(deteccion==0){ 
  if(izq1==NEGRO){
    if(izq2==NEGRO){
      giroi= constrain(giroi +20,0,180);
    }else{
   giroi= constrain(giroi +10,0,180);
    }
    girod=180;
    deteccion=1;
  }
}
}
void blanco(){
 if(deteccion==0){ 
  if (suma==5){
    blancazo++;
    if(blancazo>=7000){
      if (ultimalectura==1){
        contador=millis();
        while(central+der1+der2+izq1+izq2==5){
        girod=constrain(girod -20,0,180);
        giroi=0;
        servos[servo_der].write(girod);
        servos[servo_izq].write(giroi);
        lecturalinea();
        tiempo=millis()-contador;
        if(tiempo>=giro180){
          suma==0;
        }
         }
       if (tiempo>=giro180){
       while(central+der1+der2+izq1+izq2==5){
        girod=180;
        giroi=constrain(giroi +20,0,180);
        servos[servo_der].write(girod);
        servos[servo_izq].write(giroi);
        lecturalinea();
         } 
       }
      }
      if (ultimalectura==2){
        contador=millis();
        while(central+der1+der2+izq1+izq2==5){
          girod=180;
          giroi=constrain(giroi +20,0,180);
          servos[servo_der].write(girod);
          servos[servo_izq].write(giroi);
          lecturalinea();
          tiempo=millis()-contador;
          if (tiempo>=giro180){
            suma=0;
          }
         }
       if (tiempo>=giro180){
         while(central==BLANCO){
            girod=constrain(girod -20,0,180);
            giroi=0;
            servos[servo_der].write(girod);
            servos[servo_izq].write(giroi);
            lecturalinea();
         } 
       }
      }
      blancazo=0;
    }
  }
  }
  deteccion=1;
}

void siguelineas(){
  lecturalinea();
  suma=central+der1+der2+izq1+izq2;
  inicio();
  motor();
}
///////////////////////////////////////////////////////////////////////////////////////
                //SUMO AUTOMATICO//
void sumoautomatico(){
  lecturalinea(); 
  lecturaobstaculo();
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
  motor();
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
    contador++;
  }
}
void atacafrentei(){
  if (delantei==COCHE){
    girod=180;
    giroi=giroi+20;
    contador++;
  }
}
void lineadcha(){
  if (der2==NEGRO || der1==NEGRO){
     tone(buzzer,329,100);
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
     tone(buzzer,329,100);
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
     tone(buzzer,329,100);
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
/////////////////////////////////////////////////////////////////////////////////////////
                //SUMO MANUAL//
void sumomanual(){
parado();
adelante();
giroderecha();
giroizquierda();
atras();
diagonaldar();
diagonaldab();
diagonaliar();
diagonaliab();
evasiond();
evasioni();
giro90d();
giro90i();
giro180d();
motores();    
}
void parado(){
  if((millis()-ultimocomando)>tiempomaximo){
    girod=90;
    giroi=90;
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
void evasiond(){
  if (dato==9){
    if (cuentaatras>=10){
      girod=135;
      giroi=180;
      cuentaatras--;
    } 
    if (cuentaatras<10){
      girod=0;
      giroi=180;
      cuentaatras--;
    }
    if (cuentaatras==0){
      cuentaatras=20;
       ultimalectura=0;
      dato=0;
    }
  }
}
void evasioni(){
  if (dato==10){
    if (cuentaatras>=10){
      girod=180;
      giroi=135;
      cuentaatras--;
    }
    if (cuentaatras<10){
      girod=0;
      giroi=180;
      cuentaatras--;
    }
    if (cuentaatras==0){
      cuentaatras=20;
       ultimalectura=0;
      dato=0;
    }
  }
}
void giro90d(){
  if (dato==11){
    servos[servo_der].write(180);
    servos[servo_izq].write(180);
    delay(giro90);
     ultimalectura=0;
    dato=0;
  }
}
void giro90i(){
  if (dato==12){
    servos[servo_der].write(0);
    servos[servo_izq].write(0);
    delay(giro90);
     ultimalectura=0;
    dato=0;
  }
}
void giro180d(){
  if (dato==13){
    servos[servo_der].write(180);
    servos[servo_izq].write(180);
    delay(giro180);
     ultimalectura=0;
    dato=0;
  }
}
/////////////////////////////////////////////////////////////////////////////////////////
                //CONTROL MANUAL//
void controlmanual(){
  
}
//////////////////////////////////////////////////////////////////////////////////////////
                //CONTROL AUTOMATICO//
void controlautomatico(){
  
}
/////////////////////////////////////////////////////////////////////////////////////////
                //RECUERDO ORDENES//
void recuerdoordenes(){
  
}
/////////////////////////////////////////////////////////////////////////////////////////
                  //DETECCION COLORES//
void deteccioncolores(){
  
}
void sonido(){
    if(tono==0){
  tone(buzzer,329,100);
  delay(100);
  delay(1000);
  tone(buzzer,392,100);
  delay(100);
  delay(1000);
  tone(buzzer,494,100);
  delay(100);
  delay(1000);
  tone(buzzer,261,100);
  delay(100);
  tone(buzzer,293,100);
  delay(100);
  tone(buzzer,261,300);
  delay(300);
  tono=1;
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////7
void loop() {
  // put your main code here, to run repeatedly:
  bluetooth();
  switch(programa){
  case 0:
  //nada para que este quieto al principio
  girod=90;
  giroi=90;
  motores();
  sonido();
  break;
  case 1:
  siguelineas();
  break;
  case 2:
  sumoautomatico();
  break;
  case 3:
  sumomanual();
  break;
  case 4:
  controlmanual();
  break;
  case 5:
  controlautomatico();
  break;
  case 6:
  deteccioncolores();
  break;
  case 7:
  recuerdoordenes();
  break;
  default:
  cambio1();
}
}
