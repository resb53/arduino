//www.elegoo.com
//2016.12.08

int redPin = 5;
int grnPin = 6;
int bluPin = 7;
int buttonApin = 9;
int buttonBpin = 8;

int counter = 0;

int stateA = 0;
int stateB = 0;
int lastA = 0;
int lastB = 0;

int redState = LOW;
int grnState = LOW;
int bluState = LOW;

void ledUpdate() {
  digitalWrite(redPin, redState);
  digitalWrite(grnPin, grnState);
  digitalWrite(bluPin, bluState);
}

void ledReport(int value) { 
  if ((value & 1) == 0) {
    redState = LOW;
  }
  else {
    redState = HIGH;
  }

  if ((value & 2) == 0) {
    grnState = LOW;
  }
  else {
    grnState = HIGH;
  }

  if ((value & 4) == 0) {
    bluState = LOW;
  }
  else {
    bluState = HIGH;
  }

  ledUpdate();
}

void setup() {
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
  stateA = digitalRead(buttonApin);
  stateB = digitalRead(buttonBpin);
  
  if (stateA != lastA) {
    if (stateA == HIGH) { 
      counter += 1;
      counter %= 8;
    }
    delay(50);
  }
  if (stateB != lastB) {
    if (stateB == HIGH) {
      counter -= 1;
      counter %= 8;
    }
    delay(50);
  }
  lastA = stateA;
  lastB = stateB;
  ledReport(counter);
}
