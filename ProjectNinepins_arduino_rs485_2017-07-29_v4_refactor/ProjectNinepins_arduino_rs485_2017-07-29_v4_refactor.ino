
/*
This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

//WIRE
#define WIRE 1

//RS485 setting
#define TXControl 3
#include <SPI.h>


//Machine pins

  #define PXSENSOR_UP 34
  #define PXSENSOR_DOWN 32
  #define PXSENSOR_OVERLOAD 30

  #define GAFFE_RAMP 26
  #define GATE_RAMP 24

  #define ENGINE_RIGHT 29
  #define ENGINE_LEFT 33
  #define ENGINE_SLOW 31

  //LED pins
  #define LED_START 12
  #define LED_ERROR 13
  #define LED_PIN  23



  //Engine settings
  #define OVERLOAD 200
  #define ENGINEDOWN 500
  #define ENGINESLOWDOWN 1900

//Timings and global variables
  int lockMAG=0;
  int brightness = 80;
  int waitUp = 1800;
  int lowering = 3000;
  int accelleration = 3000;
  int lightTime = 55;
  int callEmployee;
  int overloadCounter;
  int fallenCounter = 0;
  bool isFirst = true;
  int ret;

  int PXSENSOR[9] = {52, 50, 48, 46, 44, 42, 40, 38, 36};
  int MAG[9] = {53, 51, 49, 47, 45, 43, 41, 39, 25}; // treba magnet pripojit na pi 25 z pinu 37
  int LED[9] = {2, 4, 5, 6, 7, 8, 9, 10, 11};
  int pins[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  int toMAG[9] = {0, 0, 0 ,0, 0, 0, 0, 0, 0}; // pomocne pole na ukladanie zasvietenych LED do magnetov
  int fallen[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};


  int lastPoints = 0;
  int points = 0;
  int gameType = 0;
  int gateCounter = 0;
  int gateSensorCounter = 0;
  int num = 0;


  bool last = 0;
  bool newState = false;
  bool isSettingPins = false;
  bool isError = false;
  bool errorButtonPressed = false;
  bool noneFallen = false;
  int prevPins[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};


  struct message {
    int  cmd;
    int pins[9];
    int wire;
    int rounds;

  };



  message outgoing;
  message incoming;



void setup() {

 Serial.begin(57600);
 Serial1.begin(57600);


    analogWrite(TXControl, 0); //Receiving



    pinMode(PXSENSOR[0], INPUT);
    pinMode(PXSENSOR[1], INPUT);
    pinMode(PXSENSOR[2], INPUT);
    pinMode(PXSENSOR[3], INPUT);
    pinMode(PXSENSOR[4], INPUT);
    pinMode(PXSENSOR[5], INPUT);
    pinMode(PXSENSOR[6], INPUT);
    pinMode(PXSENSOR[7], INPUT);
    pinMode(PXSENSOR[8], INPUT);
    pinMode(PXSENSOR_UP, INPUT);
    pinMode(PXSENSOR_DOWN, INPUT);
    pinMode(PXSENSOR_OVERLOAD, INPUT);
    pinMode(GAFFE_RAMP, INPUT);
    pinMode(GATE_RAMP, INPUT);



    pinMode(MAG[0], OUTPUT) ;
    pinMode(MAG[1], OUTPUT) ;
    pinMode(MAG[2], OUTPUT) ;
    pinMode(MAG[3], OUTPUT) ;
    pinMode(MAG[4], OUTPUT) ;
    pinMode(MAG[5], OUTPUT) ;
    pinMode(MAG[6], OUTPUT) ;
    pinMode(MAG[7], OUTPUT) ;
    pinMode(MAG[8], OUTPUT) ;


    pinMode(ENGINE_RIGHT, OUTPUT) ;
    pinMode(ENGINE_LEFT, OUTPUT) ;
    pinMode(ENGINE_SLOW, OUTPUT) ;


    //TODO - fix LED pins
    pinMode(LED[0], OUTPUT);
    pinMode(LED[1], OUTPUT) ;
    pinMode(LED[2], OUTPUT);
    pinMode(LED[3], OUTPUT);
    pinMode(LED[4], OUTPUT) ;
    pinMode(LED[5], OUTPUT) ;
    pinMode(LED[6], OUTPUT) ;
    pinMode(LED[7], OUTPUT) ;
    pinMode(LED[8], OUTPUT) ;
    pinMode(LED_START, OUTPUT);
    pinMode(LED_ERROR, OUTPUT) ;


    for (int i = 0; i < 9; i++)
      analogWrite(LED[i], 0);


    analogWrite(LED_START, 0);
    analogWrite(LED_ERROR, 0);


    digitalWrite(ENGINE_LEFT, LOW);
    digitalWrite(ENGINE_RIGHT, LOW);
    digitalWrite(ENGINE_SLOW, LOW);
    for (int i = 0; i < 9; i++) digitalWrite(MAG[i], LOW);



    gameType = 0;


    outgoing.wire = 0; outgoing.rounds = 0; outgoing.cmd = 0;
    for (int i = 0; i < 9; i++) outgoing.pins[i] = 0;

    incoming.wire = 0; incoming.cmd = 0; incoming.rounds = 0;
    for (int i = 0; i < 9; i++) incoming.pins[i] = 0;



}

void loop() {


 points = 0; gateCounter = 0;
checkLED();

if (gameType != 1) settingPins();
analogWrite(LED_ERROR, brightness);
analogWrite(LED_START, brightness);
//resetGame();
outgoing.wire=0;
outgoing.cmd=0;
for(int i= 0; i<9; i++) outgoing.pins[i]=0;
outgoing.rounds=0;
startGame();

}






















//******************* PIN CONTROL **********************************//

