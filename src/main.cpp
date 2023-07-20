#include <Arduino.h>

#include <Servo.h>

#include <QCFA.h>

void setup()
{
  int motor1_esc_pin = 3;
  int motor2_esc_pin = 5;
  int motor3_esc_pin = 6;
  int motor4_esc_pin = 9;
  mass = 0.3525;  /* variable of the mass */
  radius = 0.038; /* variable of the propeller radius */
  voltage = 22.8; /* variable of the battery voltage */
  KVs = 2450;     /* variable of the KVs of the motor */
  /* The pulse width attached to pins 9, 3, 5, 6
   have a minimum of 1000 µs and maximum of 2000 µs */
  ESC1.attach(motor1_esc_pin, 1000, 2000);
  ESC2.attach(motor2_esc_pin, 1000, 2000);
  ESC3.attach(motor3_esc_pin, 1000, 2000);
  ESC4.attach(motor4_esc_pin, 1000, 2000);
  bool calibrated = false; /* Set calibrated to false if it's the first time */
  if (calibrated == false)
  {
    calibrate(20000); /*20000 µs is the time taken by the ESC to be calibrated (it may vary depending on the ESCs used)*/
  }
}

void loop()
{
  up(2, 30);
  levitate(1000);
  forward(2, 30);
  backward(2, 30);
  rotate(90, 30);
  right(2, 30);
  left(2, 30);
  move_x(2, 30);
  move_y(2, 30);
  move_z(2, 30);
  go_to(-4, 4, 0, 30);
  down(2);
  land();
  ESC1.write(90);
  exit(0);
}