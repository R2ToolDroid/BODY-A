#include <Arduino.h>    

//// Commandos ///////
void ProzessComando() {

    if(data == "T"){
      //BodyRot(B_TOP);
      tPos = B_TOP;
      Serial.println("Body to Top");
    }

    if(data == "D"){
      //LMotor(B_DOWN);
      tPos = B_DOWN;
      Serial.println("Body to Down");
    }
    if(data == "C"){
      //LMotor(M_STOP);
      tPos = B_CENT;
     Serial.println("Body to Center");
    }
    
    if(data == "O"){
      //LMotor(M_STOP);
      //tPos = B_CENT;
     Serial.println("Arm out");
     ArmSrv.write(ARM_OUT);
    }
    
    if(data == "I"){
      //LMotor(M_STOP);
      //tPos = B_CENT;
     Serial.println("ARM_IN");
     ArmSrv.write(ARM_IN);
    }

    if (data == "hi-r2" )
      {             
       Serial.println("test gefunden");
       
      }
      
    if (data == "stop" )
      {         
       Serial.println("detach Servo");
       LegMot.detach();
       ArmSrv.detach();
      }

    if (data == "start" )
      {         
       Serial.println("attach Servos");
       LegMot.attach(PWM_OUT);
       ArmSrv.attach(STATUS_PIN);
      }

   
    if (data == "debug on")
      {
        Serial.println("Debug Mode ON");
        debug = true;      
      }

    if (data == "debug off")
      {
        Serial.println("Debug Mode off");
        debug = false;
      }
    if (data == "vers")   
      {
        Serial.println(F("-----   Versionnsnummer   -----"));
        Serial.println(VERSION);     
        /*
         * Vorher 73% 77%
         */
        Serial.println(F("|    Komandoreferenz"));
        Serial.println(F("| debug on"));
        Serial.println(F("| debug off"));
        Serial.println(F("| stop  : resetAll"));
        Serial.println(F("| hi-r2 : test")); 
        Serial.println(F("| D  : Body Down"));
        Serial.println(F("| T  : Body UP"));
        Serial.println(F("| C  : Body Center"));      
        Serial.println(F("| O  : Arm Out"));
        Serial.println(F("| I  : Arm IN"));
        Serial.println(F("| stop  : detach Servos"));                  
        Serial.println(F("...ready for Command_"));

      }

   
    
    if (data == "yea"){Serial.println("Rotation yea");}

    
    
    data = "";
}



void Comand() {
///Comando Pruefung////
   if(Serial.available() > 0)
    {
        data = Serial.readStringUntil('\n');
        ProzessComando();
    }
  ////Prüfung 2///
  MainInput.listen();
  
   if (MainInput.available() > 0)
    {
        data = MainInput.readStringUntil('\r');
        Serial.println(MainInput);
        Serial.println(data);
        ProzessComando();
    }
}
