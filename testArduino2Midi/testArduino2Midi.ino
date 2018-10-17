#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  MIDI.begin(1);
  MIDI.turnThruOff();
  pinMode(2, INPUT); // A
  pinMode(4, INPUT); // B
}

void loop() {
  if (digitalRead(2) == 1) {
    MIDI.sendNoteOn(60, 128, 1);
  } else {
    MIDI.sendNoteOff(60, 128, 1);
  }
}
