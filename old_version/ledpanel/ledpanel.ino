
Skip to content
Pull requests
Issues
Marketplace
Explore
@tylnesh

1
0

    0

tylnesh/Ninepins
Code
Issues 0
Pull requests 0
Projects 0
Wiki
Security
Insights
Settings
Ninepins/ledpanel/ledpanel.ino
@tylnesh tylnesh Tweaked the UI and reworked the communication between RPi and arduinos. 2695097 on Sep 17, 2017
768 lines (577 sloc) 22.3 KB
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include <SoftwareSerial.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif


#define PIN_0            3

#define PIN_1            5

#define PIN_2            6

#define PIN_3            9

#define PIN_4            10

#define PIN_5            11

#define WIRE 3
#define TXControl 2



#define NUMPIXELS      28
int resendCounter = 0;

int lastPins = 0;
int lastRounds = 0;
int lastScore = 0;
struct message{
int wire = 0;
int pins = 0 ;
int rounds = 0;
int score = 0;
};

message incoming;

Adafruit_NeoPixel pixel[] = {
  Adafruit_NeoPixel(NUMPIXELS, PIN_0, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PIN_1, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PIN_2, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PIN_3, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PIN_4, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PIN_5, NEO_GRB + NEO_KHZ800)
                           };


int delayval = 500; // delay for half a second
int micro=400;



SoftwareSerial Serial1(0,1);

void setup() {
Serial.begin(57600);
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif


 for (int i =0; i<6; i++) pixel[i].begin();
 Serial1.begin(57600);
}








//
void Nuluj(int p){

  for(int i=0;i<NUMPIXELS;i++){

    // pixel[p].Color takes RGB values, from 0,0,0 up to 255,255,255
    pixel[p].setPixelColor(i, pixel[p].Color(0,0,0)); // Moderately bright green color.

    pixel[p].show(); // This sends the updated pixel color to the hardware.
delayMicroseconds(50);

  }}

//***************************************cislo jedna*****************************************


void NumberOne(int p){
 pixel[p].setPixelColor(8, pixel[p].Color(0, 200, 0)); // Moderately bright green color.
 pixel[p].setPixelColor(9, pixel[p].Color(0, 200, 0)); // Moderately bright green color.
 pixel[p].setPixelColor(10, pixel[p].Color(0, 200, 0)); // Moderately bright green color.
 pixel[p].setPixelColor(11, pixel[p].Color(0, 200, 0)); // Moderately bright green color.
 pixel[p].setPixelColor(24, pixel[p].Color(0, 200, 0)); // Moderately bright green color.
 pixel[p].setPixelColor(25, pixel[p].Color(0, 200, 0)); // Moderately bright green color.
 pixel[p].setPixelColor(26, pixel[p].Color(0, 200, 0)); // Moderately bright green color.
 pixel[p].setPixelColor(27, pixel[p].Color(0, 200, 0)); // Moderately bright green color.
 pixel[p].show();

}

//**************************************************************************************************************
//**************************************************************************************************************

//**********************************************cislo 2****************************************************************
void NumberTwo(int p){
 for(int i=4;i<24;i++){

    // pixel[p].Color takes RGB values, from 0,0,0 up to 255,255,255
    pixel[p].setPixelColor(i, pixel[p].Color(0, 200, 0)); // Moderately bright green color.

    pixel[p].show(); // This sends the updated pixel color to the hardware.
delayMicroseconds(micro);
 }}

//**************************************************************************************************************
//**************************************************************************************************************

//**********************************************cislo 3****************************************************************




 void NumberThree(int p){
 for(int i=4;i<16;i++){

    // pixel[p].Color takes RGB values, from 0,0,0 up to 255,255,255
    pixel[p].setPixelColor(i, pixel[p].Color(0, 200, 0)); // Moderately bright green color.

    pixel[p].show(); // This sends the updated pixel color to the hardware.

  delayMicroseconds(micro);
 }
  for(int i=20;i<28;i++){

    // pixel[p].Color takes RGB values, from 0,0,0 up to 255,255,255
    pixel[p].setPixelColor(i, pixel[p].Color(0, 200, 0)); // Moderately bright green color.

    pixel[p].show(); // This sends the updated pixel color to the hardware.
delayMicroseconds(micro);

 }}


