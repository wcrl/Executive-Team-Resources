const int latchClock = 4; // Arduino digital pin connected to the shift register latch clock
const int shiftClock = 3; // Arduino digital pin connected to the shift register shift clock
const int serialData = 2; // Arduino digital pin connected to the shift register serial data input
const int numLEDs = 8;    // number of LEDs connected to the shift register
int currentLED = 0;       // current LED that is lit

void setup() {
  // set pin modes
  pinMode(latchClock, OUTPUT);
  pinMode(shiftClock, OUTPUT);
  pinMode(serialData, OUTPUT);

  // initialize all LEDs to be off
  for (int i = 0; i < numLEDs; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }

  // clear the shift register
  clearShiftRegister();
}

void loop() {
  // shift a single "1" bit through the shift register to the next position
  digitalWrite(latchClock, LOW);
  shiftOut(serialData, shiftClock, MSBFIRST, 1 << currentLED);
  digitalWrite(latchClock, HIGH);

  // turn off the current LED
  digitalWrite(currentLED, LOW);

  // move to the next LED
  currentLED = (currentLED + 1) % numLEDs;

  // turn on the next LED
  digitalWrite(currentLED, HIGH);

  // pause for a short period of time
  delay(300);
}

void clearShiftRegister() {
  // clear the shift register by shifting in 0s
  digitalWrite(latchClock, LOW);
  for (int i = 0; i < numLEDs; i++) {
    shiftOut(serialData, shiftClock, MSBFIRST, 0);
  }
  digitalWrite(latchClock, HIGH);
}

