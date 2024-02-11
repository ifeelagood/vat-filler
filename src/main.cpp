#include <Arduino.h>
#include <AccelStepper.h>

#include "LiquidSensor.h"
#include "Pins.h"
#include "Config.h"

LiquidSensor sensor(Pins::LiquidSensor);
AccelStepper stepper(AccelStepper::FULL4WIRE, Pins::L298N::I1, Pins::L298N::I2, Pins::L298N::I3, Pins::L298N::I4);

// state
unsigned long last_sensor_check = 0;
bool pump_active = false;

void initialiseStepper()
{
    stepper.setMaxSpeed(Config::MaxSpeed * Config::StepsPerRevolution);
    stepper.setAcceleration(Config::Acceleration * Config::StepsPerRevolution);
    stepper.setSpeed(Config::Speed * Config::StepsPerRevolution);
}

void setPumpState(bool enabled)
{
    int state = enabled ? HIGH : LOW;
    digitalWrite(Pins::L298N::E1, state);
    digitalWrite(Pins::L298N::E2, state);
    digitalWrite(Pins::LED, state);

    if (enabled) stepper.move(Config::StepDelta);
    else stepper.stop();

    pump_active = enabled;
}

void flashLED(long ms)
{
    delay(ms);
    digitalWrite(Pins::LED, HIGH);
    delay(ms);
    digitalWrite(Pins::LED, LOW);
}

void setup()
{
    Serial.begin(9600);

    pinMode(Pins::L298N::E1, OUTPUT);
    pinMode(Pins::L298N::E2, OUTPUT);
    pinMode(Pins::LED, OUTPUT);
    pinMode(Pins::EmergencyStop, INPUT_PULLUP);

    setPumpState(false);

    initialiseStepper();

    // startup flash
    for (int i = 0; i < 10; i++)
    {
        flashLED(100);
    }
}

void loop()
{
    // stop LOW = stop
    bool stop = !digitalRead(Pins::EmergencyStop);
    if (stop)
    {
        if (pump_active)
        {
            digitalWrite(Pins::L298N::E1, LOW);
            digitalWrite(Pins::L298N::E2, LOW);
        }
        while (digitalRead(Pins::EmergencyStop) == LOW)
        {
            flashLED(500);
        }
        if (pump_active)
        {
            digitalWrite(Pins::L298N::E1, HIGH);
            digitalWrite(Pins::L298N::E2, HIGH);
            digitalWrite(Pins::LED, HIGH); // as we are not calling set pump state
        }
    }

    long distance = stepper.distanceToGo();
    long position = stepper.currentPosition();

    // if pump is active, make sure its always targeting StepDelta
    if (pump_active)
    {
        if (distance < Config::StepDelta) stepper.moveTo(position + Config::StepDelta - distance);
        stepper.run();
    }


    if (millis() - last_sensor_check >= Config::LiquidInterval)
    {
        last_sensor_check = millis();

        float liquid = sensor.read();

        // if (!pump_active) setPumpState(true);
        if (liquid < Config::ThresholdLower && !pump_active) setPumpState(true); // turn pump on if falls lower than lower threshold
        if (liquid > Config::ThresholdUpper && pump_active) setPumpState(false); // turn pump off if greater than upper threshold
    }

}
