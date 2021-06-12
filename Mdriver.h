#include <Arduino.h>       

bool inRange(int val, int minimum, int maximum){
  return ((minimum <= val)&&(val <= maximum));
}


void LMotor(int MO){   
    tempo = 200;    
    
    switch (MO){
      case M_LEFT:
      if (debug) {   
      Serial.print(" left ");   
      } 
      digitalWrite(ledPin2, HIGH); 
      LegMot.write(180);
      //analogWrite(BMOT_R, 0); 
      //analogWrite(BMOT_L, tempo); 
      break;

      case M_RIGHT:
      if (debug) {   
      Serial.print(" right ");
      }
      digitalWrite(ledPin1, HIGH); 
      LegMot.write(0);
      //analogWrite(BMOT_L, 0); 
      //analogWrite(BMOT_R, tempo);
      break; 

      case M_STOP:
      if (debug) {   
      Serial.print(" stop ");
      }
      digitalWrite(ledPin2, LOW); 
      digitalWrite(ledPin1, LOW); 
      LegMot.write(90);
      //analogWrite(BMOT_L, 0); 
      //analogWrite(BMOT_R, 0);
      break;

      default:
      ///do nothing
      digitalWrite(ledPin2, LOW); 
      digitalWrite(ledPin1, LOW); 
      //analogWrite(BMOT_L, 0); 
      //analogWrite(BMOT_R, 0);
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
