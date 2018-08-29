#include "arduinoFFT.h"

#define micPin 0

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
            curr = 0.95 * prev + 0.05 * x;
            return curr;
        }
};

// BUFFER THAT UPDATES ITSELF AND WILL GIVE YOU A ROLLING AVERAGE

class BufferAverage {
  public:
    BufferAverage(int N);
    ~BufferAverage();
    void updateB(float val);
    float averageB();
    void printB();

  private:
    int _NSAMPLES = 0;
    float* _buf = 0;
    int _bufIndex = 0;
    float _bufVal = 0;
    Filter myFilter;
};

BufferAverage::BufferAverage(int N) {
  _NSAMPLES = N;
  
  if (_buf != 0) {
    delete [] _buf;
  }
  _buf = new float[_NSAMPLES*2];

  for (int i = 0; i < _NSAMPLES*2; i++) {
    _buf[i] = 0.0;
  }
}

BufferAverage::~BufferAverage() {
  if (_buf != 0) {
    delete [] _buf;
  }
}

void BufferAverage::updateB(float val) {
  _buf[_bufIndex] = val;
  _buf[_bufIndex + _NSAMPLES] = val;
  _bufIndex += 1;
  if (_bufIndex > _NSAMPLES-1) {
    _bufIndex = 0;
  }
}

float BufferAverage::averageB() {
  float avg = 0;
  for (int i = _bufIndex + _NSAMPLES; i--; i > _bufIndex) {
    avg += _buf[i] / float(_NSAMPLES);
  }
  return avg;
}

void BufferAverage::printB() {
  Serial.println("\n\n BufferAverage::printB()");
  for (int i = 0; i < _NSAMPLES*2; i++) {
    if (i == _NSAMPLES) Serial.println();
    Serial.print(_buf[i]); Serial.print(", ");
  }
}


Filter myFilter;
int micVal = 0;
float micValFiltered = 0;
float micValFilteredPrev = 0;

void setup() {
  pinMode(micPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  micValFilteredPrev = micValFiltered;
  
  micVal = abs(analogRead(micPin)-512);
  micValFiltered = myFilter.step(micVal);

  Serial.println(micValFiltered);
}

