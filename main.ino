void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
}


float arr[] = {130.81, 164.81, 196, 246.94, 261.63};
bool dir;




void loop() {
  int sensorReading = analogRead(A0);
  int octaveSelector = analogRead(A1);
  int amplitudeSelector = analogRead(A2);
  int thisPitch = map(sensorReading, 720, 930, 0, 5);
  int octave  = map(octaveSelector, 0, 1024, 0, 3);
  int amplitude = map(amplitudeSelector, 0, 1024, 1, 10);
  if(thisPitch > 4) thisPitch = 4;
  if(thisPitch < 0) thisPitch = 0;
  note(arr[thisPitch]);
  playnote(pow(2, octave));
  setx(amplitude / 10.0);
}

int curr = arr[0];
int target = arr[0];
int mstep;
double x = 0;

void setx(double amp) {
  x += amp / PI;
}

void note(float key) {
  target = key;
  mstep = abs(curr - target) / 5;
}

void playnote(int octave) {
  double y = curr * 4 + sin(x) * 10;
  Serial.println(y);
  tone(9,y, 100);
  if(curr > target && curr - mstep > target)
    curr -= mstep;
  else if(curr < target && curr + mstep < target)
    curr += mstep;
  else
    curr = target;
  delay(20); 
}