int settingPins(){

  Serial.println("*****************STAVANIE*****************");

    int pinsUpCounter = 0;
    overloadCounter = 0;
    callEmployee = 0; //pokial bude viac ako 4, zavolat obsluhu
  analogWrite(LED_START, 0);

    Serial.println("Waiting for pins up");
    while (pinsUpCounter < 5)
    {



      unsigned long time;
      time = millis();
      int upSensor = 0; bool pinsUp = false;
      while (millis() < time + 15000) {


       // Serial.println("stavanie");

        digitalWrite(ENGINE_RIGHT, HIGH);

        if (digitalRead(PXSENSOR_OVERLOAD) == LOW) {
          overloadCounter++;
          Serial.println("OVERLOAD");
        }


        if (overloadCounter > OVERLOAD ) {
          Serial.println("Nastalo OVERLOAD");
          stopEngines(); fixOverload();
          digitalWrite(ENGINE_RIGHT, HIGH);

        }
        if (callEmployee > 8) {
          stopEngines();
          Serial.print("Prid mi rozchlpit kolky");
          fixKnot();
          overloadCounter = 0;
          callEmployee = 0;
        }

        if (digitalRead(PXSENSOR_UP) == HIGH) upSensor++;

        if (upSensor > 3) {
          stopEngines();

          Serial.println("Koly su hore"); pinsUp = true; break;

        }
      }



      if (pinsUp) {
        stopEngines();
        delay(waitUp);
        resetPinCount();
         Serial.println("Spustam kolky");

        digitalWrite(ENGINE_RIGHT, HIGH);
        delay(ENGINEDOWN);//lowering dole odstopovat
        digitalWrite(ENGINE_SLOW, HIGH);
        delay(ENGINESLOWDOWN);
        digitalWrite(ENGINE_SLOW, LOW);








        unsigned int time3;
        time3 = millis();
        while (millis() < time3 + 100000) {

          if (digitalRead(PXSENSOR_DOWN) == HIGH) {
            Serial.println("Kolky su dole"); stopEngines();  // ak su kolky dole, nechame ich tam
            if (checkSettingPins() != 0) settingPins();

            Serial.println("Stavanie prebeho prebehlo v poriadku");
            analogWrite(LED_START, brightness);
            return 0;
          }
        }
      }
    }
  }



