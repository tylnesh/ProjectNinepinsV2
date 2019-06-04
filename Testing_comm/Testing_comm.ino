
#include <SPI.h>
#define WIRE 1
#define LED_START 12
#define LED_ERROR 11
#define TXControl 53




int brightness = 80;
int LED[9] = {2,3,4, 5, 6, 7, 8, 9, 10};



struct message {
    int cmd = 0;
    int pins[9] = {0,0,0,0,0,0,0,0,0};
    int wire = 0;
    int rounds = 0;
    int score = 0;
    int checksum = 0;
  };



  message outgoing;
  message incoming;


bool rcvMsg(){

   analogWrite(TXControl,0); //Receiving

   message temporary;

   while (Serial1.available()) {

   temporary.wire = Serial1.read();
   temporary.cmd = Serial1.read();
   for (int i = 0; i<9; i++) temporary.pins[i] = Serial1.read();
   temporary.rounds = Serial1.read();
   temporary.score = Serial1.read();
   temporary.checksum = Serial1.read();
   delay(100);

   int checksum = temporary.wire + temporary.cmd + temporary.rounds + temporary.score;
   for (int i=0; i<9; i++) checksum += temporary.pins[i];
   
   
Serial.println("Incoming cmd: ");
Serial.println(temporary.cmd);
Serial.println("Incoming pins: ");
for (int i =0; i<9; i++) Serial.println(temporary.pins[i]);

Serial.println("Incoming checksum: ");
Serial.println(temporary.checksum);

Serial.println("My checksum: ");
Serial.println(checksum);

analogWrite(TXControl,255); 

if (temporary.checksum == checksum){
 incoming = temporary;
 
 Serial1.println(true); 
} else Serial1.println(false);
   delay(100);
   analogWrite(TXControl,0); //Receiving
//showState();
return true;
    }

    return false;

}




void sndMsg(){
analogWrite(TXControl,255); //Tramsmitting

outgoing.wire = WIRE;
Serial1.print(outgoing.wire);
Serial.print("Sending wire ");
Serial.println(outgoing.wire);

if (outgoing.cmd<10) Serial1.print(0);
Serial1.print(outgoing.cmd);
Serial.print("Sending cmd ");
Serial.println(outgoing.cmd);

for (int i = 0; i<9; i++) {Serial1.print(outgoing.pins[i]); Serial.print("Sending pin ");  Serial.print(i);
Serial.println(outgoing.pins[i]);} 

if (outgoing.rounds<10) Serial1.print(0);
Serial1.print(outgoing.rounds);
Serial.print("Sending rounds ");
Serial.println(outgoing.rounds);



if (outgoing.score<100) Serial1.print(0);
if (outgoing.score<10) Serial1.print(0);
Serial1.print(outgoing.score);
Serial.print("Sending score ");
Serial.println(outgoing.score);




outgoing.checksum = 0;
outgoing.checksum += outgoing.wire + outgoing.cmd + outgoing.rounds + outgoing.score;
for (int i = 0; i<9; i++) outgoing.checksum +=outgoing.pins[i];

if (outgoing.checksum<100) Serial1.print(0);
if (outgoing.checksum<10) Serial1.print(0);
Serial1.print(outgoing.checksum);
Serial.print("Sending checksum ");
Serial.println(outgoing.checksum);

//Serial1.println();
//Serial1.flush();

delay(100);
analogWrite(TXControl,0); //Receiving

rcvMsg();
delay(10);
if (incoming.cmd == 6) {
  sndMsg();
  Serial.println("Repeating message due to an error");
  }
//CHECKSUM HANDLING, CURRENTLY OFFLINE
//if (incoming.cmd == 6 && resendCounter<5) { Serial.println("RPI didn't receive checksum, resending"); sndMsg(); resendCounter++; }
//else resendCounter = 0;

  }




void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 Serial1.begin(57600);

 analogWrite(TXControl, 0); //Receiving


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
 
    
}

void loop() {

rcvMsg();
delay (100);



  

   outgoing.wire = WIRE;
   outgoing.cmd = 1;
   //for (int i = 0; i<9; i++) outgoing.pins[i] = Serial.read();
   outgoing.pins[0] = 1;
   outgoing.pins[2] = 1;
   outgoing.pins[4] = 1;
   outgoing.pins[6] = 1;
   outgoing.pins[8] = 1;

   outgoing.rounds = 5;
   outgoing.score = 20;
  
   if (incoming.cmd > 0) {sndMsg();
   delay(500);
   }
  

}





void controlLED(int ledNumber, bool state){
  if (state) analogWrite(LED[ledNumber], brightness);
  else analogWrite(LED[ledNumber], 0);
  }

void controlLED(bool state[9]){
  
   for (int i = 0; i<9; i++) {
    if (state[i]) analogWrite(LED[i], brightness);
    else  analogWrite(LED[i], 0);
    }
  }


void onAllLED() { for (int i = 0; i<9; i++) {analogWrite(LED[i],brightness); // Give a name to number 9
  delay(100);}
  analogWrite(LED_START,brightness);
  delay(100);
  analogWrite(LED_ERROR,brightness);
  
  
}

void offAllLED() { for (int i = 0; i<9; i++) { analogWrite(LED[i],0); delay(100);}

  analogWrite(LED_START,0);
  delay(100);
  analogWrite(LED_ERROR,0);
}// Give a name to number 9


    
    
    





   void showState()
  {
    Serial.println("Current Status: ");
    Serial.println("-----------------------");
    Serial.print("Incoming wire: "); Serial.println(incoming.wire);
    Serial.println("-----------------------");
    Serial.print("Incoming cmd: "); Serial.println(incoming.cmd);
    Serial.println("-----------------------");
    Serial.print("Incoming pins: "); for (int i = 0; i<9; i++) Serial.print(incoming.pins[i]); Serial.println();
    Serial.println("-----------------------");
    Serial.print("Incoming rounds: "); Serial.println(incoming.rounds);
    Serial.println("-----------------------");
    Serial.print("Incoming score: "); Serial.println(incoming.score);
    Serial.println("-----------------------");
    Serial.print("Incoming checksum: "); Serial.println(incoming.checksum);
    }
