#include <Arduino.h>
#include <QCFA.h>
#include <Servo.h>

float land_distance = 0;

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

    while ((millis() - start_time) - (distance / (4 * (speed / 100) * ((2 * PI * parameters.propellers_radius * parameters.KVs * parameters.voltage) / 60))) * 1000 > 0)
    {
        parameters.ESC1.write(((1 - (speed / 100) - (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.propellers_radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.propellers_radius * parameters.voltage * parameters.KVs)) * 90));
        parameters.ESC2.write(((1 - (speed / 100) - (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.propellers_radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.propellers_radius * parameters.voltage * parameters.KVs)) * 90));
        parameters.ESC3.write(((1 + (speed / 100) + (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.propellers_radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.propellers_radius * parameters.voltage * parameters.KVs)) * 90));
        parameters.ESC4.write(((1 + (speed / 100) + (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.propellers_radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.propellers_radius * parameters.voltage * parameters.KVs)) * 90));
    }
    return 0;
}

int levitate(struct Quadcopter parameters, int time)
{
    parameters.mass = parameters.mass / 1000;
    parameters.propellers_radius = parameters.propellers_radius / 1000;

    signed long start_time = millis();
    while ((millis() - start_time) - time > 0)
    {
        parameters.ESC1.write(((1 - (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.propellers_radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.propellers_radius * parameters.voltage * parameters.KVs)) * 90));
        parameters.ESC2.write(((1 - (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.propellers_radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.propellers_radius * parameters.voltage * parameters.KVs)) * 90));
        parameters.ESC3.write(((1 + (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.propellers_radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.propellers_radius * parameters.voltage * parameters.KVs)) * 90));
        parameters.ESC4.write(((1 + (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.propellers_radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.propellers_radius * parameters.voltage * parameters.KVs)) * 90));
    }
    return 0;
}

int forward(struct Quadcopter parameters, float distance, int speed)
{
    parameters.mass = parameters.mass / 1000;
    parameters.propellers_radius = parameters.propellers_radius / 1000;
    signed long start_time = millis();
    while ((millis() - start_time) - (0.065 / (4 * (speed / 100) * ((2 * PI * parameters.propellers_radius * parameters.KVs * parameters.voltage) / 60))) * 1000 > 0)
    {
        parameters.ESC1.write(((1 - ((speed + 20) / 100) - (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.propellers_radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.propellers_radius * parameters.voltage * parameters.KVs)) * 90));
        parameters.ESC2.write(((1 - (speed / 100) - (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.propellers_radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.propellers_radius * parameters.voltage * parameters.KVs)) * 90));
        parameters.ESC3.write(((1 + ((speed + 20) / 100) + (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.propellers_radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.propellers_radius * parameters.voltage * parameters.KVs)) * 90));
        parameters.ESC4.write(((1 + (speed / 100) + (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.propellers_radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.propellers_radius * parameters.voltage * parameters.KVs)) * 90));
    }
    levitate(parameters, distance / (4 * (speed / 100) * ((2 * PI * parameters.propellers_radius * parameters.KVs * parameters.voltage) / 60)) * 1000);
    return 0;
}

int rotate(struct Quadcopter parameters, int degree, int speed)
{
    parameters.mass = parameters.mass / 1000;
    parameters.propellers_radius = parameters.propellers_radius / 1000;
    signed long start_time = millis();
    while ((millis() - start_time) - (abs(degree) / 2 * ((speed / 100) * parameters.KVs * parameters.voltage * 6 + parameters.KVs * parameters.voltage * 6)) * 1000 > 0)
    {
        if (degree > 0)
        {
            parameters.ESC1.write(((1 - ((speed + 20) / 100) - (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.propellers_radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.propellers_radius * parameters.voltage * parameters.KVs)) * 90));
            parameters.ESC2.write(((1 - ((speed + 20) / 100) - (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.propellers_radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.propellers_radius * parameters.voltage * parameters.KVs)) * 90));
            parameters.ESC3.write(((1 + (speed / 100) + (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.propellers_radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.propellers_radius * parameters.voltage * parameters.KVs)) * 90));
            parameters.ESC4.write(((1 + (speed / 100) + (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.propellers_radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.propellers_radius * parameters.voltage * parameters.KVs)) * 90));
        }
        else if (degree < 0)
        {
            parameters.ESC1.write(((1 - (speed / 100) - (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.propellers_radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.propellers_radius * parameters.voltage * parameters.KVs)) * 90));
            parameters.ESC2.write(((1 - (speed / 100) - (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.propellers_radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.propellers_radius * parameters.voltage * parameters.KVs)) * 90));
            parameters.ESC3.write(((1 + ((speed + 20) / 100) + (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.propellers_radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.propellers_radius * parameters.voltage * parameters.KVs)) * 90));
            parameters.ESC4.write(((1 + ((speed + 20) / 100) + (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.propellers_radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.propellers_radius * parameters.voltage * parameters.KVs)) * 90));
        }
    }
    return 0;
}

