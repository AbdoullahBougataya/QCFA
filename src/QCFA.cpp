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

int calibrate(int bip_time, Servo ESC1 = ESC1, Servo ESC2 = ESC2, Servo ESC3 = ESC3, Servo ESC4 = ESC4)
{
    unsigned long start_time1 = millis();
    while ((millis() - start_time1) <= bip_time)
    {
        ESC1.write(0);
        ESC2.write(0);
        ESC3.write(0);
        ESC4.write(0);
    }
    unsigned long start_time2 = millis();
    while ((millis() - start_time2) <= bip_time)
    {
        ESC1.write(90);
        ESC2.write(90);
        ESC3.write(90);
        ESC4.write(90);
    }
}

int up(float distance, int speed, bool landed = landed, float mass = mass, float radius = radius, float voltage = voltage, int KVs = KVs, Servo ESC1 = ESC1, Servo ESC2 = ESC2, Servo ESC3 = ESC3, Servo ESC4 = ESC4)
{
    unsigned long start_time = millis();
    if (landed)
    {
        land_distance += distance;
    }

    while ((millis() - start_time) - (distance / (4 * (speed / 100) * ((2 * PI * radius * KVs * voltage) / 60))) * 1000 > 0)
    {
        ESC1.write(((1 - (speed / 100) - (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
        ESC2.write(((1 - (speed / 100) - (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
        ESC3.write(((1 + (speed / 100) + (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
        ESC4.write(((1 + (speed / 100) + (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
    }
}

int levitate(int time, float mass = mass, float radius = radius, float voltage = voltage, int KVs = KVs, Servo ESC1 = ESC1, Servo ESC2 = ESC2, Servo ESC3 = ESC3, Servo ESC4 = ESC4)
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

int forward(float distance, int speed, float mass = mass, float radius = radius, float voltage = voltage, int KVs = KVs, Servo ESC1 = ESC1, Servo ESC2 = ESC2, Servo ESC3 = ESC3, Servo ESC4 = ESC4)
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

int backward(float distance, int speed, float mass = mass, float radius = radius, float voltage = voltage, int KVs = KVs, Servo ESC1 = ESC1, Servo ESC2 = ESC2, Servo ESC3 = ESC3, Servo ESC4 = ESC4)
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

int rotate(int degree, int speed, float mass = mass, float radius = radius, float voltage = voltage, int KVs = KVs, Servo ESC1 = ESC1, Servo ESC2 = ESC2, Servo ESC3 = ESC3, Servo ESC4 = ESC4)
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

int right(float distance, int speed, bool pitch = pitch, float mass = mass, float radius = radius, float voltage = voltage, int KVs = KVs, Servo ESC1 = ESC1, Servo ESC2 = ESC2, Servo ESC3 = ESC3, Servo ESC4 = ESC4)
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
    }
    if (!pitch)
    {
        rotate(90.0, speed, mass, radius, voltage, KVs, ESC1, ESC2, ESC3, ESC4);
        forward(distance, speed, mass, radius, distance, KVs, ESC1, ESC2, ESC3, ESC4);
    }
}

int left(float distance, int speed, bool pitch = pitch, float mass = mass, float radius = radius, float voltage = voltage, int KVs = KVs, Servo ESC1 = ESC1, Servo ESC2 = ESC2, Servo ESC3 = ESC3, Servo ESC4 = ESC4)
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
    }
    if (!pitch)
    {
        rotate(90.0, speed, mass, radius, voltage, KVs, ESC1, ESC2, ESC3, ESC4);
        forward(distance, speed, mass, radius, distance, KVs, ESC1, ESC2, ESC3, ESC4);
    }
}

int down(float distance, float mass = mass, float radius = radius, float voltage = voltage, int KVs = KVs, Servo ESC1 = ESC1, Servo ESC2 = ESC2, Servo ESC3 = ESC3, Servo ESC4 = ESC4)
{
    unsigned long start_time = millis();
    land_distance -= distance;
    while ((millis() - start_time) - (distance / (4 * (40 / 100) * ((2 * PI * radius * KVs * voltage) / 60)) * 1000 > 0))
    {
        ESC1.write(((1 + (40 / 100) - (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
        ESC2.write(((1 + (40 / 100) - (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
        ESC3.write(((1 - (40 / 100) + (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
        ESC4.write(((1 - (40 / 100) + (60 * sqrt((mass * 9.8) / (2 * 1.225 * PI * pow(radius, 2) * 0.23))) / (0.9 * PI * 2 * radius * voltage * KVs)) * 90));
    }
}

int move_x(float distance, int speed, float mass = mass, float radius = radius, float voltage = voltage, int KVs = KVs, Servo ESC1 = ESC1, Servo ESC2 = ESC2, Servo ESC3 = ESC3, Servo ESC4 = ESC4)
{
    if (distance > 0)
    {
        forward(distance, speed, mass, radius, distance, KVs, ESC1, ESC2, ESC3, ESC4);
    }
    else if (distance < 0)
    {
        backward(distance, speed, mass, radius, distance, KVs, ESC1, ESC2, ESC3, ESC4);
    }
    else if (distance == 0)
    {
        levitate(1000, mass, radius, voltage, KVs, ESC1, ESC2, ESC3, ESC4);
    }
}

int move_y(float distance, int speed, bool pitch = pitch, float mass = mass, float radius = radius, float voltage = voltage, int KVs = KVs, Servo ESC1 = ESC1, Servo ESC2 = ESC2, Servo ESC3 = ESC3, Servo ESC4 = ESC4)
{
    if (distance > 0)
    {
        right(distance, speed, pitch, mass, radius, voltage, KVs, ESC1, ESC2, ESC3, ESC4);
    }
    else if (distance < 0)
    {
        left(distance, speed, pitch, mass, radius, voltage, KVs, ESC1, ESC2, ESC3, ESC4);
    }
    else if (distance == 0)
    {
        levitate(1000, mass, radius, voltage, KVs, ESC1, ESC2, ESC3, ESC4);
    }
}

int move_z(float distance, int speed, bool landed = landed, float mass = mass, float radius = radius, float voltage = voltage, int KVs = KVs, Servo ESC1 = ESC1, Servo ESC2 = ESC2, Servo ESC3 = ESC3, Servo ESC4 = ESC4)
{
    if (distance > 0)
    {
        up(distance, speed, landed, mass, radius, voltage, KVs, ESC1, ESC2, ESC3, ESC4);
    }
    else if (distance < 0)
    {
        down(distance, mass, radius, voltage, KVs, ESC1, ESC2, ESC3, ESC4);
    }
    else if (distance == 0)
    {
        levitate(1000, mass, radius, voltage, KVs, ESC1, ESC2, ESC3, ESC4);
    }
}

int land(float mass = mass, float radius = radius, float voltage = voltage, int KVs = KVs, Servo ESC1 = ESC1, Servo ESC2 = ESC2, Servo ESC3 = ESC3, Servo ESC4 = ESC4)
{
    if (land_distance > 0)
    {
        down(land_distance, mass, radius, voltage, KVs, ESC1, ESC2, ESC3, ESC4);
        land_distance = 0;
    }
}

int go_to(float x, float y, float z, int speed, bool pitch = pitch, bool landed = landed, float mass = mass, float radius = radius, float voltage = voltage, int KVs = KVs, Servo ESC1 = ESC1, Servo ESC2 = ESC2, Servo ESC3 = ESC3, Servo ESC4 = ESC4)
{
    if (x == 0)
    {
        move_z(z, speed, landed, mass, radius, voltage, KVs, ESC1, ESC2, ESC3, ESC4);
        levitate(1000, mass, radius, voltage, KVs, ESC1, ESC2, ESC3, ESC4);
        move_y(y, speed, pitch, mass, radius, voltage, KVs, ESC1, ESC2, ESC3, ESC4);
        levitate(1000, mass, radius, voltage, KVs, ESC1, ESC2, ESC3, ESC4);
    }
    else if (y == 0)
    {
        move_z(z, speed, landed, mass, radius, voltage, KVs, ESC1, ESC2, ESC3, ESC4);
        levitate(1000, mass, radius, voltage, KVs, ESC1, ESC2, ESC3, ESC4);
        move_x(x, speed, mass, radius, voltage, KVs, ESC1, ESC2, ESC3, ESC4);
        levitate(1000, mass, radius, voltage, KVs, ESC1, ESC2, ESC3, ESC4);
    }
    else if (z == 0 && landed)
    {
        move_z(z, speed, landed, mass, radius, voltage, KVs, ESC1, ESC2, ESC3, ESC4);
        levitate(1000, mass, radius, voltage, KVs, ESC1, ESC2, ESC3, ESC4);
        rotate(floor(acos((x + y) / (x * y))), speed, mass, radius, voltage, KVs, ESC1, ESC2, ESC3, ESC4);
        forward(sqrt(pow(x, 2) + pow(y, 2)), speed, mass, radius, voltage, KVs, ESC1, ESC2, ESC3, ESC4);
        levitate(1000, mass, radius, voltage, KVs, ESC1, ESC2, ESC3, ESC4);
        move_z(z, speed, landed, mass, radius, voltage, KVs, ESC1, ESC2, ESC3, ESC4);
        levitate(1000, mass, radius, voltage, KVs, ESC1, ESC2, ESC3, ESC4);
    }
    move_z(z, speed, landed, mass, radius, voltage, KVs, ESC1, ESC2, ESC3, ESC4);
    levitate(1000, mass, radius, voltage, KVs, ESC1, ESC2, ESC3, ESC4);
    rotate(floor(acos((x + y) / (x * y))), speed, mass, radius, voltage, KVs, ESC1, ESC2, ESC3, ESC4);
    forward(sqrt(pow(x, 2) + pow(y, 2)), speed, mass, radius, voltage, KVs, ESC1, ESC2, ESC3, ESC4);
    levitate(1000, mass, radius, voltage, KVs, ESC1, ESC2, ESC3, ESC4);
}
