#ifndef PINS_H
#define PINS_H

namespace Pins
{

    class L298N
    {
    public:
        // enable pins
        static const int E1 = 9;
        static const int E2 = 6;

        // current sensing pins
        // static const int CS1 = A1;
        // static const int CS2 = A2;

        // input pins
        static const int I1 = 10;
        static const int I2 = 8;
        static const int I3 = 7;
        static const int I4 = 5;
    };

    static const int LiquidSensor = A3;
    static const int LED = 4;
    static const int EmergencyStop = 3;


} // Pins


#endif // PINS_H
