#include <Arduino.h>

void setup()
{
}

void loop()
{
    v = (30 / 100) * ((2 * PI * radius * KVs * voltage) / 60)
}