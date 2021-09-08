//www.elegoo.com
//2016.12.08

// # Constants #
const int LEDSIZE = 3;
const int maxval = pow(2, LEDSIZE);
byte sevenSegDigits[8] = { B11111100,  // = 0
                              B01100000,  // = 1
                              B11011010,  // = 2
                              B11110010,  // = 3
                              B01100110,  // = 4
                              B10110110,  // = 5
                              B10111110,  // = 6
                              B11100000  // = 7
};

// Define Hardware
int redPin = 5;
int grnPin = 6;
int bluPin = 7;
int buttonApin = 9;
int buttonBpin = 8;
int dataPin = 11; // DS of 74HC595
int latchPin = 12; // ST_CP of 74HC595
int clockPin = 13; // SH_CP of 74HC595

// Define System States
unsigned int counter = 0;
// - LED States: R, G, B
int ledState[LEDSIZE] = {0, 0, 0};
// - Button States
int stateA = 0;
int stateB = 0;
int lastA = 0;
int lastB = 0;

// # Functions #

// Send current state to LED hardware
void ledUpdate() {
  digitalWrite(redPin, ledState[2]);
  digitalWrite(grnPin, ledState[1]);
  digitalWrite(bluPin, ledState[0]);
}

// Set LED states to given value
void ledSet(int value) {
  int newState[LEDSIZE] = {0, 0, 0};
  updateState(value, LEDSIZE, newState);
  for (int i = 0; i<LEDSIZE; i++) {
    ledState[i] = newState[i];
  }
  Serial.println();
}

// Break int into bits (Requires null array)
void updateState(int value, int length, int state[LEDSIZE]) {
  length -= 1;
  int div = value / 2;
  if (div != 0) {
    updateState(div, length, state);
  }
  state[length] = value % 2;
}

// Catch state change for button
int buttonPress(int button, int last, int value) {
  int buttonState = digitalRead(button);
  if (buttonState != last) {
    if (buttonState == HIGH) {
      counter = counter + value;
      counter %= maxval;
      ledSet(counter);
      sevenSegWrite(counter);
      ledUpdate();
    }
    delay(100);
  }
  return buttonState;
}

// Write value to digital segment display
void sevenSegWrite(int digit) {
  // set the latchPin to low potential, before sending data
  digitalWrite(latchPin, LOW);
     
  // the original data (bit pattern)
  shiftOut(dataPin, clockPin, LSBFIRST, sevenSegDigits[digit]);  
 
  // set the latchPin to high potential, after sending data
  digitalWrite(latchPin, HIGH);
}

// # Arduino #

// Init
void setup() {
  // Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(grnPin, OUTPUT);
  pinMode(bluPin, OUTPUT);
  pinMode(buttonApin, INPUT_PULLUP);
  pinMode(buttonBpin, INPUT_PULLUP);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  lastA = digitalRead(buttonApin);
  lastB = digitalRead(buttonBpin);
  ledSet(counter);
  ledUpdate();
  sevenSegWrite(counter);
}

// Main Loop
void loop() { 
  lastA = buttonPress(buttonApin, lastA, 1);
  lastB = buttonPress(buttonBpin, lastB, -1);
}