//**************************************************************************************************************
//**************************************************************************************************************

//**********************************************cislo 3****************************************************************





 void NumberFour(int p){
  for(int i=0;i<4;i++){

    // pixel[p].Color takes RGB values, from 0,0,0 up to 255,255,255
    pixel[p].setPixelColor(i, pixel[p].Color(0, 200, 0)); // Moderately bright green color.

    pixel[p].show(); // This sends the updated pixel color to the hardware.

    delayMicroseconds(micro);   // Delay for a period of time (in milliseconds).

  }
  for(int i=8;i<16;i++){

    // pixel[p].Color takes RGB values, from 0,0,0 up to 255,255,255
    pixel[p].setPixelColor(i, pixel[p].Color(0, 200, 0)); // Moderately bright green color.

    pixel[p].show(); // This sends the updated pixel color to the hardware.

   delayMicroseconds(micro);  // Delay for a period of time (in milliseconds).

  }
   for(int i=24;i<28;i++){

    // pixel[p].Color takes RGB values, from 0,0,0 up to 255,255,255
    pixel[p].setPixelColor(i, pixel[p].Color(0, 200, 0)); // Moderately bright green color.

    pixel[p].show(); // This sends the updated pixel color to the hardware.

    delayMicroseconds(micro);   // Delay for a period of time (in milliseconds).

  }
}






 void NumberFive(int p){
   pixel[p].setPixelColor(0, pixel[p].Color(0, 200, 0)); // Moderately bright green color.
 for(int i=0;i<8;i++){

    // pixel[p].Color takes RGB values, from 0,0,0 up to 255,255,255
    pixel[p].setPixelColor(i, pixel[p].Color(0, 200, 0)); // Moderately bright green color.

    // This sends the updated pixel color to the hardware.


delayMicroseconds(micro);
 }
  for(int i=12;i<16;i++){

    // pixel[p].Color takes RGB values, from 0,0,0 up to 255,255,255
    pixel[p].setPixelColor(i, pixel[p].Color(0, 200, 0)); // Moderately bright green color.

    pixel[p].show(); // This sends the updated pixel color to the hardware.

delayMicroseconds(micro);

 } for(int i=20;i<28;i++){

    // pixel[p].Color takes RGB values, from 0,0,0 up to 255,255,255
    pixel[p].setPixelColor(i, pixel[p].Color(0, 200, 0)); // Moderately bright green color.

    pixel[p].show(); // This sends the updated pixel color to the hardware.

delayMicroseconds(micro);
 }
}






 void NumberSix(int p){
  pixel[p].setPixelColor(0, pixel[p].Color(0, 200, 0)); // Moderately bright green color.

 for(int i=0;i<8;i++){

    // pixel[p].Color takes RGB values, from 0,0,0 up to 255,255,255
    pixel[p].setPixelColor(i, pixel[p].Color(0, 200, 0)); // Moderately bright green color.

   // This sends the updated pixel color to the hardware.
delayMicroseconds(micro);

 }
  for(int i=12;i<28;i++){

    // pixel[p].Color takes RGB values, from 0,0,0 up to 255,255,255
   pixel[p].setPixelColor(i, pixel[p].Color(0, 200, 0)); // Moderately bright green color.

    pixel[p].show(); // This sends the updated pixel color to the hardware.
delayMicroseconds(micro);

 }
}





 void NumberSeven(int p){
   pixel[p].setPixelColor(0, pixel[p].Color(0, 200, 0)); // Moderately bright green color.

 for(int i=0;i<12;i++){

    // pixel[p].Color takes RGB values, from 0,0,0 up to 255,255,255
    pixel[p].setPixelColor(i, pixel[p].Color(0, 200, 0)); // Moderately bright green color.
delayMicroseconds(micro);
 // This sends the updated pixel color to the hardware.


 }
  for(int i=24;i<28;i++){

    // pixel[p].Color takes RGB values, from 0,0,0 up to 255,255,255
   pixel[p].setPixelColor(i, pixel[p].Color(0, 200, 0)); // Moderately bright green color.

    pixel[p].show(); // This sends the updated pixel color to the hardware.

  delayMicroseconds(micro);
 }
}


 void NumberEight(int p){
    pixel[p].setPixelColor(0, pixel[p].Color(0, 200, 0)); // Moderately bright green color.
 for(int i=0;i<28;i++){

    // pixel[p].Color takes RGB values, from 0,0,0 up to 255,255,255
    pixel[p].setPixelColor(i, pixel[p].Color(0, 200, 0)); // Moderately bright green color.

    pixel[p].show(); // This sends the updated pixel color to the hardware.
delayMicroseconds(micro);

 }

}






 void NumberNine(int p){
   pixel[p].setPixelColor(0, pixel[p].Color(0, 200, 0)); // Moderately bright green color.

 for(int i=0;i<16;i++){

    // pixel[p].Color takes RGB values, from 0,0,0 up to 255,255,255
    pixel[p].setPixelColor(i, pixel[p].Color(0, 200, 0)); // Moderately bright green color.
 // This sends the updated pixel color to the hardware.
delayMicroseconds(micro);
 }
   for(int i=24;i<28;i++){

    // pixel[p].Color takes RGB values, from 0,0,0 up to 255,255,255
    pixel[p].setPixelColor(i, pixel[p].Color(0, 200, 0)); // Moderately bright green color.

    pixel[p].show(); // This sends the updated pixel color to the hardware.
delayMicroseconds(micro);

 }
}





