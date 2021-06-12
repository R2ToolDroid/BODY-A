///Automatische Domebewegung Steuerung
///Doc Snyder Tool Droid DomeController
///für Arduino pro mini new branch

#include <SoftwareSerial.h>        // Durch diesen Include können wir die Funktionen 
#include <Servo.h>
#include <Wire.h>  
SoftwareSerial MainInput(14, 15); // Pin D14 ist RX, Pin D15 ist TX.
                                   // Die Funktion softSerial() kann nun wie Serial() genutzt werden.     

Servo LegMot;

#include "vars.h"
#include "Mdriver.h"
#include "command.h"


void setup(){

  LegMot.attach(PWM_OUT);
     
  Serial.begin(9600);
  MainInput.begin(9600);
   // set the digital pin as output:
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPinC, OUTPUT);
  
  //pinMode(STATUS_PIN, INPUT_PULLUP); 
  pinMode(SENSOR_CENTER,  INPUT_PULLUP);
  
  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generateB
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));
  //delay(2000);
  Serial.println("Body Leg Controler");
  Serial.println("...ready for Command_");
  
  //startseq();

   
}


void loop() {

    Comand();  
 
    BodyRot(tPos);
      if (debug){
     Serial.print(analogRead(LEG_POTI));
    }
 

  if (durchlauf == 10 ) {
   // center("L");
    } 
  
  #ifdef DEBUG
  Serial.print(output);
  #endif
     
    
}
