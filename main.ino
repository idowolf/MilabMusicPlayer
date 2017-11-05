void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
}


float arr[] = {130.81, 146.83, 164.81, 174.61, 196, 220, 246.94, 261.63};
bool dir;




void loop() {
  int sensorReading = analogRead(A0);
  int octaveSelector = analogRead(A1);
  int amplitudeSelector = analogRead(A2);
  int thisPitch = map(sensorReading, 720, 930, 0, 8);
  int octave  = map(octaveSelector, 0, 1024, 0, 3);
  int amplitude = map(amplitudeSelector, 0, 1024, 0, 51);
  if(thisPitch > 7) thisPitch = 7;
  if(thisPitch < 0) thisPitch = 0;
  note(arr[thisPitch]);
  playnote(pow(2, octave), amplitude);
  setx();
}

int curr = arr[0];
int target = arr[0];
int mstep;
double x = 0;

void setx() {
  x += 1 / PI;
}

void note(float key) {
  target = key;
  mstep = abs(curr - target) / 5;
}

void playnote(int octave, int amp) {
  double y = curr * octave + sin(x) * amp;
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

