#include <Arduino.h>

#include <Servo.h>

float land_distance = 0;
bool pitch = false;
bool landed = true;
float mass;
float radius;
float voltage;
int KVs;
Servo ESC1;
Servo ESC2;
Servo ESC3;
Servo ESC4;

int calibrate(int bip_time, Servo ESC1 = ESC1, Servo ESC2 = ESC2, Servo ESC3 = ESC3, Servo ESC4 = ESC4);
int up(float distance, int speed, bool landed = landed, float mass = mass, float radius = radius, float voltage = voltage, int KVs = KVs, Servo ESC1 = ESC1, Servo ESC2 = ESC2, Servo ESC3 = ESC3, Servo ESC4 = ESC4);
int levitate(int time, float mass = mass, float radius = radius, float voltage = voltage, int KVs = KVs, Servo ESC1 = ESC1, Servo ESC2 = ESC2, Servo ESC3 = ESC3, Servo ESC4 = ESC4);
int forward(float distance, int speed, float mass = mass, float radius = radius, float voltage = voltage, int KVs = KVs, Servo ESC1 = ESC1, Servo ESC2 = ESC2, Servo ESC3 = ESC3, Servo ESC4 = ESC4);
int backward(float distance, int speed, float mass = mass, float radius = radius, float voltage = voltage, int KVs = KVs, Servo ESC1 = ESC1, Servo ESC2 = ESC2, Servo ESC3 = ESC3, Servo ESC4 = ESC4);
int rotate(int degree, int speed, float mass = mass, float radius = radius, float voltage = voltage, int KVs = KVs, Servo ESC1 = ESC1, Servo ESC2 = ESC2, Servo ESC3 = ESC3, Servo ESC4 = ESC4);
int right(float distance, int speed, bool pitch = pitch, float mass = mass, float radius = radius, float voltage = voltage, int KVs = KVs, Servo ESC1 = ESC1, Servo ESC2 = ESC2, Servo ESC3 = ESC3, Servo ESC4 = ESC4);
int left(float distance, int speed, bool pitch = pitch, float mass = mass, float radius = radius, float voltage = voltage, int KVs = KVs, Servo ESC1 = ESC1, Servo ESC2 = ESC2, Servo ESC3 = ESC3, Servo ESC4 = ESC4);
int down(float distance, float mass = mass, float radius = radius, float voltage = voltage, int KVs = KVs, Servo ESC1 = ESC1, Servo ESC2 = ESC2, Servo ESC3 = ESC3, Servo ESC4 = ESC4);
int move_x(float distance, int speed, float mass = mass, float radius = radius, float voltage = voltage, int KVs = KVs, Servo ESC1 = ESC1, Servo ESC2 = ESC2, Servo ESC3 = ESC3, Servo ESC4 = ESC4);
int move_y(float distance, int speed, bool pitch = pitch, float mass = mass, float radius = radius, float voltage = voltage, int KVs = KVs, Servo ESC1 = ESC1, Servo ESC2 = ESC2, Servo ESC3 = ESC3, Servo ESC4 = ESC4);
int move_z(float distance, int speed, bool landed = landed, float mass = mass, float radius = radius, float voltage = voltage, int KVs = KVs, Servo ESC1 = ESC1, Servo ESC2 = ESC2, Servo ESC3 = ESC3, Servo ESC4 = ESC4);
int land(float mass = mass, float radius = radius, float voltage = voltage, int KVs = KVs, Servo ESC1 = ESC1, Servo ESC2 = ESC2, Servo ESC3 = ESC3, Servo ESC4 = ESC4);
int go_to(float x, float y, float z, int speed, bool pitch = pitch, bool landed = landed, float mass = mass, float radius = radius, float voltage = voltage, int KVs = KVs, Servo ESC1 = ESC1, Servo ESC2 = ESC2, Servo ESC3 = ESC3, Servo ESC4 = ESC4);