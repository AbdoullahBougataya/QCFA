#include <Arduino.h>

#include <Servo.h>

#include <QCFA.h>

struct Quadcopter drone; /*get the drone parameters from the quadcopter structure*/

void setup()
{
  int motor1_esc_pin = 6;
  int motor2_esc_pin = 10;
  int motor3_esc_pin = 9;
  int motor4_esc_pin = 11;
  drone.mass = 352.5;           /*variable of the mass in (g) */
  drone.propellers_radius = 38; /*variable of the propeller radius in (mm) */
  drone.voltage = 22.8;         /*variable of the battery voltage in (v) */
  drone.KVs = 2450;             /*variable of the KVs of the motor (KV) */
  /* The pulse width attached to pins 6, 9, 10 and 11
   have a minimum of 1000 µs and maximum of 2000 µs */
  drone.ESC1.attach(motor1_esc_pin, 1000, 2000);
  drone.ESC2.attach(motor2_esc_pin, 1000, 2000);
  drone.ESC3.attach(motor3_esc_pin, 1000, 2000);
  drone.ESC4.attach(motor4_esc_pin, 1000, 2000);
  bool calibrated = false; /* Set calibrated to false if it's the first time */
  if (calibrated == false)
  {
    calibrate(drone, 20000); /*20 s is the time taken by the ESC to make that beep so this calibration process will take 40s (it may vary depending on the ESCs used)*/
  }
}

void loop()
{
  up(drone, 2, 30);           /*up(Quadcopter parameter, hight, speed)*/
  levitate(drone, 1000);      /*levitate(Quadcopter parameter, levitation time)*/
  forward(drone, 2, 30);      /*forward(Quadcopter parameter, distance, speed)*/
  backward(drone, 2, 30);     /*backward(Quadcopter parameter, distance, speed)*/
  rotate(drone, 90, 30);      /*rotate(Quadcopter parameter, angle, speed)*/
  right(drone, 2, 30);        /*right(Quadcopter parameter, distance, speed)*/
  left(drone, 2, 30);         /*left(Quadcopter parameter, distance, speed)*/
  move_x(drone, 2, 30);       /*move_x(Quadcopter parameter, distance, speed)*/
  move_y(drone, 2, 30);       /*move_y(Quadcopter parameter, distance, speed)*/
  move_z(drone, 2, 30);       /*move_z(Quadcopter parameter, hight, speed)*/
  go_to(drone, -4, 4, 0, 30); /*goto(Quadcopter parameter, x coordinates, y coordinates, z coordinates, speed)*/
  down(drone, 2);             /*down(Quadcopter parameter, hight)*/
  land(drone);                /*land(Quadcopter parameter)*/
  stop(drone);                /*stop(Quadcopter parameter)*/
  exit(0);                    /*exit from the loop*/
}