void NumberZero(int p){
  pixel[p].setPixelColor(0, pixel[p].Color(0, 200, 0)); // Moderately bright green color.

 for(int i=0;i<12;i++){

    // pixel[p].Color takes RGB values, from 0,0,0 up to 255,255,255
    pixel[p].setPixelColor(i, pixel[p].Color(0, 200, 0)); // Moderately bright green color.

     // This sends the updated pixel color to the hardware.
delayMicroseconds(micro);

 }
   for(int i=16;i<28;i++){

    // pixel[p].Color takes RGB values, from 0,0,0 up to 255,255,255
    pixel[p].setPixelColor(i, pixel[p].Color(0, 200, 0)); // Moderately bright green color.

    pixel[p].show(); // This sends the updated pixel color to the hardware.
delayMicroseconds(micro);

 }
}



void showNumber(int index, int number)
{
switch (number){
case 0: NumberZero(index); break;
case 1: NumberOne(index); break;
case 2: NumberTwo(index); break;
case 3: NumberThree(index); break;
case 4: NumberFour(index); break;
case 5: NumberFive(index); break;
case 6: NumberSix(index); break;
case 7: NumberSeven(index); break;
case 8: NumberEight(index); break;
case 9: NumberNine(index); break;
default: break;}
}


//**************************************KOMUNIKACIA*********************************************//



void sndError() {
  analogWrite(TXControl,255); //Tramsmitting
Serial1.println(3);


Serial1.print(6);

for (int i = 0; i<9; i++) {Serial1.print(0);} 

Serial1.print(0);

int checksum = 0;
checksum = 3;

delay(100);
analogWrite(TXControl,0); //Receiving

  }