int settingPins2() {
  Serial.println("*****************STAVANIE DORAZKA*****************");
  int pinsUpCounter = 0;
    overloadCounter = 0;
    callEmployee = 0; //pokial bude viac ako 4, zavolat obsluhu
  analogWrite(LED_START, 0);

    Serial.println("Cakanie na kolky hore");
    while (pinsUpCounter < 5)
    {
      unsigned long time;
      time = millis();
      int upSensor = 0; bool pinsUp = false;
      while (millis() < time + 15000) {
       digitalWrite(ENGINE_RIGHT, HIGH);


        if (digitalRead(PXSENSOR_OVERLOAD) == LOW) {
          overloadCounter++;
          Serial.println("OVERLOADenie");
        }

        if (overloadCounter > OVERLOAD ) {
          Serial.println("Nastalo OVERLOADenie");
          stopEngines(); fixOverload();
          digitalWrite(ENGINE_RIGHT, HIGH);

        }
        if (callEmployee > 8) {
          stopEngines();
          Serial.print("Prid mi rozchlpit kolky");
          fixKnot();
          overloadCounter = 0;
          callEmployee = 0;
        }

        if (digitalRead(PXSENSOR_UP) == HIGH) upSensor++;

        if (upSensor > 3) {
          stopEngines();
          Serial.println("Koly su hore"); pinsUp = true; break;
      }
      }

  if (pinsUp) {
        stopEngines();
        delay(1500);
        delay(waitUp);


       int lockMAG=0;
        for (int i  = 0; i<9; i++) if (toMAG[i]>0) lockMAG++;
        Serial.print("Pocet spadnutych kolkov: ");
        Serial.println(lockMAG);
  if (lockMAG < 9){
        for (int i  = 0; i<9; i++) if (toMAG[i]>0) digitalWrite(MAG[i],HIGH);

         digitalWrite(ENGINE_RIGHT, HIGH);
        delay(ENGINEDOWN);//lowering dole odstopovat

        for (int i  = 0; i<9; i++) if (toMAG[i]>0) digitalWrite(MAG[i],LOW);

        digitalWrite(ENGINE_SLOW, HIGH);
        delay(ENGINESLOWDOWN);
        digitalWrite(ENGINE_SLOW, LOW);
  } else {
    for (int i  = 0; i<9; i++) {
      digitalWrite(MAG[i],LOW);
      toMAG[i] = 0; pins[i] = 0;
      offLED();
      }


    digitalWrite(ENGINE_RIGHT, HIGH);
        delay(ENGINEDOWN);//lowering dole
  digitalWrite(ENGINE_SLOW, HIGH);
        delay(ENGINESLOWDOWN);
        digitalWrite(ENGINE_SLOW, LOW);
  //fallenCounter = 0;
    }

  unsigned int time3;
        time3 = millis();
        while (millis() < time3 + 100000) {


          if (digitalRead(PXSENSOR_DOWN) == HIGH) {
            Serial.println("Kolky su dole"); stopEngines();  // ak su kolky dole, nechame ich tam
             if (checkSettingPins() != 0) settingPins2();

            Serial.println("Stavanie prebeho prebehlo v poriadku");
            analogWrite(LED_START,brightness);
            return 0;
          }
        }

  }
    }
  }


//******************************************************************//


























//******************* WORKER FUNCTIONS ****************************//







void startGame(){

  resetIncoming();

  Serial.println("Project Ninepins - wired version");

while (true) {
  rcvMsg();
  delay(10);
  if (incoming.wire == WIRE)
  {
        switch (incoming.cmd){
          case 21:
          settingPins();
          Serial.print(" Stavanie kolkov . \n");
          break;

          case 22:
          checkPins();
          Serial.print(" Kontrola kolkov. \n\n");
          break;

          case 23:
          checkLED();
          Serial.print(" Kontrola led.\n \n");
          break;

          case 24:
          game1();
          //hraPlna();
          Serial.print(" Zaciatok hry plne . \n\n");
          break;

          case 25:
          Serial.print(" Zaciatok hry dorazka .\n \n");
          game2();
          //hraDorazka();
          break;

          case 26:
          lowerPins();
          Serial.print(" Spustenie kolkov .\n \n");
          break;
          }
          resetIncoming();
  }
      delay(100);



  }




}






