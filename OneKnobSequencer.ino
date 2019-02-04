/*
 * OneKnobSequencer
 * Rubens Bandelin 2019
 * One knob is better than two knobs
 */

int const led = 3;
int const btn = 2;
int const swtch = 1;
int const gate = 4;
int const clockIn = 0;

int stepSequence[16] = {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0};
int halfStep = 0;

bool recording = false;
bool clean = false;
bool state = false;
bool btnState = false;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(gate, OUTPUT);
  pinMode(swtch, INPUT);
  pinMode(btn, INPUT);
  pinMode(clockIn, INPUT);
  digitalWrite(gate, LOW);
  digitalWrite(led, LOW);
}

void loop() {
  if (halfStep%8 == 0) {
  }
  if ((digitalRead(swtch) == true) && (clean == false)) {
    clearSequence();
    clean = true;
    recording = true;
  }
  if ((digitalRead(swtch) == true) && (clean == true)) {
    recording = true;
  }
  if (digitalRead(swtch) == false) {
    recording = false;
    clean = false;
  }
  if (digitalRead(clockIn) == HIGH) {
    digitalWrite(led, HIGH);
    if (state == false) {
      sync();
      state = true;
    }
  }
  else if (digitalRead(clockIn) == LOW) {
    digitalWrite(led, LOW);
    state = false;
  }
  if (digitalRead(btn) == HIGH) {
    digitalWrite(led, HIGH);
    if (state == false) {
      recordSequence();
      btnState = true;
    }
  }
  else if (digitalRead(clockIn) == LOW) {
    digitalWrite(led, LOW);
    btnState = false;
  }
}

void recordSequence(){
  if (recording == true) {
    digitalWrite(led, HIGH);
    int pos = ((halfStep%16)-1);
    stepSequence[pos] = stepSequence[pos]? 0 : 1;
    if (stepSequence[pos] == 1) {
      digitalWrite(gate, LOW);
      digitalWrite(gate, HIGH);
    }
  }
}

void sync() {
  ++halfStep;
  digitalWrite(gate, LOW);
  if (stepSequence[((halfStep%16)-1)] == 1) {
    digitalWrite(gate, HIGH);
    digitalWrite(led, HIGH);
  }
  else if (stepSequence[((halfStep%16)-1)] == 0) {
    digitalWrite(gate, LOW);
    digitalWrite(led, LOW);
  }
}

void clearSequence() {
  for (int i = 0; i < 16; i++) {
    stepSequence[i] = 0;
  }
}