/*void rcvMsg(){
analogWrite(TXControl,0);
int blbost;
while (Serial1.available()) {
  incoming.wire = Serial1.read();
  if (incoming.wire == 3){
  incoming.rounds = Serial1.read();
  incoming.pins = Serial1.read();
  incoming.score = Serial1.read();
  } else
  {
   blbost = Serial1.read();
   blbost = Serial1.read();
   blbost = Serial1.read();
    }
  delay(100);
}
  }*/

  void rcvMsg() {
    analogWrite(TXControl,0);
    int msg[5];
    while (Serial1.available()) {
      for (int i =0; i<5; i++) msg[i] = Serial1.read();
      int checksum = msg[0]+msg[1]+msg[2]+msg[3];
      if (msg[0] == 3) 
      { if (checksum == msg[4]) 
      {
        incoming.rounds = msg[1];
        incoming.pins = msg[2];
        incoming.score = msg[3];
        delay(100);
        }
        } else sndError(); 
        
      }
    }



  //********************************************Zobrazovanie udajov na ciselniku****************************************//

  void showRounds(){
  int n = 0;
  if (incoming.rounds < 10)
  { NumberZero(0);
  /*switch (incoming.rounds){
    case 0: NumberZero(1); break;
    case 1: NumberOne(1); break;
    case 2: NumberTwo(1); break;
    case 3: NumberThree(1); break;
    case 4: NumberFour(1); break;
    case 5: NumberFive(1); break;
    case 6: NumberSix(1); break;
    case 7: NumberSeven(1); break;
    case 8: NumberEight(1); break;
    case 9: NumberNine(1); break;
    default: break;}*/
    showNumber(1,incoming.rounds);
  }

  if (incoming.rounds >=10 && incoming.rounds < 20)
  { NumberOne(0);
  /*switch (incoming.rounds - 10){
    case 0: NumberZero(1); break;
    case 1: NumberOne(1); break;
    case 2: NumberTwo(1); break;
    case 3: NumberThree(1); break;
    case 4: NumberFour(1); break;
    case 5: NumberFive(1); break;
    case 6: NumberSix(1); break;
    case 7: NumberSeven(1); break;
    case 8: NumberEight(1); break;
    case 9: NumberNine(1); break;
    default: break;}*/
    showNumber(1,incoming.rounds-10);
  }

  if (incoming.rounds >=20 && incoming.rounds < 30)
  { NumberTwo(0);
  /*switch (incoming.rounds - 20){
    case 0: NumberZero(1); break;
    case 1: NumberOne(1); break;
    case 2: NumberTwo(1); break;
    case 3: NumberThree(1); break;
    case 4: NumberFour(1); break;
    case 5: NumberFive(1); break;
    case 6: NumberSix(1); break;
    case 7: NumberSeven(1); break;
    case 8: NumberEight(1); break;
    case 9: NumberNine(1); break;
    default: break;}*/
    showNumber(1,incoming.rounds-20);
  }

  if (incoming.rounds >=30 && incoming.rounds < 40)
  { NumberThree(0);
  /*switch (incoming.rounds - 30){
    case 0: NumberZero(1); break;
    case 1: NumberOne(1); break;
    case 2: NumberTwo(1); break;
    case 3: NumberThree(1); break;
    case 4: NumberFour(1); break;
    case 5: NumberFive(1); break;
    case 6: NumberSix(1); break;
    case 7: NumberSeven(1); break;
    case 8: NumberEight(1); break;
    case 9: NumberNine(1); break;
    default: break;}*/
    showNumber(1,incoming.rounds-30);
  }
}

