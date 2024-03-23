//Pin connected to SH_CP of 74HC595
int clockPinR = 2;
//Pin connected to ST_CP of 74HC595
int latchPinR = 3;
////Pin connected to DS of 74HC595
int dataPinR = 4;


//holder for information you're going to pass to shifting function
byte data = 0;


//Pin connected to SH_CP of 74HC595
int clockPinB = 5;
//Pin connected to ST_CP of 74HC595
int latchPinB = 6;
////Pin connected to DS of 74HC595
int dataPinB = 7;



int bluePin = A0;
int redPin = A1;
int greenPin = A2;
int button1pin = 9;
int button2pin = 10;
int buttonXpin = 11;
int flashBlueCount = 0;
int flashRedCount = 0;



void setup() {
//set pins to output because they are addressed in the main loop
  pinMode(latchPinR, OUTPUT);

  pinMode(latchPinB, OUTPUT);



  pinMode(bluePin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(button1pin, INPUT_PULLUP); 
  pinMode(button2pin, INPUT_PULLUP); 
  pinMode(buttonXpin, INPUT_PULLUP);  

  analogWrite(bluePin, 255);
  analogWrite(redPin, 255);
  analogWrite(greenPin, 255);


}
void loop() {
//function that blinks all the LEDs
//gets passed the number of blinks and the pause time

// light each pin one by one using a function A
for (int j = 0; j < 8; j++) {
//ground latchPin and hold low for as long as you are transmitting
digitalWrite(latchPinR, 0);
digitalWrite(latchPinB, 0);

lightShiftPinB(j);

digitalWrite(latchPinR, 1);
digitalWrite(latchPinB, 1);

delay(50);
}




{
  if (digitalRead(button1pin) == LOW && flashBlueCount == 0)
  {
    // Flash BLUE
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    delay(3000);
    
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, HIGH);
    // Set the flash count to 1 to indicate that the LED has been flashed
    flashBlueCount = 1;
  }
  if (digitalRead(button2pin) == LOW && flashRedCount == 0)
  {
    // Flash Red
    digitalWrite(bluePin, LOW);
    digitalWrite(greenPin, LOW);
    delay(3000);
    
    digitalWrite(bluePin, HIGH);
    digitalWrite(greenPin, HIGH);

    flashRedCount = 1;
  }
  // Check if the reset button has been pressed
  if (digitalRead(buttonXpin) == LOW)
  {
    // Reset the flash count to 0 to allow the LED to be flashed again
    flashRedCount = 0;
    flashBlueCount = 0;
  }
}
}
//This function uses bitwise math to move the pins up
void lightShiftPinA(int p) {
//defines a local variable
int pin;
//this is line uses a bitwise operator
//shifting a bit left using << is the same
//as multiplying the decimal number by two.
pin = 1<< p;
//move 'em out
shiftOutR(dataPinR, clockPinR, pin);
shiftOutB(dataPinB, clockPinB, pin);

}
//This function uses that fact that each bit in a byte
//is 2 times greater than the one before it to
//shift the bits higher
void lightShiftPinB(int p) {
//defines a local variable
int pin;
//start with the pin = 1 so that if 0 is passed to this
//function pin 0 will light.
pin = 1;
for (int x = 0; x < p; x++) {
pin = pin * 2;
}
//move 'em out
shiftOutR(dataPinR, clockPinR, pin);
shiftOutB(dataPinB, clockPinB, pin);
}




//Blue LEDs worked when code was matched up to this point





// the heart of the program
void shiftOutR(int myDataPinR, int myClockPinR, byte myDataOut) {
// This shifts 8 bits out MSB first,
//on the rising edge of the clock,
//clock idles low
//internal function setup
int i=0;
int pinState;
pinMode(myClockPinR, OUTPUT);
pinMode(myDataPinR, OUTPUT);
//clear everything out just in case to
//prepare shift register for bit shifting
digitalWrite(myDataPinR, 0);
digitalWrite(myClockPinR, 0);
//for each bit in the byte myDataOut&#xFFFD;
//NOTICE THAT WE ARE COUNTING DOWN in our for loop
//This means that %00000001 or "1" will go through such
//that it will be pin Q0 that lights.
for (i=7; i>=0; i--)  {
digitalWrite(myClockPinR, 0);
//if the value passed to myDataOut and a bitmask result
// true then... so if we are at i=6 and our value is
// %11010100 it would the code compares it to %01000000
// and proceeds to set pinState to 1.
if ( myDataOut & (1<<i) ) {
pinState= 1;
}
else {
pinState= 0;
}
//Sets the pin to HIGH or LOW depending on pinState
digitalWrite(myDataPinR, pinState);
//register shifts bits on upstroke of clock pin
digitalWrite(myClockPinR, 1);
//zero the data pin after shift to prevent bleed through
digitalWrite(myDataPinR, 0);
}
//stop shifting
digitalWrite(myClockPinR, 0);
}
//blinks both registers based on the number of times you want to

//Blue Copy
void shiftOutB(int myDataPinB, int myClockPinB, byte myDataOut) {
// This shifts 8 bits out MSB first,
//on the rising edge of the clock,
//clock idles low
//internal function setup
int i=0;
int pinState;
pinMode(myClockPinB, OUTPUT);
pinMode(myDataPinB, OUTPUT);
//clear everything out just in case to
//prepare shift register for bit shifting
digitalWrite(myDataPinB, 0);
digitalWrite(myClockPinB, 0);
//for each bit in the byte myDataOut&#xFFFD;
//NOTICE THAT WE ARE COUNTING DOWN in our for loop
//This means that %00000001 or "1" will go through such
//that it will be pin Q0 that lights.
for (i=7; i>=0; i--)  {
digitalWrite(myClockPinB, 0);
//if the value passed to myDataOut and a bitmask result
// true then... so if we are at i=6 and our value is
// %11010100 it would the code compares it to %01000000
// and proceeds to set pinState to 1.
if ( myDataOut & (1<<i) ) {
pinState= 1;
}
else {
pinState= 0;
}
//Sets the pin to HIGH or LOW depending on pinState
digitalWrite(myDataPinB, pinState);
//register shifts bits on upstroke of clock pin
digitalWrite(myClockPinB, 1);
//zero the data pin after shift to prevent bleed through
digitalWrite(myDataPinB, 0);
}
//stop shifting
digitalWrite(myClockPinB, 0);
}
//blinks both registers based on the number of times you want to
