#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

boolean debug = false;

boolean buttonA = false;
boolean buttonB = false;
int lastButton = 0; // A:1, B:2
boolean pushButton = false;

int sounds[] = { 62, 64, 62, 57, 62, 62, 64, 62, 64, 67, 64, 62, 64, 62, 57, 60, 72, 71, 67, 64 };
int soundsLength = sizeof(sounds) / sizeof(int);

int playSound = -1;

int acceleration = 0;
int bend = 0;

void setup() {
  MIDI.begin(1);
  MIDI.turnThruOff();
  pinMode(2, INPUT); // A
  pinMode(4, INPUT); // B
  if (debug) Serial.begin(9600);
}

void loop() {
  // scan buttons
  pushButton = false;
  if (!buttonA && digitalRead(2)) {
    lastButton = 1;
    pushButton = true;
  }
  if (!buttonB && digitalRead(4)) {
    lastButton = 2;
    pushButton = true;
  }

  // play or stop sound
  if (pushButton) {
    MIDI.sendNoteOff(sounds[playSound], 0, 1);
    // next sound
    playSound++;
    if (playSound == soundsLength) playSound = 0;
    MIDI.sendNoteOn(sounds[playSound], 127, 1);
    acceleration = analogRead(2);
  }
  if (!digitalRead(2) && !digitalRead(4)) {
    MIDI.sendNoteOff(sounds[playSound], 0, 1);
  }

  // pitch bend
  bend = (analogRead(2) - acceleration) * 40;
  MIDI.sendPitchBend(bend, 1);

  // reset buttons
  buttonA = digitalRead(2);
  buttonB = digitalRead(4);

  delay(50);
}