void showPins(){
  /*switch (incoming.pins){
    case 0: NumberZero(2); break;
    case 1: NumberOne(2); break;
    case 2: NumberTwo(2); break;
    case 3: NumberThree(2); break;
    case 4: NumberFour(2); break;
    case 5: NumberFive(2); break;
    case 6: NumberSix(2); break;
    case 7: NumberSeven(2); break;
    case 8: NumberEight(2); break;
    case 9: NumberNine(2); break;
    default: break;}*/
    showNumber(2,incoming.pins);
  }

  void showScore(){
int n = incoming.score;

if (n<100) {
  showNumber(3,0);
  if (n<10) { showNumber(4,0); showNumber(5,n);}
  else if (n<20) { n = n-10; showNumber(4,1); showNumber(5,n);}
  else if (n<30) { n = n-20; showNumber(4,2); showNumber(5,n);}
  else if (n<40) { n = n-30; showNumber(4,3); showNumber(5,n);}
  else if (n<50) { n = n-40; showNumber(4,4); showNumber(5,n);}
  else if (n<60) { n = n-50; showNumber(4,5); showNumber(5,n);}
  else if (n<70) { n = n-60; showNumber(4,6); showNumber(5,n);}
  else if (n<80) { n = n-70; showNumber(4,7); showNumber(5,n);}
  else if (n<90) { n = n-80; showNumber(4,8); showNumber(5,n);}
  else if (n>=90) { n = n-90; showNumber(4,9); showNumber(5,n);}
}
else if (n<200) { n = n-100;
  showNumber(3,1);
  if (n<10) { showNumber(4,0); showNumber(5,n);}
  else if (n<20) { n = n-10; showNumber(4,1); showNumber(5,n);}
  else if (n<30) { n = n-20; showNumber(4,2); showNumber(5,n);}
  else if (n<40) { n = n-30; showNumber(4,3); showNumber(5,n);}
  else if (n<50) { n = n-40; showNumber(4,4); showNumber(5,n);}
  else if (n<60) { n = n-50; showNumber(4,5); showNumber(5,n);}
  else if (n<70) { n = n-60; showNumber(4,6); showNumber(5,n);}
  else if (n<80) { n = n-70; showNumber(4,7); showNumber(5,n);}
  else if (n<90) { n = n-80; showNumber(4,8); showNumber(5,n);}
  else if (n>=90) { n = n-90; showNumber(4,9); showNumber(5,n);}
}

else if (n<300) { n = n-200;
  showNumber(3,2);
  if (n<10) { showNumber(4,0); showNumber(5,n);}
  else if (n<20) { n = n-10; showNumber(4,1); showNumber(5,n);}
  else if (n<30) { n = n-20; showNumber(4,2); showNumber(5,n);}
  else if (n<40) { n = n-30; showNumber(4,3); showNumber(5,n);}
  else if (n<50) { n = n-40; showNumber(4,4); showNumber(5,n);}
  else if (n<60) { n = n-50; showNumber(4,5); showNumber(5,n);}
  else if (n<70) { n = n-60; showNumber(4,6); showNumber(5,n);}
  else if (n<80) { n = n-70; showNumber(4,7); showNumber(5,n);}
  else if (n<90) { n = n-80; showNumber(4,8); showNumber(5,n);}
  else if (n>=90) { n = n-90; showNumber(4,9); showNumber(5,n);}
}
else if (n<400) { n = n-300;
  showNumber(3,3);
  if (n<10) { showNumber(4,0); showNumber(5,n);}
  else if (n<20) { n = n-10; showNumber(4,1); showNumber(5,n);}
  else if (n<30) { n = n-20; showNumber(4,2); showNumber(5,n);}
  else if (n<40) { n = n-30; showNumber(4,3); showNumber(5,n);}
  else if (n<50) { n = n-40; showNumber(4,4); showNumber(5,n);}
  else if (n<60) { n = n-50; showNumber(4,5); showNumber(5,n);}
  else if (n<70) { n = n-60; showNumber(4,6); showNumber(5,n);}
  else if (n<80) { n = n-70; showNumber(4,7); showNumber(5,n);}
  else if (n<90) { n = n-80; showNumber(4,8); showNumber(5,n);}
  else if (n>=90) { n = n-90; showNumber(4,9); showNumber(5,n);}
}
else if (n<500) { n = n-400;
  showNumber(3,4);
  if (n<10) { showNumber(4,0); showNumber(5,n);}
  else if (n<20) { n = n-10; showNumber(4,1); showNumber(5,n);}
  else if (n<30) { n = n-20; showNumber(4,2); showNumber(5,n);}
  else if (n<40) { n = n-30; showNumber(4,3); showNumber(5,n);}
  else if (n<50) { n = n-40; showNumber(4,4); showNumber(5,n);}
  else if (n<60) { n = n-50; showNumber(4,5); showNumber(5,n);}
  else if (n<70) { n = n-60; showNumber(4,6); showNumber(5,n);}
  else if (n<80) { n = n-70; showNumber(4,7); showNumber(5,n);}
  else if (n<90) { n = n-80; showNumber(4,8); showNumber(5,n);}
  else if (n>=90) { n = n-90; showNumber(4,9); showNumber(5,n);}
}
else if (n<600) { n = n-500;
  showNumber(3,5);
  if (n<10) { showNumber(4,0); showNumber(5,n);}
  else if (n<20) { n = n-10; showNumber(4,1); showNumber(5,n);}
  else if (n<30) { n = n-20; showNumber(4,2); showNumber(5,n);}
  else if (n<40) { n = n-30; showNumber(4,3); showNumber(5,n);}
  else if (n<50) { n = n-40; showNumber(4,4); showNumber(5,n);}
  else if (n<60) { n = n-50; showNumber(4,5); showNumber(5,n);}
  else if (n<70) { n = n-60; showNumber(4,6); showNumber(5,n);}
  else if (n<80) { n = n-70; showNumber(4,7); showNumber(5,n);}
  else if (n<90) { n = n-80; showNumber(4,8); showNumber(5,n);}
  else if (n>=90) { n = n-90; showNumber(4,9); showNumber(5,n);}
}
else if (n<700) { n = n-600;
  showNumber(3,6);
  if (n<10) { showNumber(4,0); showNumber(5,n);}
  else if (n<20) { n = n-10; showNumber(4,1); showNumber(5,n);}
  else if (n<30) { n = n-20; showNumber(4,2); showNumber(5,n);}
  else if (n<40) { n = n-30; showNumber(4,3); showNumber(5,n);}
  else if (n<50) { n = n-40; showNumber(4,4); showNumber(5,n);}
  else if (n<60) { n = n-50; showNumber(4,5); showNumber(5,n);}
  else if (n<70) { n = n-60; showNumber(4,6); showNumber(5,n);}
  else if (n<80) { n = n-70; showNumber(4,7); showNumber(5,n);}
  else if (n<90) { n = n-80; showNumber(4,8); showNumber(5,n);}
  else if (n>=90) { n = n-90; showNumber(4,9); showNumber(5,n);}
}
else if (n<800) { n = n-700;
  showNumber(3,7);
  if (n<10) { showNumber(4,0); showNumber(5,n);}
  else if (n<20) { n = n-10; showNumber(4,1); showNumber(5,n);}
  else if (n<30) { n = n-20; showNumber(4,2); showNumber(5,n);}
  else if (n<40) { n = n-30; showNumber(4,3); showNumber(5,n);}
  else if (n<50) { n = n-40; showNumber(4,4); showNumber(5,n);}
  else if (n<60) { n = n-50; showNumber(4,5); showNumber(5,n);}
  else if (n<70) { n = n-60; showNumber(4,6); showNumber(5,n);}
  else if (n<80) { n = n-70; showNumber(4,7); showNumber(5,n);}
  else if (n<90) { n = n-80; showNumber(4,8); showNumber(5,n);}
  else if (n>=90) { n = n-90; showNumber(4,9); showNumber(5,n);}
}

else if (n<900) { n = n-800;
  showNumber(3,8);
  if (n<10) { showNumber(4,0); showNumber(5,n);}
  else if (n<20) { n = n-10; showNumber(4,1); showNumber(5,n);}
  else if (n<30) { n = n-20; showNumber(4,2); showNumber(5,n);}
  else if (n<40) { n = n-30; showNumber(4,3); showNumber(5,n);}
  else if (n<50) { n = n-40; showNumber(4,4); showNumber(5,n);}
  else if (n<60) { n = n-50; showNumber(4,5); showNumber(5,n);}
  else if (n<70) { n = n-60; showNumber(4,6); showNumber(5,n);}
  else if (n<80) { n = n-70; showNumber(4,7); showNumber(5,n);}
  else if (n<90) { n = n-80; showNumber(4,8); showNumber(5,n);}
  else if (n>=90) { n = n-90; showNumber(4,9); showNumber(5,n);}
}

else if (n>=900) { n = n-900;
  showNumber(3,9);
  if (n<10) { showNumber(4,0); showNumber(5,n);}
  else if (n<20) { n = n-10; showNumber(4,1); showNumber(5,n);}
  else if (n<30) { n = n-20; showNumber(4,2); showNumber(5,n);}
  else if (n<40) { n = n-30; showNumber(4,3); showNumber(5,n);}
  else if (n<50) { n = n-40; showNumber(4,4); showNumber(5,n);}
  else if (n<60) { n = n-50; showNumber(4,5); showNumber(5,n);}
  else if (n<70) { n = n-60; showNumber(4,6); showNumber(5,n);}
  else if (n<80) { n = n-70; showNumber(4,7); showNumber(5,n);}
  else if (n<90) { n = n-80; showNumber(4,8); showNumber(5,n);}
  else if (n>=90) { n = n-90; showNumber(4,9); showNumber(5,n);}
}

  }
  void loop()
  {
    analogWrite(TXControl, 0);
  delay(1000);
   for (int i =0; i<6 ; i++) Nuluj(i);
  Serial.println("Zacina program ciselnika");
   for (int i =0; i<6 ; i++){
  delay(50);
  Nuluj(i);
  NumberZero(i);
  delay(50);
  Nuluj(i);
  NumberOne(i);
  delay(50);
  Nuluj(i);
  NumberTwo(i);
  delay(50);
  Nuluj(i);
  NumberThree(i);
  delay(50);
  Nuluj(i);
  NumberFour(i);
  delay(50);
  Nuluj(i);
  NumberFive(i);
  delay(50);
  Nuluj(i);
  NumberSix(i);
  delay(50);
  Nuluj(i);
  NumberSeven(i);
  delay(50);
  Nuluj(i);
  NumberEight(i);
  delay(50);
  Nuluj(i);
  NumberNine(i);
   }

/*
    for (int i =0; i<6 ; i++) Nuluj(i);
    for (int i =0; i<6 ; i++) Nuluj(i);
    delay(100);*/
    
    for (int i =0; i<6; i++) { Nuluj(i); delay(10); NumberZero(i); }
Serial.println("prebehla kontrola ciselnika");
  while(true) {
    if (Serial1.available()) {
      rcvMsg();
      Serial.println("Nieco Prislo: ");
      //if (incoming.rounds == 24) {
       /*delay(1000);
       for (int i =0; i<6 ; i++) Nuluj(i);
       for (int i =0; i<6 ; i++){
      delay(50);
      Nuluj(i);
      NumberZero(i);
      delay(50);
      Nuluj(i);
      NumberOne(i);
      delay(50);
      Nuluj(i);
      NumberTwo(i);
      delay(50);
      Nuluj(i);
      NumberThree(i);
      delay(50);
      Nuluj(i);
      NumberFour(i);
      delay(50);
      Nuluj(i);
      NumberFive(i);
      delay(50);
      Nuluj(i);
      NumberSix(i);
      delay(50);
      Nuluj(i);
      NumberSeven(i);
      delay(50);
      Nuluj(i);
      NumberEight(i);
      delay(50);
      Nuluj(i);
      NumberNine(i);
    }*/
      // }
    Serial.println(incoming.rounds);
    Serial.println(incoming.pins);
    Serial.println(incoming.score);
    
    
    
    if (lastRounds != incoming.rounds) {for (int i =0; i<2 ; i++) Nuluj(i); showRounds();}
    if (lastPins != incoming.pins) { Nuluj(2); showPins(); }
    if (lastScore != incoming.score) for (int i =3; i<6 ; i++) Nuluj(i); showScore();
    
    lastRounds = incoming.rounds;
    lastPins = incoming.pins;
    lastScore = incoming.score;
  }
    }

  }

    © 2019 GitHub, Inc.
    Terms
    Privacy
    Security
    Status
    Help

    Contact GitHub
    Pricing
    API
    Training
    Blog
    About

