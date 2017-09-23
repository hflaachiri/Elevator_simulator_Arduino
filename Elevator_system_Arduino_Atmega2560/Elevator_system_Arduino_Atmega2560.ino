/*
  LiquidCrystal Library - Elevator Door System

 This project is for displayin the floor numbers and the statut of an elevator to the LCD
 This project use Arduino Nano
 
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 9
 * LCD D5 pin to digital pin 8
 * LCD D6 pin to digital pin 7
 * LCD D7 pin to digital pin 6
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
/* pin2 and pin3 are used for the currentFloorNumber
 *  pin3pin2
 *  00 --> floor number 0
 *  01 --> floor number 1
 *  10 --> floor number 2
 *  11 --> floor number -1
 *  
 *  pin5 and pin4 are used for the status of the elevator 
 *  pin5pin4 == 00 --> Elevator down
 *  pin5pin4 == 01 --> elevator up
 *  pin5pin4 == 11 --> elevator Stop
 */
const int  pin2=10, pin3=11, pin4 = 12 , pin5 = 13;

byte up[8] = {
  B00000,
  B00100,
  B01110,
  B11111,
  B11111,
  B00100,
  B00100,
};
byte down[8] = {
  B00100,
  B00100,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000,
};

/*
 * Initialy the elevator is in the floor number 0
 */
int currentFloorNumber = 0, minFloorNumber = -1, maxFloorNumber = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.createChar(0, down);
  lcd.createChar(1, up);
  pinMode(pin2, INPUT);
  pinMode(pin3, INPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Elevator Syetem");

}
void printFloorNumber(int pin3Val, int pin2Val){
  if( pin3Val == 0){
    if(pin2Val == 0){// pin3pin2 == 00
      currentFloorNumber = 0;
    }
    else{// pin3pin2 == 01
      currentFloorNumber = 1;
    }
  }
  else{
    if(pin2Val == 0){// pin3pin2 == 10
      currentFloorNumber = 2;
    }
    else{// pin3pin2 == 11
      currentFloorNumber = -1;
    }
  }
  lcd.setCursor(0, 1);
  lcd.print("Floor Number: ");
  lcd.print(currentFloorNumber);

}
void printElevatorStatus(int pin5Val, int pin4Val){
  lcd.setCursor(12, 0);
  if(pin5Val == 1 && pin4Val == 1){// The elevator is Stoped
    lcd.print("STOP");
  }
  else{
    for(int i=0 ; i < 3 ; i++){
      lcd.print("    ");
      delay(500);
      lcd.setCursor(15, 0);
      if(pin5Val == 0 && pin4Val == 1){// The elevator is Stoped
        lcd.print(char(0));
      }
      else{
        lcd.print(char(1));
      }
      
    }
  } 
}
void loop() {

  int pin2Value = digitalRead(pin2);
  int pin3Value = digitalRead(pin3);
  int pin4Value = digitalRead(pin4);
  int pin5Value = digitalRead(pin5);
  lcd.clear();
  printFloorNumber(pin3Value, pin2Value);
  printElevatorStatus(pin5Value, pin4Value);
}