int checkPins() {


    noneFallen = false;
    int val = 0;
    for (int i = 0; i < 9; i++)
    {
      if (digitalRead(PXSENSOR[i]) != LOW) {
        val++;
      } else {
        Serial.print("Kolok ");
        Serial.print(i + 1);
       Serial.print(" je zhodeny. \n");
        pins[i]++;
      }

    }

    if (val == 9) {
      noneFallen = true;
      return 0;


    }

  noneFallen = false;
    return 1;


  }

  int checkSettingPins() {


    noneFallen = false;
    int val = 0;
    for (int i = 0; i < 9; i++)
    {
      if (digitalRead(PXSENSOR[i]) != LOW) {
        val++;
      }

    }

    if (val == 9) {
      return 0;


    }

    return 1;


  }




int checkLED()
  {
    Serial.println("************KOTNROLA LED*************");
    for (int i = 0; i < 9; i++) {
      analogWrite(LED[i], 70);
      delay(lightTime);
      analogWrite(LED[i], 0);


    }


     analogWrite(LED_START, 70); delay(200); analogWrite(LED_START, 0);
     analogWrite(LED_ERROR,brightness); delay(200); analogWrite(LED_ERROR, 0);
     analogWrite(LED_START, 70); delay(200); analogWrite(LED_START, 0);
  }

  void showFallenPins() {

    int compare = 0;

    int fallenCounter = 0;
    for (int i = 0; i < 9; i++)
    {
      if ((pins[i]> 0 && prevPins[i]>0) || (pins[i] == 0 && prevPins[i] == 0)) compare++;
      //if (prevPins[i] > 0) compare++;
      if (pins[i] > 0) {
        fallenCounter++;
        analogWrite(LED[i], brightness);
        toMAG[i]++;
      } else analogWrite(LED[i], 0);
    }


    if (fallenCounter == 8 && pins[4] == 0 && gameType == 1) {

      showCircle();
    }

    if (fallenCounter == 9) {
      showAll();
    }




  //if (fallenCounter == porovnanie) noneFallen = true; else noneFallen = false;
  //if (porovnanie == 9) noneFallen = true; else noneFallen = false;
  //if (fallenCounter==0) noneFallen=true; else noneFallen = false;
  for (int i=0; i<9; i++) prevPins[i] = pins[i];


    //ratampoints=false;
  }




void controlPins() {
    Serial.println("************OVLADANIE KOLKOV*************");
    if (Serial1.available())
      {
        resetIncoming(); rcvMsg(); jumpOut();
        Serial.println(); for (int i = 0; i < 9; i++) {
          Serial.println(incoming.pins[i]);
          if (incoming.pins[i] == 1)
          {
            analogWrite(LED[i], brightness);

          }

        }
      }
      }




void lowerPins() {

    digitalWrite(ENGINE_LEFT, HIGH);

    delay(2000);

    digitalWrite(ENGINE_LEFT, LOW);
  }


  void fixKnot()
  {
     resetIncoming();
     resetOutgoing();
      outgoing.cmd = 3; //arduino pocuva
      sndMsg();

    Serial.print ("Ak je rozchlpene, stlac klavesu 5");
    while (true) {

        digitalWrite(TXControl, 0);
      if (Serial1.available())
      {
        rcvMsg();
        delay(10);
        if (incoming.wire == WIRE && incoming.cmd == 3) break;
      }


      int val = Serial.parseInt();
      if (val  == 5) break;
    }
  }

  void fixOverload()
  {
    callEmployee++;
    stopEngines();
   delay(1000);
    digitalWrite(ENGINE_LEFT, HIGH);

    delay(800);

    digitalWrite(ENGINE_LEFT, LOW);
    delay(400);
    overloadCounter = 0;

  }

  void stopEngines()
  {
    digitalWrite(ENGINE_RIGHT, LOW);
    digitalWrite(ENGINE_SLOW, LOW);
    digitalWrite(ENGINE_LEFT, LOW);
  }

  void countPoints()
  {
    //lastPoints = points;
    for (int i = 0; i < 9; i++)
      if (pins[i] > 0) {
        //points++;
        outgoing.pins[i] = 1;}
  }



  void jumpOut() {
    if (incoming.cmd == -100) { resetIncoming(); loop();}
    }




