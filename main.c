/* 
 * File:   main.c
 * Author: Alan Cruz
 *
 * Created on 20 de septiembre de 2021, 12:26 PM
 */

#include <stdio.h>

#include <xc.h>
#include "conf.h"
#include <stdlib.h>

     int vel = 500;

   int j = 0;
   int k = 0;
char buffer1[8];

    int l = 0;
int a,b,s;//DECLARAMOS VARIABLES DE TIPO ENTERO

 void tocar_nota(int duracion, float tfrec){  //funcion generadora de notas, periodo de la nota y duracion de esta
 
     int duracion2;
     duracion2 = (int)duracion/tfrec;
     tfrec = 255-((tfrec/2)/(.0002*128));

       for(b=0;b<duracion2;b++){
           
            PORTAbits.RA0 = 1;
           TMR0 = tfrec;
           while(INTCONbits.TMR0IF==0);
           INTCONbits.TMR0IF=0;
  
        PORTAbits.RA0=0;
         TMR0 = tfrec;
         while(INTCONbits.TMR0IF==0);
         INTCONbits.TMR0IF=0;
}
  
 }
 void silencio(int duracion, float tfrec){  //funcion generadora de notas, periodo de la nota y duracion de esta
     
     duracion = duracion/tfrec;
     tfrec = 255-((tfrec/2)/(.0002*128));

       for(b=0;b<duracion;b++){
            PORTAbits.RA0 = 0;
           TMR0 = tfrec;
           while(INTCONbits.TMR0IF==0);
           INTCONbits.TMR0IF=0;
  
        PORTAbits.RA0=0;
         TMR0 = tfrec;
         while(INTCONbits.TMR0IF==0);
         INTCONbits.TMR0IF=0;
}
 }


 void confT0(){
     //11000010
    T0CONbits.TMR0ON = 1; //encendido
      T0CONbits.T08BIT = 1;  //modo 8 bits
      T0CONbits.T0CS = 0; //modo temporizador tcy
      T0CONbits.T0SE = 0; //leer bajadas
      T0CONbits.PSA = 0;  //con preescalador
      T0CONbits.T0PS = 0b110; 
     
      INTCONbits.TMR0IE = 1;      // Habilitamos las interrupción por desborde de TIMER0


 }


 
 
 
 
/* double cancion[44][3] = 
     {
      {vel, 3.034,1},{vel, 3.034,1},{vel,3.034,1},{(vel*.75),3.82,1},{(vel*.25),2.55,1},{vel,3.034,1},{(vel*.75),3.82,1},{(vel*.25),2.551,1},{(vel*2),3.034,1},{(vel),2.028,1},
      {vel,2.028,1},{vel,2.028,1},{vel*.75,1.911,1},{vel*.25,2.551,1},{vel,3.61,1},{vel*.75,3.82,1},{vel*.25,2.551,1},{vel*2,3.034,1},{vel,1.517,1},{vel*.75,3.034,1},
      {vel*.25,3.034,1},{vel,1.517,1},{vel*.75,1.607,1},{vel*.25,1.703,1},{vel*.25,1.804,1},{vel*.25,1.911,1},{vel*.6,1.804,1},{vel*.2,1,0},{vel*.60,2.863,1},{vel,2.145,1},
      {vel*.75,2.273,1},{vel*.25,2.408,1},{vel*.25,2.551,1},{vel*.25,2.703,1},{vel*.6,2.551,1},{vel*.2,1,0},{vel*.6,3.822,1},{vel,3.608,1},{vel*.75,3.822,1},{vel*.25,2.551,1},
      {vel,3.034,1},{vel*.75,3.822,1},{vel*.25,2.551,1},{vel*5,3.034,1}
      };*/
      
  float cancion[44][3] =     
  {
 { 1, 3.034,1},{ 1, 3.034,1},{ 1,3.034,1},{( .75),3.82,1},{( .25),2.55,1},{ 1,3.034,1},{( .75),3.82,1},{( .25),2.551,1},{( 2),3.034,1},{(1),2.028,1},
 { 1,2.028,1},{ 1,2.028,1},{ (0.75),1.911,1},{ (0.25),2.551,1},{ 1,3.61,1},{ (0.75),3.82,1},{ (0.25),2.551,1},{ 2,3.034,1},{ 1,1.517,1},{ (0.75),3.034,1},
 { (0.25),3.034,1},{ 1,1.517,1},{ (0.75),1.607,1},{ (0.25),1.703,1},{ (0.25),1.804,1},{ (0.25),1.911,1},{ (0.60),1.804,1},{ (0.20),1,0},{ (0.60),2.863,1},{ 1,2.145,1},
 { (0.75),2.273,1},{ (0.25),2.408,1},{ (0.25),2.551,1},{ (0.25),2.703,1},{ (0.60),2.551,1},{ (0.20),1,0},{ (0.60),3.822,1},{ 1,3.608,1},{ (0.75),3.822,1},{ (0.25),2.551,1},
 { 1,3.034,1},{ (0.75),3.822,1},{ (0.25),2.551,1},{ 5,3.034,1}
 };
 
 void cancion1(){ 
     

for( j = 0; j < 44; j ++){
       
     if (PORTBbits.RB1 == 1) {
            while(PORTBbits.RB1 == 1);
            j = 45;
     }
          
    if (PORTBbits.RB0 == 1) {
            while(PORTBbits.RB0 == 1);
            k ++;
     }
         
        if(k >= 3){
                k = 0;
            }
            else{
                switch (k){
                    case 0:
                    vel = 250;
                    break;
                    
                     case 1:
                    vel = 500;
                    break;
                    
                     case 2:
                    vel = 750;
                    break;
                }
               
            }
        
        if(cancion[j][2] == 1){
            tocar_nota(vel*cancion[j][0],cancion[j][1]);
        }
        
        else if(cancion[j][2] == 0){
            silencio(vel*cancion[j][0],cancion[j][1]);
        } 
    }
  l = 0;
return;
 }



void main(void) {

    ADCON1 = 15;

    TRISA =  0b00010000;
     TRISB = 0b11111111;
    confT0();


    
    
    
while (1) { 
  
          
    if (PORTBbits.RB2 == 1) {
            while(PORTBbits.RB2 == 1);
            l ++;
     }
         
        if(l >= 3){
                l = 0;
            }
            else{
                switch (l){
                    case 0:
                    if (PORTBbits.RB1 == 1) {
            while(PORTBbits.RB1 == 1);
            cancion1();
     
     }
                    break;
                    
                     case 1:
                    if (PORTBbits.RB1 == 1) {
            while(PORTBbits.RB1 == 1);
                       cancion1();

     }
                    break;
                    
                     case 2:
                   if (PORTBbits.RB1 == 1) {
            while(PORTBbits.RB1 == 1);
            cancion1();
     }
                    break;
                }
               
            }
     
    }
   

    

    
    
    
    
}




