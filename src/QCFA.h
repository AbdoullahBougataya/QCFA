#include <Arduino.h>

#include <Servo.h>

float land_distance;
bool pitch;
bool landed;

int calibrate(Servo, Servo, Servo, Servo, int);
int up(Servo, Servo, Servo, Servo, int, float, float, float, float, int, bool landed = true);
int levitate(Servo, Servo, Servo, Servo, int, float, float, float, int);
int forward(Servo, Servo, Servo, Servo, int, float, float, float, float, int);
int backward(Servo, Servo, Servo, Servo, int, float, float, float, float, int);
int rotate(Servo, Servo, Servo, Servo, int, float, float, float, float, int);
int right(Servo, Servo, Servo, Servo, int, float, float, float, float, int, bool pitch = false);
int left(Servo, Servo, Servo, Servo, int, float, float, float, float, int, bool pitch = false);
int down(Servo, Servo, Servo, Servo, float, float, float, float, int);
int move_x(Servo, Servo, Servo, Servo, int, float, float, float, float, int);
int move_y(Servo, Servo, Servo, Servo, int, float, float, float, float, int, bool pitch = false);
int move_z(Servo, Servo, Servo, Servo, int, float, float, float, float, int, bool landed = true);
int land(Servo, Servo, Servo, Servo, int, float, float, int);
int go_to(Servo, Servo, Servo, Servo, int, float, float, float, float, float, float, int, bool pitch = false, bool landed = true);