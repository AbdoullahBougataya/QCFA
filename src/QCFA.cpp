#include <Arduino.h>

#include <Servo.h>

float land_distance = 0;

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

int calibrate(struct Quadcopter parameters, int bip_time)
{
    signed long start_time1 = millis();
    while ((millis() - start_time1) <= bip_time)
    {
        parameters.ESC1.write(0);
        parameters.ESC2.write(0);
        parameters.ESC3.write(0);
        parameters.ESC4.write(0);
    }
    signed long start_time2 = millis();
    while ((millis() - start_time2) <= bip_time)
    {
        parameters.ESC1.write(90);
        parameters.ESC2.write(90);
        parameters.ESC3.write(90);
        parameters.ESC4.write(90);
    }
    return 0;
}

int up(struct Quadcopter parameters, float distance, int speed, bool landed = true)
{
    signed long start_time = millis();
    if (landed)
    {
        land_distance += distance;
    }

    while ((millis() - start_time) - (distance / (4 * (speed / 100) * ((2 * PI * parameters.radius * parameters.KVs * parameters.voltage) / 60))) * 1000 > 0)
    {
        parameters.ESC1.write(((1 - (speed / 100) - (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.radius * parameters.voltage * parameters.KVs)) * 90));
        parameters.ESC2.write(((1 - (speed / 100) - (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.radius * parameters.voltage * parameters.KVs)) * 90));
        parameters.ESC3.write(((1 + (speed / 100) + (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.radius * parameters.voltage * parameters.KVs)) * 90));
        parameters.ESC4.write(((1 + (speed / 100) + (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.radius * parameters.voltage * parameters.KVs)) * 90));
    }
    return 0;
}

int levitate(struct Quadcopter parameters, int time)
{
    signed long start_time = millis();
    while ((millis() - start_time) - time > 0)
    {
        parameters.ESC1.write(((1 - (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.radius * parameters.voltage * parameters.KVs)) * 90));
        parameters.ESC2.write(((1 - (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.radius * parameters.voltage * parameters.KVs)) * 90));
        parameters.ESC3.write(((1 + (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.radius * parameters.voltage * parameters.KVs)) * 90));
        parameters.ESC4.write(((1 + (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.radius * parameters.voltage * parameters.KVs)) * 90));
    }
    return 0;
}

int forward(struct Quadcopter parameters, float distance, int speed)
{
    signed long start_time = millis();
    while ((millis() - start_time) - (distance / (4 * (speed / 100) * ((2 * PI * parameters.radius * parameters.KVs * parameters.voltage) / 60))) * 1000 > 0)
    {
        parameters.ESC1.write(((1 - (speed / 100) - (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.radius * parameters.voltage * parameters.KVs)) * 90));
        parameters.ESC2.write(((1 - ((speed - 20) / 100) - (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.radius * parameters.voltage * parameters.KVs)) * 90));
        parameters.ESC3.write(((1 + (speed / 100) + (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.radius * parameters.voltage * parameters.KVs)) * 90));
        parameters.ESC4.write(((1 + ((speed - 20) / 100) + (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.radius * parameters.voltage * parameters.KVs)) * 90));
    }
    return 0;
}

int backward(struct Quadcopter parameters, float distance, int speed)
{
    signed long start_time = millis();
    while ((millis() - start_time) - (distance / (4 * (speed / 100) * ((2 * PI * parameters.radius * parameters.KVs * parameters.voltage) / 60))) * 1000 > 0)
    {
        parameters.ESC1.write(((1 - ((speed - 20) / 100) - (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.radius * parameters.voltage * parameters.KVs)) * 90));
        parameters.ESC2.write(((1 - (speed / 100) - (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.radius * parameters.voltage * parameters.KVs)) * 90));
        parameters.ESC3.write(((1 + ((speed - 20) / 100) + (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.radius * parameters.voltage * parameters.KVs)) * 90));
        parameters.ESC4.write(((1 + (speed / 100) + (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.radius * parameters.voltage * parameters.KVs)) * 90));
    }
    return 0;
}

int rotate(struct Quadcopter parameters, int degree, int speed)
{
    signed long start_time = millis();
    while ((millis() - start_time) - (degree / 4 * ((speed / 100) * parameters.KVs * parameters.voltage * 6 + parameters.KVs * parameters.voltage * 6)) * 1000 > 0)
    {
        if (degree > 0)
        {
            parameters.ESC1.write(((1 - (speed / 100) - (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.radius * parameters.voltage * parameters.KVs)) * 90));
            parameters.ESC2.write(((1 - (speed / 100) - (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.radius * parameters.voltage * parameters.KVs)) * 90));
            parameters.ESC3.write(((1 - (speed / 100) - (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.radius * parameters.voltage * parameters.KVs)) * 90));
            parameters.ESC4.write(((1 - (speed / 100) - (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.radius * parameters.voltage * parameters.KVs)) * 90));
        }
        else if (degree < 0)
        {
            parameters.ESC1.write(((1 + (speed / 100) - (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.radius * parameters.voltage * parameters.KVs)) * 90));
            parameters.ESC2.write(((1 + (speed / 100) - (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.radius * parameters.voltage * parameters.KVs)) * 90));
            parameters.ESC3.write(((1 + (speed / 100) - (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.radius * parameters.voltage * parameters.KVs)) * 90));
            parameters.ESC4.write(((1 + (speed / 100) - (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.radius * parameters.voltage * parameters.KVs)) * 90));
        }
    }
    return 0;
}

