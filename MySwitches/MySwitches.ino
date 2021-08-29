//www.elegoo.com
//2016.12.08

int redPin = 5;
int grnPin = 6;
int bluPin = 7;
int buttonApin = 9;
int buttonBpin = 8;

unsigned int counter = 0;

int stateA = 0;
int stateB = 0;
int lastA = 0;
int lastB = 0;

// ledState array: R, G, B
int ledState[3] = {0, 0, 0};
int redState = 0;
int grnState = 0;
int bluState = 0;


void ledUpdate() {
  digitalWrite(redPin, ledState[2]);
  digitalWrite(grnPin, ledState[1]);
  digitalWrite(bluPin, ledState[0]);
}

void ledSet(int value) {
  int newState[3] = {0, 0, 0};
  updateState(value, 3, newState);
  for (int i = 0; i<3; i++) {
    ledState[i] = newState[i];
  }
  Serial.println();
}

void updateState(int value, int length, int state[3]) {
  length -= 1;
  int div = value / 2;
  if (div != 0) {
    updateState(div, length, state);
  }
  state[length] = value % 2;
}

int buttonPress(int button, int last, int value) {
  int buttonState = digitalRead(button);
  if (buttonState != last) {
    if (buttonState == HIGH) {
      counter = counter + value;
      counter %= 8;
      ledSet(counter);
      ledUpdate();
    }
    delay(100);
  }
  return buttonState;
}

void setup() {
  // Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(grnPin, OUTPUT);
  pinMode(bluPin, OUTPUT);
  pinMode(buttonApin, INPUT_PULLUP);
  pinMode(buttonBpin, INPUT_PULLUP);
  lastA = digitalRead(buttonApin);
  lastB = digitalRead(buttonBpin);
  ledUpdate();
}

void loop() { 
  lastA = buttonPress(buttonApin, lastA, 1);
  lastB = buttonPress(buttonBpin, lastB, -1);
}