bool checkError()
  {

    Serial.println("************POTVRDENIE CHYBY*************");
    bool docasnepins[9] = {false,false,false,false,false,false,false,false,false};
    for (int i = 0; i<9; i++) docasnepins[i] = pins[i];
    analogWrite(LED_ERROR, brightness);
      while (true) {

        if (digitalRead(GATE_RAMP) == LOW) {  //pozor, tento senzor ma opacnu logiku
          gateSensorCounter++;

          Serial.println("Presla gula!"); analogWrite(LED_START, 0); //break; //ak presla gula, pokracujeme kontrolovanim padu kolkov
        }
        if (digitalRead(GATE_RAMP) == HIGH) { //pozor, tento senzor ma opacnu logiku ## ak nepride opakovany signal prechodu gule, tak mohla nastat chyba senzora, udaje vynulujeme a snimame dalej
          gateSensorCounter = 0;

        }

 checkPins();
 showFallenPins();

          rcvMsg();
          delay(10);
        if (incoming.wire == WIRE) {


        if (incoming.cmd == 205) {
          Serial.println("chyba sa nestala");
          analogWrite(LED_ERROR, LOW);
          return false;
        }
        if (incoming.cmd == 206) {
          Serial.println("chyba sa stala");
         if (gameType == 1) { resetPinCount(); } else  { for (int i =0; i<9; i++){ toMAG[i] = docasnepins[i]; pins[i] = docasnepins[i];} }
          for (int i =0; i<9; i++) analogWrite(LED[i], LOW);
          analogWrite(LED_ERROR, brightness);
           showFallenPins();
           //points = lastPoints;
          return true;
        }
        }

        }
    }



    //****************************rozsviet kurh ////////////////////


  void showCircle() {
  Serial.println("************SVIETIME KRUH*************");
    for (int i = 0; i < 9; i++)
    {
      if (pins[i] > 0) analogWrite(LED[i], 25);
    }
    analogWrite(LED[0], brightness);
    delay(lightTime);
    analogWrite(LED[0], 0);
    delay(lightTime);
    analogWrite(LED[1], brightness);
    delay(lightTime);
    analogWrite(LED[1], 0);
    delay(lightTime);
    analogWrite(LED[3], brightness);
    delay(lightTime);
    analogWrite(LED[3], 0);
    delay(lightTime);
    analogWrite(LED[6], brightness);
    delay(lightTime);
    analogWrite(LED[6], 0);
    delay(lightTime);
    analogWrite(LED[8], brightness);
    delay(lightTime);
    analogWrite(LED[8], 0);
    delay(lightTime);
    analogWrite(LED[7], brightness);
    delay(lightTime);
    analogWrite(LED[7], 0);
    delay(lightTime);
    analogWrite(LED[5], brightness);
    delay(lightTime);
    analogWrite(LED[5], 0);
    delay(lightTime);
    analogWrite(LED[2], brightness);
    delay(lightTime);
    analogWrite(LED[2], 0);
    delay(lightTime);


    analogWrite(LED[0], brightness);
    analogWrite(LED[1], brightness);
    analogWrite(LED[3], brightness);
    analogWrite(LED[6], brightness);
    analogWrite(LED[8], brightness);
    analogWrite(LED[7], brightness);
    analogWrite(LED[5], brightness);
    analogWrite(LED[2], brightness);
    }
  //******************************************************************************************************************
  //****************************rozsvietVsetko*******************************************************************
  //************************************************************************************************************
  void showAll() {

    Serial.println("************SVIETIME VSETKYM*************");
    for (int i = 0; i < 9; i++)
    {
      analogWrite(LED[i], brightness );
    }
    delay(2*lightTime);
    for (int i = 0; i < 9; i++)
    {
      analogWrite(LED[i], 0 );
    }
    delay(2*lightTime);

     for (int i = 0; i < 9; i++)
    {
      analogWrite(LED[i], brightness );
    }


  }


//***********************************************************************************


bool setState()
    {
      Serial.println("************UPRAVA STAVU*************");
      while (true)
      {
         rcvMsg();
         delay(10);
        //if (incoming.wire == WIRE)
        //{


        if (incoming.cmd == 101)
          {
          //points = incoming.score;
          gateCounter = incoming.rounds;
          for (int i =0; i<9; i++) {pins[i] = incoming.pins[i]; toMAG[i] = pins[i]; showFallenPins();}

          //fallenCounter = incoming.points;
          return true;
          }
        if (incoming.cmd == 102) {


          //points = lastPoints;
          return false;
                                   }
        //}

     }
    }





















