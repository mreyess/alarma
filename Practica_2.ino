/*
 * Autor: Reyes Solis Miguel Angel 
 * Programa: Sistema Notificador de llegada de individuos
 * Objetivo: Desarrollar una alarma con arduino para el acceso a una puerta. Cuando la puerta se abra,
 *           la alarma debe sonar.
 *           Asi mismo se debe reducir el consumo de energía al mínimo. Mientras la alarma no esté sonando el
 *           arduino deberá consumir la mínima cantidad de energía.
 *           Cuando la puerta se cierre esta deberá de dejar de sonar y regresar al estado de bajo
 *           consumo energético.
*/


#include "LowPower.h" // Incluimos la libreria que nos permitira manipular el consumo de energis
#define alarma 3     // Definimos el pin por el cual sonara la alarma al activarse la puerta
#define puerta 2      // Definimos el pin que simulara la puerta que en este caso se hizo mediante un reed switch
#define foco 13       // Definimos el pin que simulara el foco que se encendera cuando la puesrta se abra


void setup() {   
  
  pinMode(alarma, OUTPUT); // Señalamos que el pin de la alarma sera una señal de salida digital 
  pinMode(foco, OUTPUT);    // Señalamos que el pin del foco sera una señal de salida digital 
  attachInterrupt(digitalPinToInterrupt(puerta), abrePuerta, LOW); //Señalamos que cuando la puerta se abra(es decir, que el red switch se active) entonces ejecute la interrupcion de hardware abrePuerta
  digitalWrite(foco, LOW);  // Inicializamos con el foco apagado  
  digitalWrite(alarma, LOW);//Inicializamos la alarma en silencio
}

void loop() {
    /*Señalamos que miestras no se abra la puerta entonces que el arduino entre en un modo de consumo de energia minimo 
    mediante la funcion powerDown en donde señalamos que duerma indefinidamente mientras no se presente una interrupcion 
    de hardware, asi mismo le decimos que miestras duerme apague los convertidores Analógico a digital (ADC_OFF) asi como el
   circuito de Brown Out Detection (BOD_OFF), que es un circuito para detectar niveles bajos de tensión.
   Apagarlo ayuda a reducir consumo.*/
   LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF); 
}

//Definimos el metodo que servira como interrupcion de hardware para que el arduino pueda salir del modo sleep
void abrePuerta(){
  // Ordenamos que miestras la puerta este abierta suene la alarma y que al mismo tiempo el foco enciende
   digitalWrite(foco, HIGH); 
   for(int contador = 0; contador <= 255; contador += 5){
    analogWrite(alarma, contador);
    delay(300);
    }

   for(int contador = 255; contador >= 0; contador -=5){
    analogWrite(alarma, contador);
    delay(300);
    
    }
    digitalWrite(foco, LOW);
    delay(300);
   
   }


   


