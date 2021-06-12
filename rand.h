#include <Arduino.h>


// =======================================================================================
//                             Dome Automation Function
//
//    Features toggles 'on' via L2 + CIRCLE.  'off' via L2 + CROSS.  Default is 'off'.
//
//    This routines randomly turns the dome motor in both directions.  It assumes the 
//    dome is in the 'home' position when the auto dome feature is toggled on.  From
//    there it turns the dome in a random direction.  Stops for a random length of 
//    of time.  Then returns the dome to the home position.  This randomly repeats.
//
//    It is driven off the user variable - time360DomeTurn.  This records how long
//    it takes the dome to do a 360 degree turn at the given auto dome speed.  Tweaking
//    this parameter to be close provides the best results.
//
//    Activating the dome controller manually immediately cancels the auto dome feature
//    or you can toggle the feature off by pressing L2 + CROSS.
// =======================================================================================
void autoDome()
{
    long rndNum;
    int domeSpeed;

    //output += "\r\n - Dome Status=";
    //output +=    domeStatus      ; 
    
    if (domeStatus == 0)  // Dome is currently stopped - prepare for a future turn
    {
      
        if (domeTargetPosition == 0)  // Dome is currently in the home position - prepare to turn away
        {
          
            domeStartTurnTime = millis() + (random(3, 10) * 1000);
            
            rndNum = random(5,354);
            
            domeTargetPosition = rndNum;  // set the target position to a random degree of a 360 circle - shaving off the first and last 5 degrees
            
            if (domeTargetPosition < 180)  // Turn the dome in the positive direction
            {
              
                domeTurnDirection = 1;
                
                domeStopTurnTime = domeStartTurnTime + ((domeTargetPosition / 360) * time360DomeTurn);
              
            } else  // Turn the dome in the negative direction
            {
                    
                domeTurnDirection = -1;
                
                domeStopTurnTime = domeStartTurnTime + (((360 - domeTargetPosition) / 360) * time360DomeTurn);
              
            }
          
        } else  // Dome is not in the home position - send it back to home
        {
          
            domeStartTurnTime = millis() + (random(3, 10) * 1000);
            
            if (domeTargetPosition < 180)
            {
              
                domeTurnDirection = -1;
                
                domeStopTurnTime = domeStartTurnTime + ((domeTargetPosition / 360) * time360DomeTurn);
              
            } else
            {
                    
                domeTurnDirection = 1;
                
                domeStopTurnTime = domeStartTurnTime + (((360 - domeTargetPosition) / 360) * time360DomeTurn);
              
            }
            
            domeTargetPosition = 0;
          
        }
      
        domeStatus = 1;  // Set dome status to preparing for a future turn
               
        #ifdef DEBUG
          output += "Dome Automation: Initial Turn Set\r\n";
          output +=  "Current Time: ";
          output +=  millis();
          output += "- Next Start Time: ";
          output += domeStartTurnTime;
          output += " - ";
          output += "Next Stop Time: ";
          output += domeStopTurnTime;
          output += " - ";          
          output += "Dome Target Position: ";
          output += domeTargetPosition;
          output += "\r\n ";
        #endif

    }
    
    
    if (domeStatus == 1)  // Dome is prepared for a future move - start the turn when ready
    {
      
        if (domeStartTurnTime < millis())
        {
          
             domeStatus = 2; 
             
             #ifdef DEBUG
               // output += "Dome Automation: Ready To Start Turn\r\n";
             #endif
          
        }
    }
    
    if (domeStatus == 2) // Dome is now actively turning until it reaches its stop time
    {
      
        if (domeStopTurnTime > millis())
        {
          
              domeSpeed = domeAutoSpeed * domeTurnDirection;

              int DomePulseSpeed = map(domeSpeed,-100,100,0,180);
          
              //SyR->motor(domeSpeed);
              DomeMot.write(DomePulseSpeed);
              
             #ifdef DEBUG
              // output += "Turning Now!!\r\n";
                
             #endif
          
          
        } else  // turn completed - stop the motor
        {
              domeStatus = 0;
              //SyR->stop();
              DomeMot.write(90);
              
              #ifdef DEBUG
            //     output += "STOP TURN!!\r\n";
              #endif
        }
      
    }
  
}
