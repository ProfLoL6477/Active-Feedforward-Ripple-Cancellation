const int analogPin = 34;
const int dacPin = 25;

const float fs = 20000.0;
const float fc = 30.0;
const float alpha = exp(-2.0 * PI * fc / fs);

float u_prev = 0.0;
float y_prev = 0.0;
bool initialized = false;

void setup() {
  analogReadResolution(12);
}

void loop() {

  int raw = analogRead(analogPin);
  float measuredVoltage = (raw / 4095.0) * 3.3;
  float u = (3.6036 * measuredVoltage) - 0.468;

  if(u < 0) u = 0;

  if(!initialized) {
    u_prev = u;
    y_prev = 0.0;
    initialized = true;
  }

  float y = (u - u_prev) + alpha * y_prev;

  u_prev = u;
  y_prev = y;

  y = -y;

  if(!isfinite(y)) {
    y = 0.0;
    u_prev = u;
    y_prev = 0.0;
  }

  float dacVoltage = 1.65 + y;

  if(dacVoltage < 0) dacVoltage = 0;
  if(dacVoltage > 3.3) dacVoltage = 3.3;

  uint8_t dacValue = (dacVoltage / 3.3) * 255.0;

  dacWrite(dacPin, dacValue);
}
