#include <Arduino.h>

#define DEBUG_SWITCH true

#define DEBUG Serial
#define COMM Serial1

//WIRE
#define WIRE 1

//RS485 setting
#define TXControl 53
#include <SPI.h>

//Machine pins
uint8_t PXSENSOR[9] = {52, 50, 48, 46, 44, 42, 40, 38, 36};
#define PXSENSOR_UP 34
#define PXSENSOR_DOWN 32
#define PXSENSOR_OVERLOAD 30

uint8_t MAG[9] = {51, 49, 47, 45, 43, 41, 39, 37, 35};

#define GATE_RAMP 26

#define ENGINE_RIGHT 31
#define ENGINE_LEFT 29
#define ENGINE_SLOW 27

uint8_t LED[9] = {2, 3, 4, 5, 6, 7, 8, 9, 10};


//LED pins
#define LED_START 11
#define LED_ERROR 12
#define LED_CARD 13

//Engine settings
#define OVERLOAD 300
#define ENGINEDOWN 500
#define ENGINESLOWDOWN 1900

#define PINCOUNT 9
#define BRIGHTNESS 80

#define LIGHTTIME 55

#define KNOTTHRESHOLD 8
#define PINSUPTHRESHOLD 5

#define PINSUPTIME 15000
#define PINSWAITUP 1800
#define TIMETOSETTLETRESHOLD 100000

//STATE variables

uint8_t currentPins[PINCOUNT] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t toMAG[PINCOUNT] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

bool noneFallen = false;

uint8_t currentGameType = 0;

uint8_t roundsCounter = 0;
uint8_t knotCounter = 0;

uint16_t overloadCounter = 0;

enum gameType{fullgame, partialgame};

enum commands{knotCmd = 3, repeatMsgCmd = 6};

struct message {
    int cmd = 0;
    int pins[PINCOUNT] = {0,0,0,0,0,0,0,0,0};
    int wire = 0;
    int rounds = 0;
    int score = 0;
    int checksum = 0;
  };

  message outgoing;
  message incoming;

// print into debug serial functions - if you disable all the debug in the header
void debugPrintln(String str)
{
  if (DEBUG_SWITCH) DEBUG.println(str);
}

void debugPrint(String str)
{
  if (DEBUG_SWITCH) DEBUG.print(str);
}

void startReceiving(){
  analogWrite(TXControl, 0); //Receiving
}

void startTransmitting(){
  analogWrite(TXControl, 255); //Transmitting
}

// Controlling the LEDs - Passing "true" sets the LEDS to turn on, false dims them down.
void lightAllLed(bool b)
{
  if (b) 
  {
    for (int i = 0; i < PINCOUNT; i++) analogWrite(LED[i], BRIGHTNESS);
    analogWrite(LED_START, BRIGHTNESS);
    analogWrite(LED_ERROR, BRIGHTNESS);
  } else
  {
    for (int i = 0; i < PINCOUNT; i++) analogWrite(LED[i], 0);
    analogWrite(LED_START, 0);
    analogWrite(LED_ERROR, 0);
  }  
}

void lightLed(uint8_t led, bool b)
{
if (b) analogWrite(led, BRIGHTNESS);
else analogWrite(led, 0);
}

// Deletes the contents of a message
void deleteMessage(message m){ 
  m.cmd = 0;
  for (int i = 0; i < PINCOUNT; i++) m.pins[i] = 0;
  m.wire = 0; 
  m.rounds = 0;
  m.score = 0;
  m.checksum = 0;
}

// checking LEDs
void checkLED()
  {
    debugPrintln("************CHECKING LEDS*************");
    for (int i = 0; i < PINCOUNT; i++) {
      analogWrite(LED[i], BRIGHTNESS);
      delay(LIGHTTIME);
      analogWrite(LED[i], 0);
    }  
     analogWrite(LED_START, BRIGHTNESS); delay(200); analogWrite(LED_START, 0);
     analogWrite(LED_ERROR,BRIGHTNESS); delay(200); analogWrite(LED_ERROR, 0);
     analogWrite(LED_START, BRIGHTNESS); delay(200); analogWrite(LED_START, 0);
  }

// Stopping all engine movement
void stopEngines()
  {
    digitalWrite(ENGINE_RIGHT, LOW);
    digitalWrite(ENGINE_SLOW, LOW);
    digitalWrite(ENGINE_LEFT, LOW);
  }

// Protects the engines from overloading due to knotted pins
void fixOverload()
{
  knotCounter++;
  stopEngines();
  delay(1000);
  digitalWrite(ENGINE_LEFT, HIGH);
  delay(800);
  digitalWrite(ENGINE_LEFT, LOW);
  delay(400);
  overloadCounter = 0;

}

//calculates checksum of a message
void calculateChecksum(message msg){
msg.checksum = 0;
msg.checksum += msg.wire + msg.cmd + msg.rounds + msg.score;
for (int i = 0; i < PINCOUNT; i++) msg.checksum +=msg.pins[i];
}

void calculateChecksum(message msg, uint16_t *checksum){
checksum = 0;
checksum += msg.wire + msg.cmd + msg.rounds + msg.score;
for (int i = 0; i < PINCOUNT; i++) checksum += msg.pins[i];
}


