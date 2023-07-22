#include <Arduino.h>

#include <Servo.h>

#include <QCFA.h>

struct Quadcopter drone;

void setup()
{
  int motor1_esc_pin = 3;
  int motor2_esc_pin = 5;
  int motor3_esc_pin = 6;
  int motor4_esc_pin = 9;
  drone.mass = 0.3525;  /*variable of the mass */
  drone.radius = 0.038; /*variable of the propeller radius */
  drone.voltage = 22.8; /*variable of the battery voltage */
  drone.KVs = 2450;     /*variable of the KVs of the motor */
  /* The pulse width attached to pins 9, 3, 5, 6
   have a minimum of 1000 µs and maximum of 2000 µs */
  drone.ESC1.attach(motor1_esc_pin, 1000, 2000);
  drone.ESC2.attach(motor2_esc_pin, 1000, 2000);
  drone.ESC3.attach(motor3_esc_pin, 1000, 2000);
  drone.ESC4.attach(motor4_esc_pin, 1000, 2000);
  bool calibrated = false; /* Set calibrated to false if it's the first time */
  if (calibrated == false)
  {
    calibrate(drone, 20000); /*20000 ms is the time taken by the ESC to be calibrated (it may vary depending on the ESCs used)*/
  }
}

void loop()
{
  up(drone, 2, 30);
  levitate(drone, 1000);
  forward(drone, 2, 30);
  backward(drone, 2, 30);
  rotate(drone, 90, 30);
  right(drone, 2, 30);
  left(drone, 2, 30);
  move_x(drone, 2, 30);
  move_y(drone, 2, 30);
  move_z(drone, 2, 30);
  go_to(drone, -4, 4, 0, 30);
  down(drone, 2);
  land(drone);
  drone.ESC1.write(90);
  exit(0);
}