int right(struct Quadcopter parameters, float distance, int speed, bool pitch = false)
{
    signed long start_time = millis();
    while ((millis() - start_time) - (distance / (4 * (speed / 100) * ((2 * PI * parameters.radius * parameters.KVs * parameters.voltage) / 60))) * 1000 > 0)
    {
        if (pitch)
        {
            parameters.ESC1.write(((1 - (speed / 100) - (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.radius * parameters.voltage * parameters.KVs)) * 90));
            parameters.ESC2.write(((1 - (speed / 100) - (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.radius * parameters.voltage * parameters.KVs)) * 90));
            parameters.ESC3.write(((1 + ((speed - 20) / 100) + (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.radius * parameters.voltage * parameters.KVs)) * 90));
            parameters.ESC4.write(((1 + ((speed - 20) / 100) + (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.radius * parameters.voltage * parameters.KVs)) * 90));
        }
    }
    if (!pitch)
    {
        rotate(parameters, 90.0, speed);
        forward(parameters, distance, speed);
    }
    return 0;
}

int left(struct Quadcopter parameters, float distance, int speed, bool pitch = false)
{
    signed long start_time = millis();
    while ((millis() - start_time) - (distance / (4 * (speed / 100) * ((2 * PI * parameters.radius * parameters.KVs * parameters.voltage) / 60))) * 1000 > 0)
    {
        if (pitch)
        {
            parameters.ESC1.write(((1 - ((speed - 20) / 100) - (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.radius * parameters.voltage * parameters.KVs)) * 90));
            parameters.ESC2.write(((1 - ((speed - 20) / 100) - (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.radius * parameters.voltage * parameters.KVs)) * 90));
            parameters.ESC3.write(((1 + (speed / 100) + (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.radius * parameters.voltage * parameters.KVs)) * 90));
            parameters.ESC4.write(((1 + (speed / 100) + (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.radius * parameters.voltage * parameters.KVs)) * 90));
        }
    }
    if (!pitch)
    {
        rotate(parameters, 90.0, speed);
        forward(parameters, distance, speed);
    }
    return 0;
}

int down(struct Quadcopter parameters, float distance)
{
    signed long start_time = millis();
    land_distance -= distance;
    while ((millis() - start_time) - (distance / (4 * (40 / 100) * ((2 * PI * parameters.radius * parameters.KVs * parameters.voltage) / 60)) * 1000 > 0))
    {
        parameters.ESC1.write(((1 + (40 / 100) - (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.radius * parameters.voltage * parameters.KVs)) * 90));
        parameters.ESC2.write(((1 + (40 / 100) - (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.radius * parameters.voltage * parameters.KVs)) * 90));
        parameters.ESC3.write(((1 - (40 / 100) + (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.radius * parameters.voltage * parameters.KVs)) * 90));
        parameters.ESC4.write(((1 - (40 / 100) + (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.radius * parameters.voltage * parameters.KVs)) * 90));
    }
    return 0;
}

int move_x(struct Quadcopter parameters, float distance, int speed)
{
    if (distance > 0)
    {
        forward(parameters, distance, speed);
    }
    else if (distance < 0)
    {
        backward(parameters, distance, speed);
    }
    else if (distance == 0)
    {
        levitate(parameters, 1000);
    }
    return 0;
}

int move_y(struct Quadcopter parameters, float distance, int speed, bool pitch = false)
{
    if (distance > 0)
    {
        right(parameters, distance, speed, pitch);
    }
    else if (distance < 0)
    {
        left(parameters, distance, speed, pitch);
    }
    else if (distance == 0)
    {
        levitate(parameters, 1000);
    }
    return 0;
}

int move_z(struct Quadcopter parameters, float distance, int speed, bool landed = true)
{
    if (distance > 0)
    {
        up(parameters, distance, speed, landed);
    }
    else if (distance < 0)
    {
        down(parameters, distance);
    }
    else if (distance == 0)
    {
        levitate(parameters, 1000);
    }
    return 0;
}

int land(struct Quadcopter parameters)
{
    if (land_distance > 0)
    {
        down(parameters, land_distance);
        land_distance = 0;
    }
    return 0;
}

int go_to(struct Quadcopter parameters, float x, float y, float z, int speed, bool pitch = false, bool landed = true)
{
    if (x == 0)
    {
        move_z(parameters, z, speed, landed);
        levitate(parameters, 1000);
        move_y(parameters, y, speed, pitch);
        levitate(parameters, 1000);
    }
    else if (y == 0)
    {
        move_z(parameters, z, speed, landed);
        levitate(parameters, 1000);
        move_x(parameters, x, speed);
        levitate(parameters, 1000);
    }
    else if (z == 0 && landed)
    {
        move_z(parameters, z, speed, landed);
        levitate(parameters, 1000);
        rotate(parameters, floor(acos((x + y) / (x * y))), speed);
        forward(parameters, sqrt(pow(x, 2) + pow(y, 2)), speed);
        levitate(parameters, 1000);
        move_z(parameters, z, speed, landed);
        levitate(parameters, 1000);
    }
    move_z(parameters, z, speed, landed);
    levitate(parameters, 1000);
    rotate(parameters, floor(acos((x + y) / (x * y))), speed);
    forward(parameters, sqrt(pow(x, 2) + pow(y, 2)), speed);
    levitate(parameters, 1000);
    return 0;
}