//******************************** COMMUNICATION ***********************************
//receive message
bool rcvMsg(){
  startReceiving();
  message temporary;
  while(COMM.available()) {
    temporary.wire = COMM.read();
    temporary.cmd = COMM.read();
    for (int i = 0; i < PINCOUNT; i++) temporary.pins[i] = COMM.read();
    temporary.rounds = COMM.read();
    temporary.score = COMM.read();
    temporary.checksum = COMM.read();
    delay(100);
    calculateChecksum(temporary);
  
  debugPrintln("Incoming wire: " + temporary.wire);
  debugPrintln("Incoming cmd: " + temporary.cmd);
  debugPrintln("Incoming pins: "); for (int i =0; i < PINCOUNT; i++) debugPrintln((String)temporary.pins[i]);
  debugPrintln("Incoming rounds: " + temporary.rounds);
  debugPrintln("Incoming score: " + temporary.score);
  debugPrintln("Incoming checksum: " + temporary.checksum);

  
  uint16_t checksum = 0;
  calculateChecksum(temporary, &checksum);
  debugPrintln("My checksum: " + checksum);

  startTransmitting();

  if (temporary.checksum == checksum){
    incoming = temporary; 
    COMM.println(true);
    } else COMM.println(false);
    delay(100); // To send message over rs485, you need delays to ensure the message went through
    startReceiving();
    return true;
  }
  return false;
  }

//sending message
void sndMsg(){
startTransmitting();

//sending WIRE
outgoing.wire = WIRE;
COMM.print(outgoing.wire);
debugPrintln("Sending wire " + outgoing.wire);

//sending CMD
if (outgoing.cmd<10) COMM.print(0);
COMM.print(outgoing.cmd);
debugPrintln("Sending cmd " + outgoing.cmd);

//sending PINS
for (int i = 0; i < PINCOUNT; i++) {
  COMM.print(outgoing.pins[i]); 
  debugPrintln((String)"Sending pin " + i + " " + outgoing.pins[i]);
}

//sending ROUNDS
if (outgoing.rounds<10) COMM.print(0);
COMM.print(outgoing.rounds);
debugPrintln("Sending rounds " + outgoing.rounds);

//sending SCORE
if (outgoing.score<100) COMM.print(0);
if (outgoing.score<10) COMM.print(0);
COMM.print(outgoing.score);
debugPrintln("Sending score " + outgoing.score);

//sending CHECKSUM
calculateChecksum(outgoing);
if (outgoing.checksum<100) COMM.print(0);
if (outgoing.checksum<10) COMM.print(0);
COMM.print(outgoing.checksum);
debugPrintln("Sending checksum " + outgoing.checksum);

delay(100); // To send message over rs485, you need delays to ensure the message went through

rcvMsg();
if (incoming.cmd == repeatMsgCmd) {
  sndMsg();
  debugPrintln("Repeating message due to an error");
  }
}





//Funtions that call an employee to come and untie the knotted pins.
void untieKnot()
  {
    deleteMessage(incoming);
    deleteMessage(outgoing);
    outgoing.cmd = knotCmd; // Send message that Arduino is listening
    sndMsg();

    debugPrintln("If the pins are untied, press 5 on the keyboard");
    while (true) {
      startReceiving();
      if (COMM.available())
      {
        rcvMsg();
        delay(10);
        if (incoming.wire == WIRE && incoming.cmd == knotCmd) break;
      }
      //if the pins are untied, press 5 on the keyboard
      uint8_t val = DEBUG.parseInt();
      if (val  == 5) break;
    }
  }


//Lowering the pins
void pinsLower()
{
  digitalWrite(ENGINE_RIGHT, HIGH);
  delay(ENGINEDOWN);//lowering dole odstopovat
  digitalWrite(ENGINE_SLOW, HIGH);
  delay(ENGINESLOWDOWN);
  digitalWrite(ENGINE_SLOW, LOW);
}

//resetting pin count
 void resetPinCount()
  {
    debugPrintln("************ZEROING THE PINS*************");
    for (int i = 0; i < PINCOUNT; i++) currentPins[i] = 0;
  }

//checking if the pins don't fall while setting down - returns true if all are standing, false if at least one has fallen
bool checkSettingPins() {
    noneFallen = false;
    int countStandingPins = 0;
    for (int i = 0; i < PINCOUNT; i++)
    {
      if (digitalRead(PXSENSOR[i]) != LOW) 
      {
        countStandingPins++;
      }
    }
    if (countStandingPins == PINCOUNT)  return true;
    else return false;
}








