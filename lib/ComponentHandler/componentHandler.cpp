#include "componentHandler.h"

void pinSetup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void blinkLedBuiltin(int ripetitions) {
  int i = 0;
  while (i < ripetitions) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(125);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(125);
    i++;
  }
}