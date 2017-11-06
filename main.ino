void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
}


float arr[] = {130.81, 164.81, 196, 246.94, 261.63};
bool dir;




void loop() {
  int sensorReading = analogRead(A0);
  Serial.println(sensorReading);
  int wavelengthSelector = analogRead(A1);
  int amplitudeSelector = analogRead(A2);
  int wavelength  = map(wavelengthSelector, 0, 1024, 0, 10);
  int amplitude = map(amplitudeSelector, 0, 1024, 0, 51);
  playnote(sensorReading, amplitude);
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

void playnote(int note, int amp) {
  double y = note * 1 + sin(x) * amp;
  Serial.println(y);
  tone(9,y, 100);
  delay(20); 
}

