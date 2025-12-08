
/*  ----------------------------------------------------------------

--------------------------------------------------------------------  
*/
String secuencia="1000R600R1000R600S";
#define IN1MD  12
#define IN2MD  11
#define IN3MD  10
#define IN4MD  9
#define IN1MI  7
#define IN2MI  6
#define IN3MI  5
#define IN4MI  4
#define BUZZR  13
double RadioRueda=32;
int EntreEjes=111; //Distancia entre las ruedas
int Morro=110; //Distancia del frente al eje de giro
String crt=""; // Para almacenar cada caracter leido
String sec=""; // Para almacenar una secuencia parcial
double miPI=3.14159;
double K; // Constante para el paso de mm a ciclos

int pasos=4096; //Pasos por vuelta
int StepsD = 0;
int StepsI = 7;
int NCiclos=0;
boolean PrimeraV=true;

int Paso [ 8 ][ 4 ] =
    {   {1, 0, 0, 0},
        {1, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 1},
        {0, 0, 0, 1},
        {1, 0, 0, 1}
     };

void setup()
    {
      pinMode(IN1MD, OUTPUT); 
      pinMode(IN2MD, OUTPUT); 
      pinMode(IN3MD, OUTPUT); 
      pinMode(IN4MD, OUTPUT); 
      pinMode(IN1MI, OUTPUT); 
      pinMode(IN2MI, OUTPUT); 
      pinMode(IN3MI, OUTPUT); 
      pinMode(IN4MI, OUTPUT);
      pinMode(BUZZR, OUTPUT); 
      K=pasos/(2*miPI*RadioRueda);
    }

void loop() 
{     
      delay(3000);
      doremi();
      int longitud=secuencia.length();
        for (int i = 0; i <= longitud; i++) {
          crt=secuencia.substring(i,i+1);
          sec += String(crt);
          if ((crt == "L") || ((crt == "R") || (crt == "S"))) {
            if (sec.length() == 1) {
              EjecutaOrden(sec);
              sec="";
             }else {
               sec=sec.substring(0,sec.length()-1);      
               EjecutaOrden(sec);
               sec="";             
               EjecutaOrden(crt);
             }
           }
        }  
        doremi(); 
}
void EjecutaOrden (String x) {
  pita();
  if (x == "L") {
    NCiclos=int(2*miPI*EntreEjes/4*K);  
    giraI(NCiclos); 
   }else if (x == "R") {
    NCiclos=int(2*miPI*EntreEjes/4*K);       
    giraD(NCiclos);
   }else if (x == "S") {
    delay(5000);
   }else {
      if (PrimeraV== true){
        NCiclos=int((x.toInt()+Morro-EntreEjes*0.5)*K);      
        avanza(NCiclos);
        PrimeraV=false;
      }else {
        NCiclos=int((x.toInt()-EntreEjes)*K);      
        avanza(NCiclos);
      }
   }
 }
 
void avanza(int ciclos)
{
      while(ciclos>0)
         {
          digitalWrite( IN1MD, Paso[StepsD][ 0] );
           digitalWrite( IN1MI, Paso[StepsI][ 0] );
          digitalWrite( IN2MD, Paso[StepsD][ 1] );
           digitalWrite( IN2MI, Paso[StepsI][ 1] );
          digitalWrite( IN3MD, Paso[StepsD][ 2] );
            digitalWrite( IN3MI, Paso[StepsI][ 2] );
          digitalWrite( IN4MD, Paso[StepsD][ 3] );
            digitalWrite( IN4MI, Paso[StepsI][ 3] );
          ciclos-- ;  // Un paso menos
          delay (1) ;
          StepsD++;
           if (StepsD>7)
               StepsD=0 ;
           StepsI--;
           if (StepsI<0)
               StepsI=7 ;
         } 
  
}
void giraD(int ciclos)
{
      while(ciclos>0)
         {
          digitalWrite( IN1MI, Paso[StepsI][ 0] );
          digitalWrite( IN2MI, Paso[StepsI][ 1] );
          digitalWrite( IN3MI, Paso[StepsI][ 2] );
          digitalWrite( IN4MI, Paso[StepsI][ 3] );
          ciclos-- ;  // Un paso menos
          delay (1) ;
           StepsI--;
           if (StepsI<0)
               StepsI=7 ;
         } 
  
}
void giraI(int ciclos)
{
      while(ciclos>0)
         {
          digitalWrite( IN1MD, Paso[StepsD][ 0] );
          digitalWrite( IN2MD, Paso[StepsD][ 1] );
          digitalWrite( IN3MD, Paso[StepsD][ 2] );
          digitalWrite( IN4MD, Paso[StepsD][ 3] );
          ciclos-- ;  // Un paso menos
          delay (1) ;
          StepsD++;
           if (StepsD>7)
               StepsD=0 ;
         } 

}
void doremi()
{
    tone(BUZZR,261,200);//DO
    delay(200);
    tone(BUZZR,293,200);//Re
    delay(200);
    tone(BUZZR,329,200);//Mi
    delay(200);
    tone(BUZZR,329,200);//Mi
    delay(200);
    tone(BUZZR,293,200);//Re
    delay(200);
    tone(BUZZR,261,200);//DO
    
}
void pita()
{
    tone(BUZZR,494,300);//Si
}
