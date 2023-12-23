#ifndef PINS_H
#define PINS_H


namespace Pins
{

    class DRV8825
    {
    public:
        static const int RESET = 11;
        static const int SLEEP = 10;
        static const int STEP = 9;
        static const int DIR = 8;
    };


    static const int LiquidSensor = A0;

    static const int LED = 12;

    static const int STOP = 3;

} // Pins


#endif // PINS_H
