#include <Arduino.h>

#include <Servo.h>

Servo ESC1;
Servo ESC2;
Servo ESC3;
Servo ESC4;

void setup()
{
  int motor1_esc_pin = 3;
  int motor2_esc_pin = 5;
  int motor3_esc_pin = 6;
  int motor4_esc_pin = 9;
  /* The pulse width attached to pin 9 in microseconds
   with a minimum of 1000 µs and maximum of 2000 µs */
  ESC1.attach(motor1_esc_pin, 1000, 2000);
  bool calibrated = false; /* Set calibrated to false if it's the first time */
  if (calibrated == false)
  {
    calibrate(ESC1, ESC2, ESC3, ESC4, 10000);
  }
}

void loop()
{
  up(ESC1, ESC2, ESC3, ESC4, 30, 0.3525, 0.038, 2, 22.8, 2450);      /* up(..., ..., ..., ..., speed in (%), mass in (Kg), propeller radius in (m), distance in (m), battery voltage in (v), motor KVs in (KV)) */
  forward(ESC1, ESC2, ESC3, ESC4, 30, 0.3525, 0.038, 2, 22.8, 2450); /* forward(..., ..., ..., ..., speed in (%), mass in (Kg), propeller radius in (m), distance in (m), battery voltage in (v), motor KVs in (KV)) */
  ESC1.write(90);
}

int calibrate(Servo ESC1, Servo ESC2, Servo ESC3, Servo ESC4, int bip_time)
{
  unsigned long start_time = millis();
  while ((millis() - start_time) <= bip_time) /* Do this loop for up to 10000mS */
  {
    ESC1.write(0);
    ESC2.write(0);
    ESC3.write(0);
    ESC4.write(0);
  }
  unsigned long start_time = millis();
  while ((millis() - start_time) <= bip_time) /* Do this loop for up to 10000mS */
  {
    ESC1.write(90);
    ESC2.write(90);
    ESC3.write(90);
    ESC4.write(90);
  }
}

