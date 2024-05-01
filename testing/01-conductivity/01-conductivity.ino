

struct Config
{
  static constexpr int           ANALOGPIN  = A0;
  static constexpr unsigned long BAUDRATE   = 115200;
  static constexpr unsigned long PERIOD     = 250; // ms
  static constexpr unsigned      ITERATIONS = 200;
};

// time taken = PERIOD * ITERATIONS, 250 * 200 = 50 seconds


static unsigned long t_start = 0;
static unsigned i = 0;

void setup() 
{
   Serial.begin(Config::BAUDRATE);
   while (!Serial); // wait for serial 
   
   Serial.println("time,value");
   t_start = millis();
}

void loop() 
{
  if (i < Config::ITERATIONS)
  {
    unsigned long t_curr = millis() - t_start;
    int value = analogRead(Config::ANALOGPIN);
  
    Serial.print(t_curr);
    Serial.print(',');
    Serial.print(value);
    Serial.println();
  
    delay(Config::PERIOD);
    i++;
  }
  else
  {
    delay(1000);
  }
}
