#include <AccelStepper.h>

AccelStepper stepper(AccelStepper::FULL4WIRE, 10, 8, 7, 5);

constexpr int E1 = 9;
constexpr int E2 = 6;

constexpr int spr = 200;



void setup() 
{
  pinMode(E1, OUTPUT);
  pinMode(E2, OUTPUT);

  digitalWrite(E1, HIGH);
  digitalWrite(E2, HIGH);

  // THESE ARE THE MOST IMPORTANT PARAMETERS. IF THESE ARE NOT SET CORRECTLY, IT WILL NOT WORK.
  stepper.setMaxSpeed(200);
  stepper.setAcceleration(100);
  stepper.setSpeed(150);
}

void loop() 
{
  stepper.moveTo(10000);
  stepper.runToPosition(); // 5000 / 200 = 25 revolutions

  stepper.setCurrentPosition(0);

}
