#define micPin 0

// LOW PASS FILTER

class Filter
{
    public:
        Filter()
        {
            v[0]=0.0;
        }
    private:
        float v[2];
    public:
        float step(float x) //class II 
        {
            v[0] = v[1];
            v[1] = (5.919070381841e-2 * x)
                + (  0.8816185924 * v[0]);
            return (v[0] + v[1]);
        }
};

// BUFFER THAT UPDATES ITSELF AND WILL GIVE YOU A ROLLING AVERAGE

class BufferAverage {
  public:
    BufferAverage(int N);
    ~BufferAverage();
    void updateB(int val);
    int averageB();
    void printB();

  private:
    int _NSAMPLES = 0;
    int* _buf = 0;
    int _bufIndex = 0;
    int _bufVal = 0;
    Filter myFilter;
};

BufferAverage::BufferAverage(int N) {
  _NSAMPLES = N;
  
  if (_buf != 0) {
    delete [] _buf;
  }
  _buf = new int[_NSAMPLES*2];

  for (int i = 0; i < _NSAMPLES*2; i++) {
    _buf[i] = 0;
  }
}

BufferAverage::~BufferAverage() {
  if (_buf != 0) {
    delete [] _buf;
  }
}

void BufferAverage::updateB(int val) {
  _buf[_bufIndex] = val;
  _buf[_bufIndex + _NSAMPLES] = val;
  _bufIndex += 1;
  if (_bufIndex > _NSAMPLES-1) {
    _bufIndex = 0;
  }
}

int BufferAverage::averageB() {
  float avg = 0;
  for (int i = _bufIndex + _NSAMPLES; i--; i > _bufIndex) {
    avg += float(_buf[i]) / float(_NSAMPLES);
  }
  return int(avg);
}

void BufferAverage::printB() {
  Serial.println("\n\n BufferAverage::printB()");
  for (int i = 0; i < _NSAMPLES*2; i++) {
    if (i == _NSAMPLES) Serial.println();
    Serial.print(_buf[i]); Serial.print(", ");
  }
}

BufferAverage micBuf(50);
int micVal = 0;

void setup() {
  pinMode(micPin, INPUT);
  Serial.begin(9600);
}

void loop() {

  micVal = abs(analogRead(micPin)-512);
  micBuf.updateB(micVal);
  Serial.println(micBuf.averageB());

}

