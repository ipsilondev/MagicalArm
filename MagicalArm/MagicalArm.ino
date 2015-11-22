#include "Keypad.h"
#include <SoftwareSerial.h>


const byte rows = 4; //four rows
const byte cols = 8; //eight columns
const char SPECIAL_UPPERCASE[] = "UPX";
const char SPECIAL_ERASE[] = "ERX";
const char SPECIAL_SWITCH[] = "SWX";
const char SPECIAL_SPACE[] = "SPX";
const char SPECIAL_ENTER[] = "ENX";
const char SPECIAL_UP[] = "UPA";
const char SPECIAL_LEFT[] = "LEA";
const char SPECIAL_RIGHT[] = "RIA";
const char SPECIAL_DOWN[] = "DOA";
boolean switchState = false;
boolean uppercase = false;
int lastIndexKey[2];
int redPin = 7;
int greenPin = 8;
int bluePin = 12;
 
//uncomment this line if using a Common Anode LED
#define COMMON_ANODE
char keys[rows][cols] = {
  {'1','2','3','4','5','6','7','8'},
  {'9','0','A','B','C','D','E','F'},
  {'G','v','H','I','J','K','L','M'},
  {'N','O','P','Q','R','S','T','U'}
};

/*char keys[rows][cols] = {
  {'1','2','3','4'},
  {'9','0','A','B'},
  {'G','E','H','I'},
  {'N','O','P','Q'}
};*/

const char* firstSetKeys[rows][cols] = {
  {"q","w","e","r","t","y","u","i"},
  {"o","p","a","s","d","f","g","h"},
  {SPECIAL_UPPERCASE,"j","k","l","z","x","c",SPECIAL_ERASE},
  {SPECIAL_SWITCH,"v","b","n","m",",",SPECIAL_SPACE,SPECIAL_ENTER}
};


const char* firstSetKeysUppercase[rows][cols] = {
  {"Q","W","E","R","T","Y","U","I"},
  {"O","P","A","S","D","F","G","H"},
  {SPECIAL_UPPERCASE,"J","K","L","Z","X","C",SPECIAL_ERASE},
  {SPECIAL_SWITCH,"V","B","N","M",",",SPECIAL_SPACE,SPECIAL_ENTER}
};

const char* secondSetKeys[rows][cols] = {
  {"1","2","3","4","5","6","7","8"},
  {"9","0","@","&","%","=","+","-"},
  {SPECIAL_UPPERCASE,"*","/","(",")","!","?",SPECIAL_ERASE},
  {SPECIAL_SWITCH,"'","?","\"",":",".",SPECIAL_SPACE,SPECIAL_ENTER}
};


const char* thirdSetKeys[rows][cols] = {
  {"[","]",SPECIAL_UP,"{","}","<",">","|"},
  {"\\",SPECIAL_LEFT,SPECIAL_DOWN,SPECIAL_RIGHT,"$","@","+","-"},
  {SPECIAL_UPPERCASE,"*","/","(",")","!","?",SPECIAL_ERASE},
  {SPECIAL_SWITCH,"'","?","\"",":",";",SPECIAL_SPACE,SPECIAL_ENTER}
};

byte rowPins[rows] = {2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[cols] = {6,9,10,11,A0,A1,A4,A5}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );


void setup()
{
  pinMode(bluePin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(redPin,OUTPUT);
  
  Serial.begin(9600);  // Begin the serial monitor at 9600bps
  delay(100);  // Short delay, wait for the Mate to send back CMD
  
}

void loop()
{
 char keyPressed = keypad.getKey();

  if (keyPressed != NO_KEY){
    if(keypad.getState() == PRESSED){
switch(keyPressed){
   case 'G':
   uppercaseSwitch();
   break;
   case 'M':
   //Serial.write(0x2A);
   Serial.write(0x08);   
   break;
   case 'N':
   switchKeySet();
   break;
   case 'T':
   Serial.write(0x20);
   break;
   case 'U':
//   Serial.write(0x28);
   Serial.write(0x0A);
   break;
   default:
   if(switchState==true && uppercase==true){     
    switch(keyPressed){
      case '3':
//      Serial.write(0x52);
      Serial.write(0x0E);      
      break;
      case '0':
      //Serial.write(0x50);
      Serial.write(0x0B);     
      break;
      case 'A':
//      Serial.write(0x51);
      Serial.write(0x0C);
      break;
      case 'B':
//      Serial.write(0x4F);
      Serial.write(0x07);      
      break;
      default:
      getIndexOfKey(keyPressed);
      Serial.print(thirdSetKeys[lastIndexKey[0]][lastIndexKey[1]]);      
      break;
    }
   }else if(switchState==true){
      getIndexOfKey(keyPressed);
      Serial.print(secondSetKeys[lastIndexKey[0]][lastIndexKey[1]]);        
   }else if(uppercase==true){
      getIndexOfKey(keyPressed);
      Serial.print(firstSetKeysUppercase[lastIndexKey[0]][lastIndexKey[1]]);                
   }else{
      getIndexOfKey(keyPressed);
      Serial.print(firstSetKeys[lastIndexKey[0]][lastIndexKey[1]]);                  
   }
   break;


  }


      
  

    }
  }
  delay(100);
}

void getIndexOfKey(char k){
for(int i = 0; i<rows;i++){
for(int g = 0; g<cols;g++){
  if(keys[i][g]==k){
   lastIndexKey[0] = i;  
   lastIndexKey[1] = g;  
  }
}
}  
}


void switchKeySet(){
  if(switchState==true){
     switchState=false;
    digitalWrite(bluePin,LOW);
    digitalWrite(greenPin,LOW);
     if(uppercase==true){
     uppercaseSwitch();
     }
   }else{
    digitalWrite(bluePin,HIGH);
    digitalWrite(greenPin,LOW);     
    switchState=true;   
    if(uppercase==true){
     uppercaseSwitch();
     }  
   }
  
}
void uppercaseSwitch(){
  if(uppercase==true){
     uppercase=false;
     digitalWrite(redPin,LOW);
     if(switchState==true){
    digitalWrite(bluePin,HIGH);
    digitalWrite(greenPin,LOW);                   
     }
   }else{
     uppercase=true;     
     digitalWrite(redPin,HIGH);
     if(switchState==true){
    digitalWrite(redPin,LOW);
    digitalWrite(bluePin,LOW);
    digitalWrite(greenPin,HIGH);            
     }
   }
}

void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}
  
