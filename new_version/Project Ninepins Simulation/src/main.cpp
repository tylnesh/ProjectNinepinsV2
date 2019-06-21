#include <Arduino.h>
#include <SPI.h>
#include <stdint.h>
#include <array>

#define SIMULATION true
#define DEBUG_SWITCH true

#define DEBUG Serial
#define COMM Serial1

//WIRE
#define WIRE 1

//RS485 setting
#define TXControl 53


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

#define PINS_UP_TIME 15000
#define PINS_WAIT_UP 1800
#define TIME_TO_SETTLE_TRESHOLD 100000
#define TIME_TO_COUNT_POINTS_TRESHOLD 4000

//STATE variables

uint8_t currentPins[PINCOUNT] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t toMAG[PINCOUNT] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

bool noneFallen = false;
bool newState = false;
bool isSettingPins = false;
bool isGutter = false;
bool gutterButtonPressed = false;

uint16_t scoreCounter = 0;
uint8_t roundsCounter = 0;

uint8_t knotCounter = 0;
uint16_t overloadCounter = 0;

enum class Game: uint8_t {FULL_GAME = 1, PARTIAL_GAME = 2};
Game currentGameType;


enum commands : uint8_t {
  FULL_GAME = 24,
  PARTIAL_GAME = 25,
  CHANGE_OK = 41,
  CHANGE_CANCEL = 42,
  CHANGE_CMD = 40,
  SETTING_PINS = 3,
  END_GAME = 50,
  GAFFE_CONFIRMED = 66,
  GAFFE_CANCELED = 65,
  CHECKSUM_NOT_MATCH = 6,
  FULL_GAME_MSG = 1,
  CHECK_GAFFE = 61,
  ACKNOWLEDGED = 43,
  REQ_REPEAT = 44,
  KNOT_CMD = 70

};

static constexpr size_t PINS = PINCOUNT;
static constexpr int statusLength = PINS + 7;

union Status {
    struct {
        uint8_t wire;
        uint8_t cmd;
        std::array<uint8_t, PINS> pins;
        uint8_t rounds;
        uint16_t score;
        uint16_t checksum;
    };
    std::array<uint8_t, statusLength> bytes;
    uint8_t getPoints()
    {
        uint8_t points = 0;
        for (size_t i = 0; i < PINS; i++) if (pins[i]) points++;
        return points;
    }
};

Status *state;

Status incoming, outgoing;


// FORWARD DECLARATION

bool receiveMessage(); //receiveMessage needs to be declared here, otherwise the compiler screams.
void sendMessage();



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

// declaring functions
bool checkPins();
void resetPinCount();
void game(uint8_t gType);

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

