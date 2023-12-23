#ifndef CONFIG_H
#define CONFIG_H

namespace Config
{
    constexpr int StepsPerRevolution =  200; // s / r
    constexpr float RevolutionDelta  =  1.0; // r
    constexpr float StepRatio        = 1.0;

    constexpr float MaxSpeed         = 20.0; // r / m
    constexpr float Acceleration     =  3.5; // r / m / s
    constexpr float Speed            =  6.0; // r / m


    constexpr float LiquidThreshold = 30.0; // 0 - 100
    constexpr unsigned long LiquidInterval = 2500; // ms
}

#endif // CONFIG_H