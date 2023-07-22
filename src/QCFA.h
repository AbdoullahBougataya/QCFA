#include <Arduino.h>
#include <Servo.h>

float land_distance = 0;
bool pitch = false;
bool landed = true;
struct Quadcopter
{
    Servo ESC1;
    Servo ESC2;
    Servo ESC3;
    Servo ESC4;
    float mass;
    float radius;
    float voltage;
    int KVs;
};

int calibrate(struct Quadcopter parameters, int bip_time);
int up(struct Quadcopter parameters, float distance, int speed, bool landed = landed);
int levitate(struct Quadcopter parameters, int time);
int forward(struct Quadcopter parameters, float distance, int speed);
int backward(struct Quadcopter parameters, float distance, int speed);
int rotate(struct Quadcopter parameters, int degree, int speed);
int right(struct Quadcopter parameters, float distance, int speed, bool pitch = pitch);
int left(struct Quadcopter parameters, float distance, int speed, bool pitch = pitch);
int down(struct Quadcopter parameters, float distance);
int move_x(struct Quadcopter parameters, float distance, int speed);
int move_y(struct Quadcopter parameters, float distance, int speed, bool pitch = pitch);
int move_z(struct Quadcopter parameters, float distance, int speed, bool landed = landed);
int land(struct Quadcopter parameters);
int go_to(struct Quadcopter parameters, float x, float y, float z, int speed, bool pitch = pitch, bool landed = landed);