// Deletes the contents of a Status
void deleteMessage(Status *m){ 
  m->wire = 0; 
  m->cmd = 0;
  for (int i = 0; i < PINCOUNT; i++) m->pins[i] = 0;
  m->rounds = 0;
  m->score = 0;
  m->checksum = 0;
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
     analogWrite(LED_ERROR, BRIGHTNESS); delay(200); analogWrite(LED_ERROR, 0);
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


void showCircle()
{
  debugPrintln("Animating circle of LEDs");
  for (int i = 0; i < PINCOUNT; i++)
  {
    if (currentPins[i] > 0) lightLed(LED[i], true);
  }

  lightLed(LED[0], true);
  delay(LIGHTTIME);
  lightLed(LED[0], true);

  lightLed(LED[1], true);
  delay(LIGHTTIME);
  lightLed(LED[1], true);

  lightLed(LED[3], true);
  delay(LIGHTTIME);
  lightLed(LED[3], true);

  lightLed(LED[6], true);
  delay(LIGHTTIME);
  lightLed(LED[6], true);

  lightLed(LED[8], true);
  delay(LIGHTTIME);
  lightLed(LED[8], true);

  lightLed(LED[7], true);
  delay(LIGHTTIME);
  lightLed(LED[7], true);

  lightLed(LED[5], true);
  delay(LIGHTTIME);
  lightLed(LED[5], true);

  lightLed(LED[2], true);
  delay(LIGHTTIME);
  lightLed(LED[2], true);

  lightLed(LED[0], true);
  lightLed(LED[1], true);
  lightLed(LED[3], true);
  lightLed(LED[6], true);
  lightLed(LED[8], true);
  lightLed(LED[7], true);
  lightLed(LED[5], true);
  lightLed(LED[2], true);  
}

//Lights up all the pin leds
void showAll() 
{
  debugPrintln("Let there be light");
  for (int i = 0; i < PINCOUNT; i++) lightLed(LED[i], true);
  delay(2*LIGHTTIME);
  for (int i = 0; i < PINCOUNT; i++) lightLed(LED[i], false);
  delay(2*LIGHTTIME);
  for (int i = 0; i < PINCOUNT; i++) lightLed(LED[i], true);
}


/*  
Lights up leds corresponding to fallen pins. 
If the fallen pins form a circle and the game type is "Full Game", 
it displays an animated circle. If the player downs all the pins in one go,
it blinks several times.
*/
void showFallenPins()
{
  uint8_t fallenCounter = 0;
  
  for (int i = 0; i < PINCOUNT; i++)
  {
    if (currentPins[i] > 0)
    {
      fallenCounter++;
      lightLed(LED[i], true);
      toMAG[i]++;
    } else lightLed(LED[i], false);
  }

  if ((fallenCounter == 8) && (currentPins[4] == 0) && (currentGameType == Game::FULL_GAME))
  {
    showCircle();
  }

  if (fallenCounter == PINCOUNT)
  {
    showAll();
  }
  
}

bool setState()
{
  debugPrintln("***********CHANGING STATE***********");
  while (true)
  {
    receiveMessage();
    if (state->cmd == CHANGE_OK)
    {
      roundsCounter = state->rounds;
      scoreCounter = state->score;
      for (int i = 0; i < PINCOUNT; i++)
      {
       toMAG[i] = currentPins[i] = state->pins[i];
      }
      showFallenPins();
      return true;
    }

    if (state->cmd == CHANGE_CANCEL)
    {
      lightLed(LED_ERROR, false);
      return false;
    }  
  }  
}


//******************************** COMMUNICATION ***********************************


//calculates checksum of a Status
void calculateChecksum(Status *msg){
msg->checksum = 0;
msg->checksum += msg->wire + msg->cmd + msg->rounds + msg->score;
for (int i = 0; i < PINCOUNT; i++) msg->checksum +=msg->pins[i];
}

void calculateChecksum(Status *msg, uint16_t *checksum){
*checksum = 0;
*checksum += msg->wire + msg->cmd + msg->rounds + msg->score;
for (int i = 0; i < PINCOUNT; i++) checksum += msg->pins[i];
  debugPrint("Calculated checksum: "); debugPrintln(String(*checksum));

}





//receive Status
bool receiveMessage(){
  startReceiving();

  while(COMM.available()) {
    debugPrintln("receiving msg");
    
  Status *temporary;
  byte buffer[statusLength];
  COMM.readBytes(buffer, statusLength);
  temporary = reinterpret_cast<Status*>(buffer);
  
  debugPrint("Incoming wire: "); debugPrintln((String)temporary->wire);
  debugPrint("Incoming cmd: "); debugPrintln((String)temporary->cmd);
  debugPrint("Incoming pins: "); for (int i = 0; i < PINCOUNT; i++) debugPrintln((String)temporary->pins[i]);
  debugPrint("Incoming rounds: "); debugPrintln((String)temporary->rounds);
  debugPrint("Incoming score: "); debugPrintln((String)temporary->score);
  debugPrint("Incoming checksum: "); debugPrintln((String)temporary->checksum);

  
  uint16_t checksum = 0;
  calculateChecksum(temporary, &checksum);
  //checksum += temporary->wire + temporary->cmd + temporary->rounds + temporary->score;
  //for (uint8_t i = 0; i < PINS; i++) checksum += temporary->pins[i];
  
  debugPrint("My checksum: "); debugPrintln(String(checksum));

   delay(100);

  startTransmitting();

  if (temporary->checksum == checksum){
    state = temporary; 

    state->cmd = 43; 
    debugPrintln("sending ACK");
    sendMessage();
    } else {
    state->cmd = 44;
    debugPrintln("sending REQ");
    sendMessage();
    receiveMessage();
    }
    delay(100); // To send Status over rs485, you need delays to ensure the Status went through
    startReceiving();
    return true;
  }
  return false ;
  }


//sending Status
void sendMessage(){
  startTransmitting();
  state->wire = WIRE;

  state->checksum = 0 + state->wire + state->cmd + state->rounds + state->score;
  for (uint8_t i = 0; i < PINS; i++) state->checksum += state->pins[i];
  
  debugPrint("Sending wire: "); debugPrintln((String)state->wire);
  debugPrint("Sending cmd: "); debugPrintln((String)state->cmd);
  debugPrint("Sending pins: "); for (int i = 0; i < PINCOUNT; i++) debugPrintln((String)state->pins[i]);
  debugPrint("Sending rounds: "); debugPrintln((String)state->rounds);
  debugPrint("Sending score: "); debugPrintln((String)state->score);
  
  
  debugPrint("Sending msg with checksum: "); debugPrintln((String)state->checksum);
  
  
  byte buffer[statusLength];
  for (size_t i = 0; i < statusLength; i++)
    {
        buffer[i] = state->bytes.at(i);
    }


  COMM.write(buffer,sizeof(buffer));
  delay(100); // To send Status over rs485, you need delays to ensure the Status went through

  receiveMessage();
  if (state->cmd == REQ_REPEAT) {
    sendMessage();
    debugPrintln("Repeating Status due to an error");
    }
}

bool checkGutter()
{
  debugPrintln("Checking whether the ball hit the gutter");
  bool tempPins[PINCOUNT] = {0,0,0,0,0,0,0,0,0}; 
  for (int i = 0; i < PINCOUNT; i++) tempPins[i] = currentPins[i];
  lightLed(LED_ERROR, true);

  while (true)
  {
    if (digitalRead(GATE_RAMP) == HIGH) lightLed(LED_START, true);
    checkPins();
    showFallenPins();

    receiveMessage();
    if (incoming.wire == WIRE)
    {
      switch (incoming.cmd)
      {
      case GAFFE_CANCELED:
        debugPrintln("No gutter");
        lightLed(LED_ERROR, false);
        return false;
      
      case GAFFE_CONFIRMED:
        debugPrintln("Gutter confirmed");
        if (currentGameType == Game::FULL_GAME)
        {
          resetPinCount();
        }
        else
        {
          for (int i = 0; i < PINCOUNT; i++) {
            toMAG[i] = currentPins[i] = outgoing.pins[i] = tempPins[i];
            lightLed(LED[i], false);
          }
          lightLed(LED_ERROR, true);
          showFallenPins();
          return true;
        }
    
      default:
        break;
      }
    }
  }
}


void readMsg()
{
  if (incoming.wire == WIRE) 
  {
    debugPrintln("Reading Status");
    switch (state->cmd)
    {
          
      case CHANGE:
      lightLed(LED_START, false);
      newState = setState();
      if (newState) lightLed(LED_ERROR, true);
      lightLed(LED_START, true);
      break;

      case SETTING_PINS:
      isSettingPins = true;
      delay(100);
      break;

      case CHECK_GAFFE:
      lightLed(LED_START, false);
      lightLed(LED_ERROR, true);
      gutterButtonPressed = true;
      debugPrintln("The gutter button has been pressed");
      isGutter = checkGutter();
      break;
    
      default:
      newState = false;
      break;
    }
  }

}




//Funtions that call an employee to come and untie the knotted pins.
void untieKnot()
  {
    
    state->cmd = KNOT_CMD; // Send Status that Arduino is listening
    sendMessage();

    debugPrintln("If the pins are untied, press 5 on the keyboard");
    while (true) {
      startReceiving();
      if (COMM.available())
      {
        receiveMessage();
        delay(10);
        if (incoming.wire == WIRE && incoming.cmd == KNOT_CMD) break;
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

//checking which pins have fallen - returns true if all are standing, false if at least one has fallen
bool checkPins() {
  //checking if there are any Statuss while checking for fallen pins
  bool msgReceived = false;
  msgReceived = receiveMessage(); 
  if( msgReceived) { readMsg(); msgReceived =false;}
  
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
void settingPins(Game gType)
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
    
    while (millis() < pinsUpTimer + PINS_UP_TIME) {
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
        delay(PINS_WAIT_UP);
        
        if(gType == Game::FULL_GAME) 
        {
          resetPinCount();
          debugPrintln("LOWERING THE PINS");
          pinsLower();
        }
        if(gType == Game::PARTIAL_GAME)
        {
          uint8_t lockMAG = 0; // variable to store number of locked pins
          for (int i = 0; i < PINCOUNT; i++) if (toMAG[i] > 0) lockMAG++;
          debugPrintln("Number of locked pins: " + lockMAG);
          if (lockMAG < PINCOUNT)
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
      while (millis() < timeToSettle + TIME_TO_SETTLE_TRESHOLD)
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

void countPoints()
{
    
  for (int i = 0; i < PINCOUNT; i++)
  {
    if (currentPins[i] > 0) 
    {
      outgoing.pins[i] = 1;
      scoreCounter++;
    }  
  }
  outgoing.score = scoreCounter;
} 


//Game logic function
void game(Game gType)
{
  currentGameType = gType;
  lightLed(LED_ERROR, false);
  if (currentGameType == Game::FULL_GAME) 
  {
    debugPrintln("FULL GAME");
    roundsCounter = 0;
    scoreCounter = 0;
  }
  
  if (currentGameType == Game::PARTIAL_GAME) 
  {
    debugPrintln("PARTIAL GAME");
    roundsCounter = 0; //score only zeores in full game, as partial game is a continuation of the full game.
  }
  
  lightAllLed(false);

  while (true)
  {
    isGutter = false;
    isSettingPins = false;
    noneFallen = true;
    gutterButtonPressed = false;
    int gateSensorCounter = 0;
    lightLed(LED_ERROR, false);
    if (currentGameType == Game::FULL_GAME)
    {
      resetPinCount(); // pin count doesn not reset between rounds in partialgame 
      lightAllLed(false);
    }
    lightLed(LED_START, true);

    //Waiting for the ball to go through the gate, or command from the user
    while (gateSensorCounter < 10 && !gutterButtonPressed && !isSettingPins) 
    {
      if (receiveMessage()) readMsg();
      if (digitalRead(GATE_RAMP) == HIGH) gateSensorCounter++;
    }

    lightLed(LED_START, false);

    //if you trigger setting pins with a command, it bypasses counting points
    if (!isSettingPins)
    {
      roundsCounter++;
      uint32_t timeToCountPoints = millis();
      while ( (millis() < timeToCountPoints + TIME_TO_COUNT_POINTS_TRESHOLD) && !gutterButtonPressed)
      {
        checkPins();
        showFallenPins();
      }

      //if the ball didn't touch the sides, count points
      if (!isGutter) countPoints();
      outgoing.wire = WIRE;
      outgoing.cmd = (uint8_t)currentGameType;
      outgoing.rounds = roundsCounter;
      sendMessage();

      //if at least one pin has fallen, run settingPins function
      if (!noneFallen) 
      {
        settingPins(currentGameType);
      }
    }
  }
  
}



void startGame()
{
  deleteMessage(state);
  debugPrintln("Project Ninepins - wired version");
  while (true)
  {
    receiveMessage();
    if (incoming.wire == WIRE)
    {
      switch (incoming.cmd)
      {
      case SETTING_PINS:
        debugPrintln("Setting Pins");
        settingPins(Game::FULL_GAME);
        break;
    
      case FULL_GAME:
        debugPrintln("Starting Full Game");
        game(Game::FULL_GAME);
        break;

      case PARTIAL_GAME:
        debugPrintln("Starting Full Game");
        game(Game::PARTIAL_GAME);
        break;
    
      default:
        break;
      }
    }
    

  }
}

// ******************************  SETUP FUNCTION *******************************

void setup() {

  DEBUG.begin(9600);
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

  for (int i = 0; i < PINCOUNT; i++) digitalWrite(MAG[i], LOW);

  currentGameType = Game::FULL_GAME;

  deleteMessage(state);
}

void loop() {
  //roundsCounter = 0;
  //checkLED();
  //if (currentGameType != fullgame) settingPins(fullgame);
  //lightLed(LED_ERROR,true);
  //lightLed(LED_START,true);
  //deleteMessage(outgoing);
  //startGame();

  receiveMessage();
} 