int backward(struct Quadcopter parameters, float distance, int speed, bool rotation = true)
{
    if (!rotation)
    {
        parameters.mass = parameters.mass / 1000;
        parameters.propellers_radius = parameters.propellers_radius / 1000;
        signed long start_time = millis();
        while ((millis() - start_time) - (0.065 / (4 * (speed / 100) * ((2 * PI * parameters.propellers_radius * parameters.KVs * parameters.voltage) / 60))) * 1000 > 0)
        {
            parameters.ESC1.write(((1 - ((speed - 20) / 100) - (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.propellers_radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.propellers_radius * parameters.voltage * parameters.KVs)) * 90));
            parameters.ESC2.write(((1 - (speed / 100) - (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.propellers_radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.propellers_radius * parameters.voltage * parameters.KVs)) * 90));
            parameters.ESC3.write(((1 + ((speed - 20) / 100) + (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.propellers_radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.propellers_radius * parameters.voltage * parameters.KVs)) * 90));
            parameters.ESC4.write(((1 + (speed / 100) + (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.propellers_radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.propellers_radius * parameters.voltage * parameters.KVs)) * 90));
        }
        levitate(parameters, distance / (4 * (speed / 100) * ((2 * PI * parameters.propellers_radius * parameters.KVs * parameters.voltage) / 60)) * 1000);
    }
    else if (rotation)
    {
        rotate(parameters, 180, speed);
        forward(parameters, distance, speed);
    }
    return 0;
}

int right(struct Quadcopter parameters, float distance, int speed, bool pitch = false)
{
    if (pitch)
    {
        parameters.mass = parameters.mass / 1000;
        parameters.propellers_radius = parameters.propellers_radius / 1000;
        signed long start_time = millis();
        while ((millis() - start_time) - (0.065 / (4 * (speed / 100) * ((2 * PI * parameters.propellers_radius * parameters.KVs * parameters.voltage) / 60))) * 1000 > 0)
        {
            parameters.ESC1.write(((1 - (speed / 100) - (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.propellers_radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.propellers_radius * parameters.voltage * parameters.KVs)) * 90));
            parameters.ESC2.write(((1 - (speed / 100) - (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.propellers_radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.propellers_radius * parameters.voltage * parameters.KVs)) * 90));
            parameters.ESC3.write(((1 + ((speed - 20) / 100) + (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.propellers_radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.propellers_radius * parameters.voltage * parameters.KVs)) * 90));
            parameters.ESC4.write(((1 + ((speed - 20) / 100) + (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.propellers_radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.propellers_radius * parameters.voltage * parameters.KVs)) * 90));
        }
        levitate(parameters, distance / (4 * (speed / 100) * ((2 * PI * parameters.propellers_radius * parameters.KVs * parameters.voltage) / 60)) * 1000);
    }
    else if (!pitch)
    {
        rotate(parameters, 90.0, speed);
        forward(parameters, distance, speed);
    }
    return 0;
}

int left(struct Quadcopter parameters, float distance, int speed, bool pitch = false)
{
    signed long start_time = millis();
    if (pitch)
    {
        parameters.mass = parameters.mass / 1000;
        parameters.propellers_radius = parameters.propellers_radius / 1000;
        while ((millis() - start_time) - (0.065 / (4 * (speed / 100) * ((2 * PI * parameters.propellers_radius * parameters.KVs * parameters.voltage) / 60))) * 1000 > 0)
        {
            parameters.ESC1.write(((1 - ((speed - 20) / 100) - (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.propellers_radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.propellers_radius * parameters.voltage * parameters.KVs)) * 90));
            parameters.ESC2.write(((1 - ((speed - 20) / 100) - (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.propellers_radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.propellers_radius * parameters.voltage * parameters.KVs)) * 90));
            parameters.ESC3.write(((1 + (speed / 100) + (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.propellers_radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.propellers_radius * parameters.voltage * parameters.KVs)) * 90));
            parameters.ESC4.write(((1 + (speed / 100) + (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.propellers_radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.propellers_radius * parameters.voltage * parameters.KVs)) * 90));
        }
        levitate(parameters, distance / (4 * (speed / 100) * ((2 * PI * parameters.propellers_radius * parameters.KVs * parameters.voltage) / 60)) * 1000);
    }
    else if (!pitch)
    {
        rotate(parameters, 90.0, speed);
        forward(parameters, distance, speed);
    }
    return 0;
}

int down(struct Quadcopter parameters, float distance)
{
    parameters.mass = parameters.mass / 1000;
    parameters.propellers_radius = parameters.propellers_radius / 1000;
    signed long start_time = millis();
    land_distance -= distance;
    while ((millis() - start_time) - (distance / (4 * (40 / 100) * ((2 * PI * parameters.propellers_radius * parameters.KVs * parameters.voltage) / 60)) * 1000 > 0))
    {
        parameters.ESC1.write(((1 + (40 / 100) - (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.propellers_radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.propellers_radius * parameters.voltage * parameters.KVs)) * 90));
        parameters.ESC2.write(((1 + (40 / 100) - (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.propellers_radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.propellers_radius * parameters.voltage * parameters.KVs)) * 90));
        parameters.ESC3.write(((1 - (40 / 100) + (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.propellers_radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.propellers_radius * parameters.voltage * parameters.KVs)) * 90));
        parameters.ESC4.write(((1 - (40 / 100) + (60 * sqrt((parameters.mass * 9.8) / (2 * 1.225 * PI * pow(parameters.propellers_radius, 2) * 0.23))) / (0.9 * PI * 2 * parameters.propellers_radius * parameters.voltage * parameters.KVs)) * 90));
    }
    return 0;
}

int move_x(struct Quadcopter parameters, float distance, int speed, bool rotation = false)
{
    if (distance > 0)
    {
        forward(parameters, distance, speed);
    }
    else if (distance < 0)
    {
        backward(parameters, distance, speed, !rotation);
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
        move_x(parameters, x, speed, pitch);
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

int stop(struct Quadcopter parameters)
{
    parameters.ESC1.write(90);
    parameters.ESC2.write(90);
    parameters.ESC3.write(90);
    parameters.ESC4.write(90);
}
