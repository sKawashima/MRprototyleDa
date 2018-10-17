#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  MIDI.begin(1);
  MIDI.turnThruOff();
  pinMode(2, INPUT); // A
  pinMode(4, INPUT); // B
}

boolean buttonA = false;
boolean buttonB = false;
int lastButton = 0; // A:1, B:2
boolean switchButton = false;

int sounds = {60, 67, 64, 72, 71, 67, 64, 71, 69, 65, 64, 72, 71, 67, 64, 69, 67, 64, 60, 62, 64, 62, 67, 64, 62, 60, 62, 62, 64, 67, 64, 62, 60, 62, 64};
int soundsLength = sizeof(sounds);
int playSound = -1;

void loop() {
  // scan buttons
  switchButton = false;
  if (!buttonA && digitalRead(2)) {
    lastButton = 1;
    switchButton = true;
  }
  if (!buttonB && digitalRead(4)) {
    lastButton = 2;
    switchButton = true;
  }

  // play sound
  if (switchButton) {
    MIDI.sendNoteOff(sounds[playSound], 0, 1);
    // next sound
    playSound++;
    if (playSound == soundsLength) playSound = 0;
    MIDI.sendNoteOn(42, 127, 1);
  }

  // reset buttons
  buttonA = digitalRead(2);
  buttonB = digitalRead(4);
}
