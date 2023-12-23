#ifndef CONFIG_H
#define CONFIG_H

namespace Config
{
    constexpr int StepsPerRevolution =  200; // spr
    constexpr long StepDelta         =  400; // s

    constexpr float MaxSpeed         = 20.0; // rpm
    constexpr float Acceleration     =  6.0; // rpm / s
    constexpr float Speed            =  5.0; // rpm

    constexpr float LiquidThreshold = 30.0; // 0 - 100
    constexpr unsigned long LiquidInterval = 2500; // ms
}

#endif // CONFIG_H