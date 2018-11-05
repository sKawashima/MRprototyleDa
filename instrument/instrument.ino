#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

boolean debug = false;

boolean buttonA = false;
boolean buttonB = false;
int lastButton = 0; // A:1, B:2
boolean pushButton = false;

int sounds[] = { 53, 52, 53, 55, 53, 55, 57, 58, 59, 60, 57, 55, 53, 53, 62, 60, 53, 50, 58, 57, 55, 53 };
// 戦場のメリークリスマス
// 62, 64, 62, 57, 62, 62, 64, 62, 64, 67, 64, 62, 64, 62, 57, 60, 72, 71, 67, 64
// ようこそジャパリパークへ
// 53, 52, 53, 55, 53, 55, 57, 58, 59, 60, 57, 55, 53, 53, 62, 60, 53, 50, 58, 57, 55, 53
int soundsLength = sizeof(sounds) / sizeof(int);

int playSound = -1;

int acceleration_base = 0;
int acceleration_next = 0;
int bend = 0;

void setup() {
  MIDI.begin(1);
  MIDI.turnThruOff();
  pinMode(2, INPUT); // A
  pinMode(4, INPUT); // B
  if (debug) Serial.begin(9600);
}

void loop() {
  acceleration_next = analogRead(2);
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
    MIDI.sendNoteOn(sounds[playSound], 100, 1);
    // MIDI.sendNoteOn(sounds[playSound], map(analogRead(3), 0, 1023, 0, 127), 1);
    acceleration_base = acceleration_next;
  }
  if (!digitalRead(2) && !digitalRead(4)) {
    MIDI.sendNoteOff(sounds[playSound], 0, 1);
    acceleration_base = acceleration_next;
  }

  // pitch bend
  bend = (acceleration_next - acceleration_base) * 40;
  MIDI.sendPitchBend(bend, 1);

  // reset buttons
  buttonA = digitalRead(2);
  buttonB = digitalRead(4);

  delay(50);
}
