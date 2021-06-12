#include <Arduino.h>                           

String data; //Consohlen Input
String VERSION = "12-06-21-BODY-A";
String output = "";

#define DEBUG

byte debug = true;
/*
long randNumber;
long zeit;
unsigned long previousMillis = 0;        // will store last time LED was updated
unsigned long previousMillis1 = 0;        // will store last time LED was updated
unsigned long previousMillis2 = 0;        // will store last time LED was updated
// constants won't change:
const long interval = 3000;           // interval at which to blink (milliseconds)
unsigned long interval1 = 3000;           // interval at which to blink (milliseconds)
unsigned long interval2 = 2000;           // interval at which to blink (milliseconds)


// Dome Automation Variables
boolean domeAutomation = true;
int domeTurnDirection = 1;  // 1 = positive turn, -1 negative turn
float domeTargetPosition = 0; // (0 - 359) - degrees in a circle, 0 = home
unsigned long domeStopTurnTime = 0;    // millis() when next turn should stop
unsigned long domeStartTurnTime = 0;  // millis() when next turn should start
int domeStatus = 0;  // 0 = stopped, 1 = prepare to turn, 2 = turning
int time360DomeTurn = 2500;  // milliseconds for dome to complete 360 turn at domeAutoSpeed - Valid Values: 2000 - 8000 (2000 = 2 seconds)
byte domeAutoSpeed = 70;     // Speed used when dome automation is active - Valid Values: 50 - 100

*/



//Move Sensor
byte NachL = false;
byte NachR = false;
byte Mitte = false;
byte Ping = false;

int Sdiff = 0;

///PIN ARRANGEMENT

#define DOME_PULSE_IN 21 //RC Signal DomeRotation
//#define BODY_PULSE_IN 16 //RC Signal Body Move

#define DMOT_L 5  //L298 MotorIN1
#define DMOT_R 6  //L298 MotorIN2

#define BMOT_L 7  //L298 MotorIN3
#define BMOT_R 4  //L298 MotorIN4

//#define STATUS_PIN 16  // Body Sensor or Input Ping

#define DOME_PWM_OUT 16 // Dome PWR as Controller signal

#define PWM_OUT 10 // PWM POLOLU

#define SENSOR_CENTER 8  //Center Sensor
//#define SENSOR_RC_IN 21  //PWM INPUT Sensor Dome Rotation

#define LEG_POTI 9 // Position Reading Leg

#define M_LEFT 1
#define M_RIGHT 2
#define M_STOP 3

//Body Positionen

#define B_TOP  450 //Body Hoch
#define B_DOWN  800 //Body Down
#define B_CENT 620 //Boby Center
#define D_ZONE 20 // Death Zone
bool mov = true;
int MO = 0;
int tPos = B_CENT;   // Target Position Body Roll


//int tempo = 200;
int Htempo = 170; //Human Tracking Tempo
int Rtempo = 200; // Autorotation Tempo
int tempo = 200; // kalkuliertes Tempo

int faktor = 100;
unsigned long Rpos = 35;  //Zeit von Center to Zielposition in Millisec
int durchlauf = 0;
int sensorValue = 1500; ///Umschalt Pulse

int rotime;
unsigned long zeit1, zeit2;
//int sensorRC = 21; ///von 2 auf 21 geänder wg I2C  Dome Rotation

//int sensorRC_out = 10;
int Mode = 0;// 0=RandMove // 1=RCMove  //2=human //3=Service
int moving = 0;

//#### Status Signal fom 16  ACTUAL INACTIVE

//#define USE_STATUS_PIN



int stat=0;

int vpos1;
int vpos2;
int Vdiff;
byte Hdiff;

int pos = 0;    // variable to store the servo position
int tempPos ;

int centerState = 0;

const int ledPinC =  20;  
const int ledPin1 =  18;  
const int ledPin2 =  19;  

int ledStateC = LOW;
int ledState1 = LOW; 
int ledState2 = LOW; 