//******************* RESET FUNCTIONS  ****************************//


void offLED() { for (int i = 0; i<9; i++) analogWrite(LED[i],0);
  }

void offMAG() {for (int i = 0; i<9; i++) toMAG[i] = 0;
  }

void resetIncoming(){
  incoming.cmd = 0; incoming.wire = 0;
for (int i=0;i<9;i++) incoming.pins[i] = 0; incoming.rounds =0;
  }

  void resetOutgoing()
  {
    outgoing.cmd = 0; for (int i = 0; i<9; i++) outgoing.pins[i] = 0; outgoing.rounds=0;

  }


void resetGame(){

  lockMAG=0;
  brightness = 80;

  lowering = 3000;
  accelleration = 3000;
  lightTime = 55;

  fallenCounter = 0;

  resetIncoming();

  lastPoints = 0;
  points = 0;
  gameType = 0;
  gateCounter = 0;
  gateSensorCounter = 0;
  num = 0;

  last = 0;
  newState = false;
  isSettingPins = false;

  noneFallen = false;
  for (int i=0;i<9;i++) {prevPins[i] = 0; fallen[i] = 0; toMAG[i] = 0; pins[i] = 0;}

  }

   void resetPinCount()
  {
    Serial.println("************NULOVANIE KOLKOV*************");
    for (int i = 0; i < 9; i++)
    {
      pins[i] = 0;
    }
  }


  void resetMAG()
  {
    Serial.println("************NULOVANIE MAGNETOV*************");
    for (int i = 0; i < 9; i++)
    {
      MAG[i] = 0;
    }
  }

  void resetFallenPins()
  {
    Serial.println("************NULOVANIE PADNUTYCH*************");
    for (int i = 0; i < 9; i++)
    {
      fallen[i] = 0;
    }
  }



//******************************************************************//




//******************************* GAME****************************//







void game1()

{
  analogWrite(LED_ERROR, LOW);
  Serial.println("Plna HRA");

  offLED();

  gameType = 1;

  while(true){

    isError = false; isSettingPins = false; noneFallen = false; errorButtonPressed = false;
    int gaffeSensorCounter = 0; gateSensorCounter = 0;

    analogWrite(LED_ERROR, 0);

    resetPinCount();
    offLED();

    analogWrite(LED_START, brightness);
    bool msgReceived = false;
    while (gateSensorCounter<10 && !errorButtonPressed && !isSettingPins ){

      msgReceived = rcvMsg();
      delay(10);
      if( msgReceived) { readMsg(); msgReceived =false;}
      //if (incoming.wire == WIRE && incoming.cmd == 3) {settingPins(); resetIncoming();}


      if (digitalRead(GATE_RAMP)== LOW) {

      gateSensorCounter++;
      analogWrite(LED_START,0);
      resetOutgoing();
      break;

      }

    }

    if(!isSettingPins) {
      gateCounter++;
      unsigned long time;
      time = millis();
      while (millis() < time + 4000 && !errorButtonPressed) {

        checkPins();
        showFallenPins();


      }

      if(!isError) countPoints();
      outgoing.cmd = 1;
      outgoing.rounds=gateCounter;
      outgoing.wire = WIRE;



      delay(10);
      sndMsg();
      delay(10);
      sndMsg();
     // delay(500);
     for (int i = 0; i < 9; i++) {
      outgoing.pins[i] = 0;
    }

isError = false; errorButtonPressed = false; newState = false;



    } else { isSettingPins = false; }

  if (!noneFallen) {settingPins(); resetIncoming(); isSettingPins = false;}
  }

}




void game2()

