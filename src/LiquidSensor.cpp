#include "LiquidSensor.h"

double LiquidSensor::read()
{
    int value = analogRead(pin);
    return map(static_cast<double>(value), 1023.0, 0.0, 0.0, 100.0);
}
