void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
}


float arr[] = {130.81, 164.81, 196, 246.94, 261.63};
bool dir;




void loop() {
  int sensorReading = analogRead(A0);
  int wavelengthSelector = analogRead(A1);
  int amplitudeSelector = analogRead(A2);
  int thisPitch = map(sensorReading, 720, 930, 0, 5);
  int wavelength  = map(wavelengthSelector, 0, 1024, 0, 10);
  int amplitude = map(amplitudeSelector, 0, 1024, 0, 51);
  if(thisPitch > 4) thisPitch = 4;
  if(thisPitch < 0) thisPitch = 0;
  note(arr[thisPitch]);
  playnote(amplitude);
  setx(wavelength / 10.0);
}

int curr = arr[0];
int target = arr[0];
int mstep;
double x = 0;

void setx(double wavelength) {
  x += wavelength / PI;
}

void note(float key) {
  target = key;
  mstep = abs(curr - target) / 5;
}

void playnote(int amp) {
  double y = curr * 4 + sin(x) * amp;
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

