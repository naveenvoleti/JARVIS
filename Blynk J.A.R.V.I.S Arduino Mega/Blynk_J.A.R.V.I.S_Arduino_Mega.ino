#include <Keypad.h>
#include<LiquidCrystal.h>
#include<EEPROM.h>
#include <Wire.h>
#include "FPS_GT511C3.h"
#include "SoftwareSerial.h"
#include <IRremote.h>
//#include <LM35.h>
#define sw 7
LiquidCrystal lcd(49, 48, 52, 53, 50, 51);
FPS_GT511C3 fps(10, 11); // (Arduino SS_RX = pin 10, Arduino SS_TX = pin 11)

char passcode[4];
char pass0[4], pass1[4];
int i = 0;
int s = 0;
char customKey = 0;
const byte ROWS = 4; //four rows
const byte COLS = 3; //four columns
int scanned = false;
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {A12, A13, A14, A15}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {A9, A10, A11}; //connect to the column pinouts of the keypad
//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
IRsend irsend;
//LM35 sensor(0);
void setup()
{
  delay(100);
  fps.Open();         //send serial command to initialize fps
  fps.SetLED(true);
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(sw, INPUT_PULLUP);
  //pinMode(m11, OUTPUT);
  //pinMode(m12, OUTPUT);
  lcd.clear();
  lcd.print("Enter Ur Passkey:");
  Serial.print("Enter Ur Passkey:");
  lcd.setCursor(0, 1);
  for (int j = 0; j < 4; j++)
    EEPROM.write(j, j + 49);
  for (int j = 0; j < 4; j++)
    pass0[j] = EEPROM.read(j);
  /*Serial.print(pass[0]);
    Serial.print(pass[1]);
    Serial.print(pass[2]);
    Serial.print(pass[3]);*/
  fps.SetLED(false);
  fps.Close();
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  
}

void loop()
{
  if (digitalRead(sw) == 1) {
    //fpsRead();
    customKey = customKeypad.getKey();
    if (customKey == '#') {
      customKey = 0;
      change();
    }
    if (customKey == '*') {
      s = 0;
      customKey = 0;
      scanned = false;
      //fpsEnroll();
      fpsRead();
    }
    getPassKey();
    //fpsRead();
    //Serial.println("running");
  }
}


void receiveEvent(int howMany) {
  int port = Wire.read();
  int value = Wire.read();
  char type = Wire.read();
  char mode = Wire.read();
  Serial.print(port);
  Serial.print(value);
  Serial.print(type);
  Serial.print(mode);
  if (mode == 'W') {
    pinMode(port, OUTPUT);
    if (type == 'A') {
      analogWrite(port, value);
    }
    else if (type == 'D') {
      digitalWrite(port, value);
    }
  }
  else if (mode == 'R') {
    
    if (type == 'A') {
      pinMode('A'+port, INPUT);
      int val = analogRead('A'+port);
      Wire.beginTransmission(42);
      Wire.write(val);
      Wire.endTransmission();
      Serial.print(val);
    }
    else if (type == 'D') {
      pinMode(port, INPUT);
      int val = digitalRead(port);
      Wire.beginTransmission(42);
      Wire.write(val);
      Wire.endTransmission();
      Serial.print(val);
    }
  }

}

void remote(int code){
  switch(code){
    case 0:    //
      Serial.println("Tv on");
      irSend(0x80BF1EE1);
      break;
    case 1:    //
      Serial.println("Tv off");
      irSend(0x80BF1EE1);
      break;
    case 2:    //
      Serial.println("next channel");
      irSend(0x80BF53AC);
      break;
    case 3:    //
      Serial.println("previous channel");
      irSend(0x80BF4BB4);
      break;
    case 4:    //
      Serial.println("mute");
      irSend(0x80BF33CC);
      break;
    case 5:    // 
      Serial.println("volume Up");
      irSend(0x80BF837C);
      break;
    case 6:    //
      Serial.println("volume Down");
      irSend(0x80BF9966);
      break;
  }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
}
