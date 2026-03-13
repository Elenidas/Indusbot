#include <Servo.h>
//#include <EasyBuzzer.h>         esta en formato texto porque no esta la libreria descargada
Servo servos[13];
int servo_brotar=11;      //motor para rotar el brazo
int servo_blevantar=12;   //motor que levanta el primer brazo
int servo_bbrazo=13;       //motor que levanta el segundo brazo
int servo_protar=14;       //motor que rota la pinza
int servo_pabrir=15;       //motor que abre y cierra  la pinza
int buzzer=16;
int dato=0;
int estado=0;
int giropinza=0;
int girobrazo=0;
int alturabrazo1=0;
int alturabrazo2=0;
void setup() {
  // put your setup code here, to run once:
servos[servo_brotar].attach(servo_brotar);
servos[servo_blevantar].attach(servo_blevantar);
servos[servo_bbrazo].attach(servo_bbrazo);
servos[servo_protar].attach(servo_protar);
servos[servo_pabrir].attach(servo_pabrir);
//EasyBuzzer.setPin(buzzer);    //EasyBuzzer.beep(frecuencia,beeps)
}

void loop() {
  // put your main code here, to run repeatedly:
abrirpinza();
rotarpinzad();
rotarpinzai();
rotarbrazod();
rotarbrazoi();
levantarbrazo1();
bajarbrazo1();
levantarbrazo2();
bajarbrazo2();
}
void abrirpinza(){
  if (dato==1){
    if (estado==180){
      estado=0;
    }else{
      estado=180;
    }
    servos[servo_pabrir].write(estado);
    dato=0;
  }
}
void rotarpinzad(){
  if (dato==2){
    if (giropinza<180){
      giropinza++;
      servos[servo_protar].write(giropinza);
    }else{
     //EasyBuzzer.beep(200,2); 
    }
    dato=0;
  }
}
void rotarpinzai(){
  if (dato==3){
    if (giropinza>0){
      giropinza++;
      servos[servo_protar].write(giropinza);
    }else{
      //EasyBuzzer.beep(200,2);
    }
    dato=0;
  }
}
void rotarbrazod(){
  if (dato==4){
    if (girobrazo<180){
      girobrazo++;
      servos[servo_brotar].write(girobrazo);
    }else{
      //EasyBuzzer.beep(200,2);
    }
    dato=0;
  }
}
void rotarbrazoi(){
  if (dato==5){
    if (girobrazo>0){
      girobrazo--;
      servos[servo_brotar].write(girobrazo);
    }else{
      //EasyBuzzer.beep(200,2);
    }
    dato=0;
  }
}
void levantarbrazo1(){
  if (dato==6){
    if (alturabrazo1<180){
      alturabrazo1++;
      servos[servo_blevantar].write(alturabrazo1);
    }else{
      //EasyBuzzer.beep(200,2);
    }
    dato=0;
  }
}
void bajarbrazo1(){
  if (dato==7){
    if (alturabrazo1>0){
      alturabrazo1--;
      servos[servo_blevantar].write(alturabrazo1);
    }else{
      //EasyBuzzer.beep(200,2);
    }
    dato=0;
  }
}
void levantarbrazo2(){
  if (dato==8){
    if (alturabrazo2<180){
      alturabrazo2++;
      servos[servo_bbrazo].write(alturabrazo2);
    }else{
      //EasyBuzzer.beep(200,2);
    }
    dato=0;
  }
}
void bajarbrazo2(){
  if (dato==9){
    if (alturabrazo2>0){
      alturabrazo2--;
      servos[servo_bbrazo].write(alturabrazo2);
    }else{
      //EasyBuzzer.beep(200,2):
    }
    dato=0;
  }
}