{
  analogWrite(LED_ERROR, LOW);
  Serial.println("Dorazka");

  offLED();
  offMAG();
  lockMAG = 0;
  gameType = 2;

  resetFallenPins();

  while(true){

    isError = false; isSettingPins = false; noneFallen = false; errorButtonPressed = false;
    int gaffeSensorCounter = 0; gateSensorCounter = 0;

    analogWrite(LED_ERROR, 0);

    analogWrite(LED_START, brightness);
    bool msgReceived = false;
    while (gateSensorCounter<10 && !errorButtonPressed && !isSettingPins ){

      msgReceived = rcvMsg();
      delay(10);
      if( msgReceived) { readMsg(); msgReceived =false;}
      //if (incoming.wire == WIRE && incoming.cmd == 3) {settingPins(); resetIncoming();}


      if (digitalRead(GATE_RAMP)== LOW) {

      gateSensorCounter++;
      analogWrite(LED_START,0);
      resetOutgoing();
      break;

      }

    }

    if(!isSettingPins) {
      gateCounter++;
      unsigned long time;
      time = millis();
      while (millis() < time + 4000 && !errorButtonPressed) {

        checkPins();
        showFallenPins();


      }

      if(!isError) countPoints();
      outgoing.cmd = 2;
      outgoing.rounds=gateCounter;
      outgoing.wire = WIRE;



      delay(10);
      sndMsg();
      delay(10);
      sndMsg();
     // delay(500);
     for (int i = 0; i < 9; i++) {
      outgoing.pins[i] = 0;
    }

isError = false; errorButtonPressed = false; newState = false;



    }

  if (!noneFallen) settingPins2();
  }

}





















//********************* COMMUNICATION ***********************//

// sending message
void sndMsg(){
analogWrite(TXControl,255); //Tramsmitting

outgoing.wire = WIRE;
Serial1.print(outgoing.wire);

if (outgoing.cmd<10) Serial1.print(0);
Serial1.print(outgoing.cmd);

for (int i = 0; i<9; i++) Serial1.print(outgoing.pins[i]);

if (outgoing.rounds<10) Serial1.print(0);
Serial1.print(outgoing.rounds);

int checksum = 0;
checksum += outgoing.wire + outgoing.cmd + outgoing.rounds;
for (int i = 0; i<9; i++) checksum +=outgoing.pins[i];

Serial1.print(checksum);
Serial1.println();
Serial1.flush();

delay(100);
analogWrite(TXControl,0); //Receiving

rcvMsg();
delay(10);
if (incoming.cmd == 6) sndMsg();


  }

//********************************************************************
//receiving message
  bool rcvMsg(){

 //analogWrite(LED_ERROR, brightness);

    analogWrite(TXControl,0); //Receiving

    while (Serial1.available()) {

   incoming.wire = Serial1.read();
   incoming.cmd = Serial1.read();
   for (int i = 0; i<9; i++) incoming.pins[i] = Serial1.read();
   incoming.rounds = Serial1.read();
   //if (incoming.wire == WIRE && incoming.cmd == 3) {settingPins(); break;}
   delay(100);

Serial.println("Incoming cmd: ");
Serial.println(incoming.cmd);

   //if (incoming.wire == WIRE && incoming.cmd != 0) showCircle();
   //if (incoming.wire == WIRE && incoming.cmd == 3) {
  //  isSettingPins = true; showAll(); settingPins(); resetIncoming();}

return true;
    }

    return false;
//analogWrite(LED_ERROR, 0);
}





void readMsg(){
      if (incoming.wire == WIRE) {

        Serial.print(incoming.cmd);

        switch (incoming.cmd){


          case 100:
          analogWrite(LED_START, LOW);
          resetIncoming();
          loop();
          break;

          case 200:
          analogWrite(LED_START, LOW);
          newState = setState();
          analogWrite(LED_ERROR, brightness);
          analogWrite(LED_START, brightness);
          resetIncoming();
          break;

          case 3:
          //showAll();
          isSettingPins = true;
          //if (typHry == 1) stavanie(); else stavanieDorazka();
          resetIncoming();
          delay(250);
          break;

          /*case 26:
          spustit();
          resetIncoming();
          break;*/

          case 201:
          analogWrite(LED_START, LOW);
          analogWrite(LED_ERROR, brightness);
          isError = checkError();
          errorButtonPressed = true;
          resetIncoming();
          break;

          default: newState = false;
          break;
        }
      delay(100);
     }
      }
//*********************************************************************
