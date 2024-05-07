unsigned long micros_sp, ms = 0, currentTime, lastNotifyTime;
volatile int sp = 0, sz = 0;

void setup() {
  digitalWrite(13, HIGH);
  pinMode(3, INPUT_PULLUP);
  pinMode(7, OUTPUT);
  Serial.begin(115200);
  attachInterrupt(1, speedometr, RISING);
  digitalWrite(7, LOW);
}

void loop() {
  // SERIAL (TIMER) DEBUG
  currentTime = millis();
  if(currentTime - lastNotifyTime > 5000) {
    lastNotifyTime = currentTime;
    Serial.print(sp);
    Serial.println(" km/h");
  }
  // COUNTER
  if(sz <= 0) sp = 0;
  else sz--;
  // SPEED PWM
  if(sp > 5) {
    ms = 75750 / sp;
    digitalWrite(7, HIGH);
    delayMicroseconds(ms);
    digitalWrite(7, LOW);
    delayMicroseconds(ms);
  } else {
    digitalWrite(7, LOW);
  }
}

void speedometr() {
  sp = (1450000.0 / (micros() - micros_sp));
  if(sp > 160) sp = 160; // SPEED LIMIT CUT
  micros_sp = micros();
  sz = 30;
}
