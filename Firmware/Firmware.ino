////////////////////////////
// Firmware ver 0.1
// by Yariv Amar
////////////////////////////
#include <BlockNot.h>

#define timeoutSeconds 300
#define buttonPin 2
#define pumpPin 13
#define ledPin 9

BlockNot ledTimer(timeoutSeconds, SECONDS);
BlockNot pumpTimer(timeoutSeconds, SECONDS);

bool isLedOn = false;
bool isPumpRunning = false;

void turnLedOff() {
  digitalWrite(ledPin, LOW);
  isLedOn = false;
}

void setup()
{
  pinMode(buttonPin, INPUT);
  pinMode(pumpPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  if (digitalRead(buttonPin) == 1){ //Switch ON
    if (isPumpRunning == false) {
      pumpTimer.RESET;
      ledTimer.RESET;
      isPumpRunning = true;
      digitalWrite(pumpPin, HIGH);
      digitalWrite(ledPin, HIGH);
      isLedOn = true;
    }
    if (pumpTimer.HAS_TRIGGERED) {
      digitalWrite(pumpPin, LOW);
      if (pumpTimer.FIRST_TRIGGER) {
        ledTimer.RESET;
      }
      if (ledTimer.HAS_TRIGGERED && isLedOn) {
        turnLedOff();
      }
    }
  } else {
    if (isPumpRunning) {
      isPumpRunning = false;
      ledTimer.RESET;
    }
    digitalWrite(pumpPin, LOW);
    if (ledTimer.HAS_TRIGGERED && isLedOn) {      
      turnLedOff();
    }
  }
}
