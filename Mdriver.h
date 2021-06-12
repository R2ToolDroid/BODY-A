#include <Arduino.h>       

bool inRange(int val, int minimum, int maximum){
  return ((minimum <= val)&&(val <= maximum));
}

void resetM(){
   digitalWrite(ledPin1, LOW); 
   digitalWrite(ledPin2, LOW); 
   ledState1 = LOW;
   ledState2 = LOW;
   analogWrite(DMOT_L, 0);  
   analogWrite(DMOT_R, 0);  
   DomeMot.write(90);
   
    
}

void LMotor(int MO){   
    tempo = 200;    
    
    switch (MO){
      case M_LEFT:
      if (debug) {   
      Serial.print(" left ");   
      } 
      digitalWrite(ledPin2, HIGH); 
      analogWrite(BMOT_R, 0); 
      analogWrite(BMOT_L, tempo); 
      break;

      case M_RIGHT:
      if (debug) {   
      Serial.print(" right ");
      }
      digitalWrite(ledPin1, HIGH); 
      analogWrite(BMOT_L, 0); 
      analogWrite(BMOT_R, tempo);
      break; 

      case M_STOP:
      if (debug) {   
      Serial.print(" stop ");
      }
      digitalWrite(ledPin2, LOW); 
      digitalWrite(ledPin1, LOW); 
      analogWrite(BMOT_L, 0); 
      analogWrite(BMOT_R, 0);
      break;

      default:
      ///do nothing
      digitalWrite(ledPin2, LOW); 
      digitalWrite(ledPin1, LOW); 
      analogWrite(BMOT_L, 0); 
      analogWrite(BMOT_R, 0);
      break;
      
    }
  
}


void BodyRot(int tPos) {   // Rotiert zu tPos

    int potPos = analogRead(LEG_POTI);

    //inRange (x, 0, 200)
    

   if (inRange(tPos, potPos-D_ZONE, potPos+D_ZONE)){
    if (debug) {   
      Serial.print(" match "); // Alles klar so bleiben
    }
      potPos = tPos;
      MO = M_STOP; 
      mov = false;
      
   
   }    else {
    mov = true;              
   }

    //if ( potPos >= B_TOP ) {mov = false;}
    //if ( potPos <= B_DOWN) {mov = false;}

   if ( (potPos >= tPos) && (mov == true) ){
      MO = M_LEFT;
   }

    if ((potPos <= tPos) && (mov == true)) {
      MO = M_RIGHT;
   }

   
   
    LMotor(MO);
    if (debug) {   
    Serial.print(" Poti Pos = ");
    //Serial.print();  
    Serial.print(potPos);
    Serial.print(" | Tpos = ");
    Serial.println(tPos);
    }
/*
    if ((potPos >= GAB_A)&&(potPos <= B_TOP)) {
      Serial.print("left");
      MO = M_LEFT;   
      //LMotor(MO); 
      //tempo = map(potPos, 600,1050,100,255); 
    } 
    if ((potPos <= GAB_B)&&(potPos >= B_DOWN)){
      Serial.print("right");
      MO = M_RIGHT;  
      //LMotor(MO);   
     // tempo = map(potPos, 400,0,100,255);
    }
    if ((potPos >= GAB_B)&&(potPos <= GAB_A)){
      Serial.print("stop");
      MO = M_STOP;
      tempo = 0;
    }  
    if ((potPos >= B_TOP)||(potPos <= B_DOWN)){
      Serial.print("stop");
      MO = M_STOP;
      tempo = 0;
    }
    LMotor(MO);
*/
    
}




int center(String dir) {
    /// Fuert den Dome in die Ausgangsposition //
   centerState = digitalRead(SENSOR_CENTER);  
   if (debug) {   
    Serial.print(F("CenterMode "));
    Serial.println(centerState);
   }
    analogWrite(DMOT_R, 0); 
    analogWrite(DMOT_L, 0); 
      
      while ( centerState == 0){

                 centerState = digitalRead(SENSOR_CENTER);  
                
                if (dir == "L" ) {
                  analogWrite(DMOT_L, Rtempo); 
                  digitalWrite(ledPin2, HIGH);                  
                } 
                
                if (dir == "R") {
                  analogWrite(DMOT_R, Rtempo); 
                  digitalWrite(ledPin1, HIGH); 
                }
                
                if (debug){Serial.println(F("try to get center"));Serial.print(SENSOR_CENTER);}
              
 
      }
   digitalWrite(ledPin1, LOW); 
   digitalWrite(ledPin2, LOW); 
   analogWrite(DMOT_L, 0);  
   analogWrite(DMOT_R, 0);  
   
   delay(200);
   durchlauf = 0;
   
   //Mode = 0; 
}