// setting pins 
void settingPins(int gType)
{
  debugPrintln("************SETTING PINS*************");
  
  uint8_t pinsUpCounter = 0; //
  uint8_t knotCounter = 0;   // if it reaches the KNOTTHRESHOLD, call employee to untie the knot

  lightLed(LED_START,false);
  debugPrintln("Waiting for pins up");

  while(pinsUpCounter < PINSUPTHRESHOLD){
    
    uint32_t pinsUpTimer = millis();
    uint8_t upSensor = 0; 
    bool pinsUp = false;
    
    while (millis() < pinsUpTimer + PINSUPTIME) {
      digitalWrite(ENGINE_RIGHT, HIGH);
      
      //CHECKING IF THE ENGINES ARE BEING OVERLOADED
      if (digitalRead(PXSENSOR_OVERLOAD) == HIGH) {
          overloadCounter++;
          debugPrintln("ADDING TO OVERLOAD");
        }

      //CHECKING IF THE OVERLOAD HAS REACHED THE THRESHOLD
      if (overloadCounter > OVERLOAD ) {
        debugPrintln("OVERLOAD REACHED");
        stopEngines(); 
        fixOverload();
        digitalWrite(ENGINE_RIGHT, HIGH);
        }

      //CHECKING IF THE PINS ARE KNOTTED UP
      if (knotCounter > KNOTTHRESHOLD) {
          stopEngines();
          Serial.print("Prid mi rozchlpit kolky");
          untieKnot();
          overloadCounter = 0;
          knotCounter = 0;
        }
      
      //checking if the pins are up
      if (digitalRead(PXSENSOR_UP) == LOW) upSensor++;
      if (upSensor > 3) {
        stopEngines();
        debugPrintln("PINS ARE UP");
        pinsUp = true;
        break;
      }

      //if pins are up, we set them down to the ground
      if (pinsUp) {
        stopEngines();
        delay(PINSWAITUP);
        
        if(gType == fullgame) 
        {
          resetPinCount();
          debugPrintln("LOWERING THE PINS");
          pinsLower();
        }
        if(gType == partialgame)
        {
          uint8_t lockMAG = 0; // variable to store number of locked pins
          for (int i = 0; i < PINCOUNT; i++) if (toMAG[i] > 0) lockMAG++;
          debugPrintln("Number of locked pins: " + lockMAG);
          if (lockMAG < 9)
          {
            for (int i = 0; i < PINCOUNT; i++) if (toMAG[i] > 0) digitalWrite(MAG[i], HIGH);
            digitalWrite(ENGINE_RIGHT, HIGH);
            delay(ENGINEDOWN); 
            for (int i = 0; i < PINCOUNT; i++) if (toMAG[i] > 0) digitalWrite(MAG[i], LOW);
            digitalWrite(ENGINE_SLOW, HIGH);
            delay(ENGINESLOWDOWN);
            digitalWrite(ENGINE_SLOW, LOW);
          } 
          else 
          {
            for (int i = 0; i < PINCOUNT; i++) 
            {
            digitalWrite(MAG[i], LOW);
            toMAG[i] = 0; 
            currentPins[i] = 0;
            }
            lightAllLed(false);
            pinsLower();
          }

        }
      }

      uint32_t timeToSettle = millis();
      while (millis() < timeToSettle + TIMETOSETTLETRESHOLD)
      {
        if (digitalRead(PXSENSOR_DOWN) == LOW) 
        {
          debugPrintln("PINS ARE SETTLED DOWN");
          stopEngines();
          if (!checkSettingPins()) settingPins(gType);
          debugPrintln("SETTING PINS - COMPLETE");
          lightLed(LED_START, true);
          return;
        }
      }

  }
  }
}







// ******************************  SETUP FUNCTION *******************************

void setup() {

  DEBUG.begin(57600);
  COMM.begin(57600);

  startReceiving();
  
  //Setting PXSENSORS pins to INPUT
  for(int i = 0; i < PINCOUNT; i++) pinMode(PXSENSOR[i], INPUT);
  pinMode(PXSENSOR_UP, INPUT);
  pinMode(PXSENSOR_DOWN, INPUT);
  pinMode(PXSENSOR_OVERLOAD, INPUT);

  pinMode(GATE_RAMP, INPUT);

  //Setting locking MAGNET pins to OUTPUT

  for(int i = 0; i < PINCOUNT; i++) pinMode(MAG[i], OUTPUT);

  //Setting ENGINE control pins to OUTPUT
  pinMode(ENGINE_RIGHT, OUTPUT);
  pinMode(ENGINE_LEFT, OUTPUT);
  pinMode(ENGINE_SLOW, OUTPUT);

  //Setting LED pins to OUTPUT 
  for(int i = 0; i < PINCOUNT; i++) pinMode(LED[i], OUTPUT);
  pinMode(LED_START, OUTPUT);
  pinMode(LED_ERROR, OUTPUT) ;

  lightAllLed(false);

  //Keeping ENGINE pins OFF
  digitalWrite(ENGINE_LEFT, LOW);
  digitalWrite(ENGINE_RIGHT, LOW);
  digitalWrite(ENGINE_SLOW, LOW);

  for (int i = 0; i < 9; i++) digitalWrite(MAG[i], LOW);

  currentGameType = fullgame;

  deleteMessage(outgoing);
  deleteMessage(incoming);
}

void loop() {
  roundsCounter = 0;
  checkLED();
  if (currentGameType != fullgame) settingPins(fullgame);
  lightLed(LED_ERROR,true);
  lightLed(LED_START,true);
  deleteMessage(outgoing);
  startGame();
}