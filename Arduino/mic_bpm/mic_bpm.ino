#define micPin 0
#define sampling_period_ms 10

int micVal = 0;
int prevT = 0;
int T = 0;

void setup() {
  pinMode(micPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  micVal = analogRead(micPin);

  Serial.println(micVal);

  delay(sampling_period_ms);
}

