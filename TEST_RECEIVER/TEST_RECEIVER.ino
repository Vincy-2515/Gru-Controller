#include <Arduino.h>

//DIRECTION_PIN_1 (brown): {ESP-32: 23, ARDUINO-UNO: 9}
//DIRECTION_PIN_2 (red): {ESP-32: 22, ARDUINO-UNO: 10}
//SPEED_PIN (white): {ESP-32: 21, ARDUINO-UNO: 11}

#define DIRECTION_PIN_1 (9)
#define DIRECTION_PIN_2 (10)
#define SPEED_PIN A0

const unsigned long PULSE_TIMEOUT_US = 200000UL;

void setup() {
  Serial.begin(115200);
  pinMode(DIRECTION_PIN_1, INPUT);
  pinMode(DIRECTION_PIN_2, INPUT);
  pinMode(SPEED_PIN, INPUT);
}

void loop() {
  int direction1 = digitalRead(DIRECTION_PIN_1);
  int direction2 = digitalRead(DIRECTION_PIN_2);

  unsigned long highTime = pulseIn(SPEED_PIN, HIGH, PULSE_TIMEOUT_US);
  unsigned long lowTime  = pulseIn(SPEED_PIN, LOW,  PULSE_TIMEOUT_US);

  float duty = 0.0f;
  if ((highTime + lowTime) > 0) {
    duty = (float)highTime / (float)(highTime + lowTime);
  }

  int pwmValue = (int)round(duty * 255.0f);
  float rawPwmValue = duty * 255.0f;

  Serial.print("DIR_PIN_1:");
  Serial.print(direction1);
  Serial.print(",DIR_PIN_2:");
  Serial.print(direction2);
  Serial.print(",SPEED_PIN:");
  Serial.print(pwmValue);
  Serial.print(",RAW_SPEED:");
  Serial.println(rawPwmValue);

  delay(100);
}
