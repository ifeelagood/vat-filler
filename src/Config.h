#ifndef CONFIG_H
#define CONFIG_H
// speed for thingy 2.0
namespace Config
{
    constexpr int StepsPerRevolution = 200;
    constexpr float MaxSpeed = 5.0;
    constexpr float Acceleration = 5.0;
    constexpr float Speed = 2.0;
    constexpr long StepDelta = 100;
    constexpr float ThresholdUpper = 70.0f; // turn off if above (0 - 100)
    constexpr float ThresholdLower = 30.0f; // turn on if lower than (0-100)
    constexpr unsigned long LiquidInterval = 1000; // ms
};

#endif // CONFIG_H