int up(Servo ESC1, Servo ESC2, Servo ESC3, Servo ESC4, int speed, float mass, float radius, float distance, float voltage, int KVs)
{
  unsigned long start_time = millis();
  while ((millis() - start_time) - (distance / (4 * (speed / 100) * ((2 * PI * radius * KVs * voltage) / 60))) * 1000 > 0)
  {
    ESC1.write(((1 - (speed / 100) - (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
    ESC2.write(((1 - (speed / 100) - (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
    ESC3.write(((1 + (speed / 100) + (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
    ESC4.write(((1 + (speed / 100) + (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
  }
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

int levitate(Servo ESC1, Servo ESC2, Servo ESC3, Servo ESC4, int time, float mass, float radius, float voltage, int KVs)
{
  unsigned long start_time = millis();
  while ((millis() - start_time) - time > 0)
  {
    ESC1.write(((1 - (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
    ESC2.write(((1 - (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
    ESC3.write(((1 + (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
    ESC4.write(((1 + (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
  }
}

int forward(Servo ESC1, Servo ESC2, Servo ESC3, Servo ESC4, int speed, float mass, float radius, float distance, float voltage, int KVs)
{
  unsigned long start_time = millis();
  while ((millis() - start_time) - (distance / (4 * (speed / 100) * ((2 * PI * radius * KVs * voltage) / 60))) * 1000 > 0)
  {
    ESC1.write(((1 - (speed / 100) - (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
    ESC2.write(((1 - ((speed - 20) / 100) - (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
    ESC3.write(((1 + (speed / 100) + (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
    ESC4.write(((1 + ((speed - 20) / 100) + (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
  }
}

int backward(Servo ESC1, Servo ESC2, Servo ESC3, Servo ESC4, int speed, float mass, float radius, float distance, float voltage, int KVs)
{
  unsigned long start_time = millis();
  while ((millis() - start_time) - (distance / (4 * (speed / 100) * ((2 * PI * radius * KVs * voltage) / 60))) * 1000 > 0)
  {
    ESC1.write(((1 - ((speed - 20) / 100) - (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
    ESC2.write(((1 - (speed / 100) - (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
    ESC3.write(((1 + ((speed - 20) / 100) + (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
    ESC4.write(((1 + (speed / 100) + (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
  }
}

int rotate(Servo ESC1, Servo ESC2, Servo ESC3, Servo ESC4, int speed, float mass, float radius, float degree, float voltage, int KVs)
{
  unsigned long start_time = millis();
  while ((millis() - start_time) - (degree / 4 * ((speed / 100) * KVs * voltage * 6 + KVs * voltage * 6)) * 1000 > 0)
  {
    if (degree > 0)
    {
      ESC1.write(((1 - (speed / 100) - (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
      ESC2.write(((1 - (speed / 100) - (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
      ESC3.write(((1 - (speed / 100) - (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
      ESC4.write(((1 - (speed / 100) - (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
    }
    else if (degree < 0)
    {
      ESC1.write(((1 + (speed / 100) - (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
      ESC2.write(((1 + (speed / 100) - (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
      ESC3.write(((1 + (speed / 100) - (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
      ESC4.write(((1 + (speed / 100) - (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
    }
  }
}

int right(Servo ESC1, Servo ESC2, Servo ESC3, Servo ESC4, int speed, float mass, float radius, float distance, float voltage, int KVs, bool pitch = true)
{
  unsigned long start_time = millis();
  while ((millis() - start_time) - (distance / (4 * (speed / 100) * ((2 * PI * radius * KVs * voltage) / 60))) * 1000 > 0)
  {
    if (pitch)
    {
      ESC1.write(((1 - (speed / 100) - (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
      ESC2.write(((1 - (speed / 100) - (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
      ESC3.write(((1 + ((speed - 20) / 100) + (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
      ESC4.write(((1 + ((speed - 20) / 100) + (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
    }
    else if (!pitch)
    {
      rotate(ESC1, ESC2, ESC3, ESC4, speed, mass, radius, 90.0, voltage, KVs);
      forward(ESC1, ESC2, ESC3, ESC4, speed, mass, radius, distance, voltage, KVs);
    }
  }
}

int left(Servo ESC1, Servo ESC2, Servo ESC3, Servo ESC4, int speed, float mass, float radius, float distance, float voltage, int KVs, bool pitch = true)
{
  unsigned long start_time = millis();
  while ((millis() - start_time) - (distance / (4 * (speed / 100) * ((2 * PI * radius * KVs * voltage) / 60))) * 1000 > 0)
  {
    if (pitch)
    {
      ESC1.write(((1 - ((speed - 20) / 100) - (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
      ESC2.write(((1 - ((speed - 20) / 100) - (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
      ESC3.write(((1 + (speed / 100) + (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
      ESC4.write(((1 + (speed / 100) + (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
    }
    else if (!pitch)
    {
      rotate(ESC1, ESC2, ESC3, ESC4, speed, mass, radius, -90.0, voltage, KVs);
      forward(ESC1, ESC2, ESC3, ESC4, speed, mass, radius, distance, voltage, KVs);
    }
  }
}

int down(Servo ESC1, Servo ESC2, Servo ESC3, Servo ESC4, int speed, float mass, float radius, float distance, float voltage, int KVs)
{
  unsigned long start_time = millis();
  while ((millis() - start_time) - (distance / (4 * (speed / 100) * ((2 * PI * radius * KVs * voltage) / 60)) * 1000 > 0))
  {
    ESC1.write(((1 + (speed / 100) - (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
    ESC2.write(((1 + (speed / 100) - (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
    ESC3.write(((1 - (speed / 100) + (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
    ESC4.write(((1 - (speed / 100) + (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
  }
}

int move_x(Servo ESC1, Servo ESC2, Servo ESC3, Servo ESC4, int speed, float mass, float radius, float distance, float voltage, int KVs)
{
  if (distance > 0)
  {
    forward(ESC1, ESC2, ESC3, ESC4, speed, mass, radius, distance, voltage, KVs);
  }
  else if (distance < 0)
  {
    backward(ESC1, ESC2, ESC3, ESC4, speed, mass, radius, distance, voltage, KVs);
  }
  else if (distance == 0)
  {
    levitate(ESC1, ESC2, ESC3, ESC4, 1000, mass, radius, voltage, KVs);
  }
}

int move_y(Servo ESC1, Servo ESC2, Servo ESC3, Servo ESC4, int speed, float mass, float radius, float distance, float voltage, int KVs, bool pitch = true)
{
  if (distance > 0)
  {
    right(ESC1, ESC2, ESC3, ESC4, speed, mass, radius, distance, voltage, KVs, pitch);
  }
  else if (distance < 0)
  {
    left(ESC1, ESC2, ESC3, ESC4, speed, mass, radius, distance, voltage, KVs, pitch);
  }
  else if (distance == 0)
  {
    levitate(ESC1, ESC2, ESC3, ESC4, 1000, mass, radius, voltage, KVs);
  }
}

int move_z(Servo ESC1, Servo ESC2, Servo ESC3, Servo ESC4, int speed, float mass, float radius, float distance, float voltage, int KVs)
{
  if (distance > 0)
  {
    up(ESC1, ESC2, ESC3, ESC4, speed, mass, radius, distance, voltage, KVs);
  }
  else if (distance < 0)
  {
    down(ESC1, ESC2, ESC3, ESC4, speed, mass, radius, distance, voltage, KVs);
  }
  else if (distance == 0)
  {
    levitate(ESC1, ESC2, ESC3, ESC4, 1000, mass, radius, voltage, KVs);
  }
}

int go_to(Servo ESC1, Servo ESC2, Servo ESC3, Servo ESC4, int speed, float x, float y, float z, float mass, float radius, float voltage, int KVs, bool pitch = true)
{
  if (x == 0)
  {
    move_z(ESC1, ESC2, ESC3, ESC4, speed, mass, radius, z, voltage, KVs);
    levitate(ESC1, ESC2, ESC3, ESC4, 1000, mass, radius, voltage, KVs);
    move_y(ESC1, ESC2, ESC3, ESC4, speed, mass, radius, y, voltage, KVs, false);
    levitate(ESC1, ESC2, ESC3, ESC4, 1000, mass, radius, voltage, KVs);
  }
  else if (y == 0)
  {
    move_z(ESC1, ESC2, ESC3, ESC4, speed, mass, radius, z, voltage, KVs);
    levitate(ESC1, ESC2, ESC3, ESC4, 1000, mass, radius, voltage, KVs);
    move_x(ESC1, ESC2, ESC3, ESC4, speed, mass, radius, x, voltage, KVs);
    levitate(ESC1, ESC2, ESC3, ESC4, 1000, mass, radius, voltage, KVs);
  }
  else if (z == 0)
  {
    move_z(ESC1, ESC2, ESC3, ESC4, speed, mass, radius, 1, voltage, KVs);
    levitate(ESC1, ESC2, ESC3, ESC4, 1000, mass, radius, voltage, KVs);
    rotate(ESC1, ESC2, ESC3, ESC4, speed, mass, radius, acos((x + y) / (x * y)), voltage, KVs);
    forward(ESC1, ESC2, ESC3, ESC4, speed, mass, radius, sqrt(pow(x, 2) + pow(y, 2)), voltage, KVs);
    levitate(ESC1, ESC2, ESC3, ESC4, 1000, mass, radius, voltage, KVs);
    move_z(ESC1, ESC2, ESC3, ESC4, speed, mass, radius, -1, voltage, KVs);
    levitate(ESC1, ESC2, ESC3, ESC4, 1000, mass, radius, voltage, KVs);
  }
  move_z(ESC1, ESC2, ESC3, ESC4, speed, mass, radius, z, voltage, KVs);
  levitate(ESC1, ESC2, ESC3, ESC4, 1000, mass, radius, voltage, KVs);
  rotate(ESC1, ESC2, ESC3, ESC4, speed, mass, radius, acos((x + y) / (x * y)), voltage, KVs);
  forward(ESC1, ESC2, ESC3, ESC4, speed, mass, radius, sqrt(pow(x, 2) + pow(y, 2)), voltage, KVs);
  levitate(ESC1, ESC2, ESC3, ESC4, 1000, mass, radius, voltage, KVs);
}
