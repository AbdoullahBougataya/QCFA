#include <Arduino.h>

#include <Servo.h>

#include <QCFA.h>

Servo ESC1;
Servo ESC2;
Servo ESC3;
Servo ESC4;
float land_distance = 0;

void setup()
{
  int motor1_esc_pin = 3;
  int motor2_esc_pin = 5;
  int motor3_esc_pin = 6;
  int motor4_esc_pin = 9;
  /* The pulse width attached to pins 9, 3, 5, 6
   have a minimum of 1000 µs and maximum of 2000 µs */
  ESC1.attach(motor1_esc_pin, 1000, 2000);
  ESC2.attach(motor2_esc_pin, 1000, 2000);
  ESC3.attach(motor3_esc_pin, 1000, 2000);
  ESC4.attach(motor4_esc_pin, 1000, 2000);
  bool calibrated = false; /* Set calibrated to false if it's the first time */
  if (calibrated == false)
  {
    calibrate(ESC1, ESC2, ESC3, ESC4, 20000); /*20000 µs is the time taken by the ESC to be calibrated (it may vary depending on the ESCs used)*/
  }
}

void loop()
{
  up(ESC1, ESC2, ESC3, ESC4, 30, 0.3525, 0.038, 2, 22.8, 2450);           /* up(ESC1, ESC2, ESC3, ESC4, speed in relation to max speed in (%), total mass in (Kg), propeller radius in (m), distance in (m), battery voltage in (v), motor KVs in (KV), optional if the quadcopter is landed or not) */
  levitate(ESC1, ESC2, ESC3, ESC4, 1000, 0.3525, 0.038, 22.8, 2450);      /* levitate(..., ..., ..., ..., levitation time in (µs), total mass in (Kg), propeller radius in (m), distance in (m), battery voltage in (v), motor KVs in (KV)) */
  forward(ESC1, ESC2, ESC3, ESC4, 30, 0.3525, 0.038, 2, 22.8, 2450);      /* forward(..., ..., ..., ..., speed in relation to max speed in (%), total mass in (Kg), propeller radius in (m), distance in (m), battery voltage in (v), motor KVs in (KV)) */
  backward(ESC1, ESC2, ESC3, ESC4, 30, 0.3525, 0.038, 2, 22.8, 2450);     /* backward(..., ..., ..., ..., speed in relation to max speed in (%), total mass in (Kg), propeller radius in (m), distance in (m), battery voltage in (v), motor KVs in (KV)) */
  rotate(ESC1, ESC2, ESC3, ESC4, 30, 0.3525, 0.038, 90, 22.8, 2450);      /* rotate(..., ..., ..., ..., speed in relation to max speed in (%), total mass in (Kg), propeller radius in (m), rotation in (°), battery voltage in (v), motor KVs in (KV)) */
  right(ESC1, ESC2, ESC3, ESC4, 30, 0.3525, 0.038, 2, 22.8, 2450);        /* right(..., ..., ..., ..., speed in relation to max speed in (%), total mass in (Kg), propeller radius in (m), distance in (m), battery voltage in (v), motor KVs in (KV), optional if you want translate without rotating or not) */
  left(ESC1, ESC2, ESC3, ESC4, 30, 0.3525, 0.038, 2, 22.8, 2450);         /* left(..., ..., ..., ..., speed in relation to max speed in (%), total mass in (Kg), propeller radius in (m), distance in (m), battery voltage in (v), motor KVs in (KV), optional if you want translate without rotating or not) */
  move_x(ESC1, ESC2, ESC3, ESC4, 30, 0.3525, 0.038, 2, 22.8, 2450);       /* move_x(..., ..., ..., ..., speed in relation to max speed in (%), total mass in (Kg), propeller radius in (m), distance in (m) might be positive or negative, battery voltage in (v), motor KVs in (KV)) */
  move_y(ESC1, ESC2, ESC3, ESC4, 30, 0.3525, 0.038, 2, 22.8, 2450);       /* move_y(..., ..., ..., ..., speed in relation to max speed in (%), total mass in (Kg), propeller radius in (m), distance in (m) might be positive or negative, battery voltage in (v), motor KVs in (KV), optional if you want translate without rotating or not) */
  move_z(ESC1, ESC2, ESC3, ESC4, 30, 0.3525, 0.038, 2, 22.8, 2450);       /* move_z(..., ..., ..., ..., speed in relation to max speed in (%), total mass in (Kg), propeller radius in (m), distance in (m) might be positive or negative, battery voltage in (v), motor KVs in (KV), optional if the quadcopter is landed or not) */
  go_to(ESC1, ESC2, ESC3, ESC4, 30, -4, 4, 0, 0.3525, 0.038, 22.8, 2450); /* go_to(..., ..., ..., ..., speed in relation to max speed in (%), targeted x coordinates in (m), targeted y coordinates in (m), targeted z coordinates in (m), total mass in (Kg), propeller radius in (m), distance in (m) might be positive or negative, battery voltage in (v), motor KVs in (KV), optional if you want translate without rotating or not (false by default), optional if the quadcopter is landed or not (true by default)) */
  down(ESC1, ESC2, ESC3, ESC4, 0.3525, 0.038, 2, 22.8, 2450);             /* down(..., ..., ..., ..., total mass in (Kg), propeller radius in (m), distance in (m), battery voltage in (v), motor KVs in (KV)) */
  land(ESC1, ESC2, ESC3, ESC4, 0.3525, 0.038, 22.8, 2450);                /* land(..., ..., ..., ..., total mass in (Kg), propeller radius in (m), battery voltage in (v), motor KVs in (KV)) */
  ESC1.write(90);
}