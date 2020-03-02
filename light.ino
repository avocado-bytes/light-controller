
const int minimum = 400;
const int lightSensor = A0;
const int sensitivity = A1;
const int relayOutput = 7;
const byte bufferMax = 127;
byte buffer = 0;

void setup() {
  pinMode(lightSensor, INPUT);
  pinMode(sensitivity, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(relayOutput, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  delay(1000);
  int lightLevel = analogRead(lightSensor);
  int sensitivitySettings = analogRead(sensitivity);
  int limit = calculateLimit(lightLevel, sensitivitySettings, minimum);
  bool limitReached = lightLevel > limit;
  bool ON = buffer == bufferMax;
  updateBuffer(limitReached);
  printDebugMessage(lightLevel, limitReached, sensitivitySettings, limit, ON);
  if (ON) {
    digitalWrite(relayOutput, LOW);
  } else {
    digitalWrite(relayOutput, HIGH);
  }
}

/**
 * The buffer serves to smooth out oscillating light levels.
 * The light level might oscilate around the intended light level limit
 * and this might cause the light controller to flicker uncontrollably.
 * If the limit for light being lit has been reached a 1 is written to the 
 * right most bit of the buffer. Each cycle the buffer is right shifted which 
 * causes the byte value of the buffer to change. The light will only turn on if the 
 * byte has all of its bits set. Oscillating values will never allow 
 * the buffer to reach its max value and will not cause the light to turn on. 
 **/
void updateBuffer(bool limitReached) {
  if (limitReached) {
    buffer = buffer | B10000000;
  }
  buffer = buffer >> 1;
}

void printDebugMessage(int lightLevel, int limitReached,
                       int sensitivitySettings, int limit, bool on) {
  Serial.print("Light level:");
  Serial.println(lightLevel);
  Serial.print("Limit reached:");
  Serial.println(limitReached); 
  Serial.print("Light ON:");
  Serial.println(on); 
  Serial.print("Sensitivity: ");
  Serial.println(sensitivitySettings);
  Serial.print("New limit: ");
  Serial.println(limit);
  Serial.print("Buffer: ");
  Serial.println(buffer);
  Serial.println("-----------------------");
}

/**
 * The Arduino's ADC module has the value range of 0 - 1024. However to achieve more
 * sensitivity in the region of values that is typical for light conditions that occur
 * it has been limited to minimal value that is set as constant at the top of the program.
 **/
int calculateLimit(int lightLevel, int sensitivitySettings, int minimum) {
  float ratio = ((float)sensitivitySettings)/((float)1024);
  return ((1024 - minimum) * ratio) + minimum;
}
