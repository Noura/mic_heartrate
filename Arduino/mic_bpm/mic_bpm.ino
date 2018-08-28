#define micPin 0

// TODO average delta buffer class

// MIC INPUT BUFFER GLOBAL VARIABLES
// yes it's bad but... we're in a hurry
#define bufferN 30

int micBuffer[bufferN*2]; // duplicate buffer for averaging convenience
int micIndex = 0;   // current index we are updating in the micVals buffer
int micVal = 0;     // latest mic reading
int micValPrev = 0; // previous mic reading
int micDelta = 0;   // delta
int micDeltaAvg = 0; // average delta over previous buffer's worth of deltas


// BPM GLOBAL VARIABLES
// bb is short for babump
#define bbBufferN 30

int bbTimes[bbBufferN*2]; // time deltas (ms) of the "ba" and "bump" of the babump
int bbIndex = 0; // current index we are updating in the bbTimes buffer
int bbTime = 0;  // latest timestamp (ms)
int bbTimePrev = 0; // previous timestamp (ms)
int bbDelta = 0; // delta
int bbDeltaAvg = 0; // average delta over previous buffer's worth of deltas


// TRACKING UPS AND DOWNS
bool avgUP = false;

void setup() {
  pinMode(micPin, INPUT);
  Serial.begin(9600);

  for (int i = 0; i < bufferN*2; i++) {
    micBuffer[i] = 0;
  }

  for (int i = 0; i < bbBufferN*2; i++) {
    bbTimes[i] = 0;
  }
}

void loop() {
  micValPrev = micVal;
  micVal = abs(analogRead(micPin)-512);
  micDelta = micVal - micValPrev;
  updateBuffer(micDelta);
  micDeltaAvg = avgBuffer();
  //Serial.println(micDeltaAvg);
  Serial.println(micVal);

  if (micDeltaAvg < 0 && avgUP) {
    // things were going up previously, but now they are going down
    // so we think we are at the crest of the peak of ba or bump in babump
    avgUP = false;
    bbTimePrev = bbTime;
    bbTime = millis();
    bbDelta = bbTime - bbTimePrev;
    updateBBTimesBuffer(bbDelta);
    bbDeltaAvg = avgBBTimesBuffer();
    //Serial.println("*******************************************************");
    //Serial.print("bbDeltaAvg: ");Serial.println(bbDeltaAvg);  
  }
  avgUP = micDeltaAvg > 0 ? true : false;
}

// MIC INPUT BUFFER HELPER FUNCTIONS
// Tracking averaged deltas in absolute value of mic signal to find the "babump"
// The "babump" is marked by the amplitude of the mic signal going upward on avg

// mainting a duplicate buffer so it is easier to take a trailing average
void updateBuffer(int val) {
  micBuffer[micIndex] = val;
  micBuffer[micIndex + bufferN] = val;
  micIndex += 1;
  if (micIndex > bufferN-1) {
    micIndex = 0;
  }
}

// see how convenient it is to take the trailing average this way
int avgBuffer() {
  int sum = 0;
  for (int i = micIndex + bufferN; i--; i > micIndex) {
    sum += micBuffer[i];
  }
  return float(sum) / float(bufferN);
}

void printBuffer() {
  Serial.println("\n\n");
  for (int i = 0; i < bufferN*2; i++) {
    if (i == bufferN) Serial.println();
    Serial.print(micBuffer[i]); Serial.print(", ");
  }
}

// BABUMP BUFFER HELPER FUNCTIONS

void updateBBTimesBuffer(int val) {
  bbTimes[bbIndex] = val;
  bbTimes[bbIndex + bbBufferN] = val;
  bbIndex += 1;
  if (bbIndex > bbBufferN-1) {
    bbIndex = 0;
  }
}

int avgBBTimesBuffer() {
  float avg = 0;
  for (int i = bbIndex + bbBufferN; i--; i > bbIndex) {
    avg += float(bbTimes[i]) / float(bbBufferN);
  }
  return avg;
}

void printBBTimesBuffer() {
  Serial.println("\n\n");
  for (int i = 0; i < bbBufferN*2; i++) {
    if (i == bbBufferN) Serial.println();
    Serial.print(bbTimes[i]); Serial.print(", ");
  }
}
