#include <Arduino.h>
#include <AccelStepper.h>

#include "LiquidSensor.h"
#include "Pins.h"
#include "Config.h"


template <typename T>
constexpr long STEPS(T rpm) { return rpm * Config::StepsPerRevolution * Config::StepRatio; }

LiquidSensor sensor(Pins::LiquidSensor);
AccelStepper stepper(AccelStepper::DRIVER, Pins::DRV8825::STEP, Pins::DRV8825::DIR);
// state
unsigned long last_sensor_check = 0;
bool pump_active = false;

void initialiseStepper()
{
    pinMode(Pins::DRV8825::SLEEP, OUTPUT);
    pinMode(Pins::DRV8825::RESET, OUTPUT);

    digitalWrite(Pins::DRV8825::RESET, HIGH);


    // pinMode(Pins::DRV8825::DIR, OUTPUT);
    // pinMode(Pins::DR2V8825::STEP, OUTPUT);

    stepper.setMaxSpeed(STEPS(Config::MaxSpeed));
    stepper.setAcceleration(STEPS(Config::Acceleration));
    stepper.setSpeed(STEPS(Config::Speed));
}

void setPumpState(bool enabled)
{
    if (enabled)
    {
        stepper.setCurrentPosition(0L);
        stepper.move(STEPS(Config::RevolutionDelta));
    }
    else stepper.stop();

    digitalWrite(Pins::LED,  enabled ? HIGH : LOW);
    digitalWrite(Pins::DRV8825::SLEEP, enabled ? HIGH : LOW);
    // digitalWrite(Pins::DRV8825::RESET, enabled ? HIGH : LOW); // effectively resets
    delay(4); // t_wake=2 of DRV8825, see ds @ p7

    pump_active = enabled;
}

void setup()
{
    Serial.begin(9600);

    pinMode(Pins::LED, OUTPUT);
    pinMode(Pins::STOP, INPUT);

    initialiseStepper();
    setPumpState(false);
}

void loop()
{
    bool stop = digitalRead(Pins::STOP);
    if (stop)
    {
        if (pump_active) setPumpState(false);
        while (digitalRead(Pins::STOP) == HIGH)
        {
            digitalWrite(Pins::LED, HIGH);
            delay(500);
            digitalWrite(Pins::LED, LOW);
            delay(500);
        }

        if (pump_active) setPumpState(true);
    }

    long distance = stepper.distanceToGo();
    long position = stepper.currentPosition();

    // if pump is active, make sure its always targeting StepDelta
    if (pump_active)
    {
        constexpr long target_delta = STEPS(Config::RevolutionDelta);
        stepper.moveTo(position + target_delta - distance);
        stepper.run();
    }


    if (millis() - last_sensor_check >= Config::LiquidInterval)
    {
        last_sensor_check = millis();

        float liquid = sensor.read();
        bool liquid_low = liquid < Config::LiquidThreshold;

        if (liquid_low && !pump_active) setPumpState(true);
        if (!liquid_low && pump_active) setPumpState(false);
    }


}
