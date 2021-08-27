//www.elegoo.com
//2016.12.08

int redPin = 5;
int grnPin = 6;
int bluPin = 7;
int buttonApin = 9;
int buttonBpin = 8;

int counter = 0;
int lastA = 0;
int lastB = 0;

int redState = LOW;
int grnState = LOW;
int bluState = LOW;

void ledUpdate()
{
  digitalWrite(redPin, redState);
  digitalWrite(grnPin, grnState);
  digitalWrite(bluPin, bluState);
}

void ledReport(int value)
{ 
  if ((value & 1) == 0)
  {
    redState = LOW;
  }
  else
  {
    redState = HIGH;
  }

  if ((value & 2) == 0)
  {
    grnState = LOW;
  }
  else
  {
    grnState = HIGH;
  }

  if ((value & 4) == 0)
  {
    bluState = LOW;
  }
  else
  {
    bluState = HIGH;
  }

  ledUpdate();
}

void setup() 
{
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(grnPin, OUTPUT);
  pinMode(bluPin, OUTPUT);
  pinMode(buttonApin, INPUT_PULLUP);
  pinMode(buttonBpin, INPUT_PULLUP);
  lastA = digitalRead(buttonApin);
  lastB = digitalRead(buttonBpin);
  ledUpdate();
}

void loop()
{ 
  if ((lastA == 0) && (digitalRead(buttonApin) == 1))
  {
    counter += 1;
  }
  if ((lastB == 0) && (digitalRead(buttonBpin) == 1))
  {
    counter -= 1;
  }
  lastA = digitalRead(buttonApin);
  lastB = digitalRead(buttonBpin);
  counter %= 8;
  ledReport(counter);
  Serial.print(counter);
  Serial.println();
}