void FindRoTime(){
    //int rotime;
    center("L");
    if (debug){Serial.println(F("Dome ist Center"));}  
    delay(1000);
    zeit1 = millis();
    center("L");
    zeit2 = millis();
    if (debug){Serial.print(F("Zeit1_"));Serial.println(zeit1); Serial.print(F("Zeit2_")); Serial.println(zeit2);}
    rotime = zeit2-zeit1;
    if (debug){Serial.print(F("rotime_")); Serial.println(rotime);}
    Rpos = rotime/360; ///Rpos ist dann Winkel in Zeit Variable  90° also SUM*90;
    center("R");
    if (debug){Serial.print(F("Rpos_")); Serial.println(Rpos);}
}


void rotateR( int Rpos) {
  
     digitalWrite(ledPin1, HIGH); 
     analogWrite(DMOT_L, 0); 
     analogWrite(DMOT_R, Rtempo);
     delay (Rpos);
     digitalWrite(ledPin1, LOW); 
     analogWrite(DMOT_L, 0); 
     analogWrite(DMOT_R, 0);
          
}

void rotateL( int Rpos) {

     digitalWrite(ledPin2, HIGH); 
     analogWrite(DMOT_R, 0); 
     analogWrite(DMOT_L, Rtempo);
     delay (Rpos);
     digitalWrite(ledPin2, LOW); 
     analogWrite(DMOT_L, 0); 
     analogWrite(DMOT_R, 0);
    
  
}


int rcMove() {

    int sensorValue = pulseIn(SENSOR_RC_IN,HIGH);
    
    if (sensorValue >=800){ ///Check if Sensor is Connectet an RC on

    
    if (sensorValue < 1350){
      
     
      int tempoR = map (sensorValue, 1460, 530,50,254);
     
      if (tempoR >= 180) {tempoR=255;}
         
     digitalWrite(ledPin2, HIGH); 
     analogWrite(DMOT_L, 0); 
     analogWrite(DMOT_R, tempoR); 
     DomeMot.write(180);

     if (debug){ 
        Serial.println(F("Rechts"));
         Serial.print(F("tempoR "));Serial.println(tempoR);
      } 
    
    
    } else if (sensorValue > 1650) {
          
     // set the LED with the ledState of the variable:
      digitalWrite(ledPin1, HIGH); 
      //tempo = sensorValue ;////6;
      int tempoL = map(sensorValue, 1450,2400,50,254);
      //tempo = tempo /5;
      
      analogWrite(DMOT_R, 0);  
      analogWrite(DMOT_L, tempoL); 
      DomeMot.write(0);
      if (debug) {
      Serial.println(F("Links"));
      Serial.print(F("tempoL "));Serial.println(tempoL);
      }   
     
    }  else {
      analogWrite(DMOT_L, 0);  
      digitalWrite(ledPin1, LOW); 
      analogWrite(DMOT_R, 0); 
      digitalWrite(ledPin2, LOW);    
      DomeMot.write(90); 
      //delay (zeit);    
    }

    }///End Sensor Check
    
  if (debug) { 
    //Serial.print(F("Tempo "));Serial.println(tempo);
    //Serial.print(F("Value "));Serial.println(sensorValue);
    }
  
}

void randomMove() {
 
   // print a random number from 0 to 299
  zeit = random(3000, 6000)+(temp-20)*faktor;
  
  // print a random number from 10 to 19
  randNumber = random(10, 40);
  //Speed
  int tempo = random(90,120);
  //Moving länge
  moving = random(500,1500);
 
  if (randNumber < 20){     ///Drehung Links
    if (debug){
    Serial.println(F("Links"));
     Serial.println(randNumber);
    }
     // set the LED with the ledState of the variable:
     digitalWrite(ledPin2, HIGH);
     analogWrite(DMOT_L, tempo);  
     delay(moving);
     analogWrite(DMOT_L, 0);  
     digitalWrite(ledPin2, LOW);
     delay(500);
    
    } else if (randNumber > 20 && randNumber <= 30) {  ///Rechts Drehung

     if (debug) {
      Serial.println(F("rechts"));
      Serial.println(randNumber);
     }
     // set the LED with the ledState of the variable:
      digitalWrite(ledPin1, HIGH);   
      analogWrite(DMOT_R, tempo); 
      delay(moving);      
      digitalWrite(ledPin1, LOW); 
      analogWrite(DMOT_R, 0); 
      delay(500);
      
    }  else {
      
      analogWrite(DMOT_L, 0);  
      analogWrite(DMOT_R, 0); 
      digitalWrite(ledPin1, LOW); 
      digitalWrite(ledPin2, LOW); 
      delay (zeit);  
    }

  if (debug) {
      Serial.print(F("Zeit "));
      Serial.println(zeit);
      Serial.print(F("Druchlauf "));
      Serial.println(durchlauf);
      Serial.print(F("Temp0 "));
      Serial.println(tempo);
      Serial.print(F("Temp "));
      Serial.println(temp);
      Serial.print(F("Faktor "));
      Serial.println(temp*faktor);
  }
 
}

void SendPing(){
  
    unsigned long currentMillis = millis();


       if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    if (Ping == true){
    Serial.println("Ping");
    Ping = false;
    }

    
    }
       
    
    
    
}
