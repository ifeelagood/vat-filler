#ifndef PINS_H
#define PINS_H

namespace Pins
{

    class DRV8825
    {
    public:
        static const int SLEEP = 10;
        static const int STEP = 9;
        static const int DIR = 8;
    };

    class OLED
    {
    public:
        static const int SCK = A4;
        static const int SDA = A5;
    };

    class RotaryEncoder
    {
    public:
        static const int A = A2;
        static const int B = A3;
        static const int SW = 2;
    };

    static const int LiquidSensor = A0;

    static const int LED = 12;

    static const int STOP = 3;

} // Pins


#endif // PINS_H
