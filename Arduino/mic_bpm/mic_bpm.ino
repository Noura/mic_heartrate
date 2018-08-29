#define micPin 0
#define sampling_period_ms 20

// LOW PASS FILTER

class Filter
{
    public:
        Filter()
        {
            curr = 0.0;
            prev = 0.0;
        }
    private:
        float curr;
        float prev;
    public:
        float step(float x)
        {
            prev = curr;
            curr = 0.99 * prev + 0.01 * x;
            return curr;
        }
};


Filter myFilter;
int micVal = 0;
float micValFiltered = 0;

void setup() {
  pinMode(micPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  
  micVal = abs(analogRead(micPin)-512);
  micValFiltered = myFilter.step(micVal);

  Serial.println(micValFiltered);

  delay(sampling_period_ms);
}

