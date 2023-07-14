#include <Arduino.h>

#include <Servo.h>

Servo ESC1;
Servo ESC2;
Servo ESC3;
Servo ESC4;

int motor1_esc_pin = 9;
int motor2_esc_pin = 9;
int motor3_esc_pin = 9;
int motor4_esc_pin = 9;

void setup()
{
  /* The pulse width attached to pin 9 in microseconds
   with a minimum of 1000 µs and maximum of 2000 µs */
  ESC1.attach(motor1_esc_pin, 1000, 2000);
}

void loop()
{
  ESC1.write(90);
}

int buttonPressed(int button)
{
  static uint16_t lastStates = 0;
  int state = digitalRead(button);
  if (state != ((lastStates >> button) & 1))
  {
    lastStates ^= 1 << button;
    return state == HIGH;
  }
  return false;
}
