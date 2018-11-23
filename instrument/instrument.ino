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
// さくら
// 72, 75, 75, 72, 75, 75, 72, 70, 68, 80, 80, 82, 79, 77, 75, 73, 75, 77, 79, 80, 75, 72, 75, 73, 72, 70, 68, 70, 72, 75, 75, 77, 75, 75, 75, 75, 77, 80, 80, 82, 84, 82, 80, 77, 79, 80, 80, 75, 68, 70, 72, 68, 70, 68
// 蛍の光
// 60, 65, 65, 65, 69, 67, 65, 67, 69, 65, 65, 69, 72, 74, 74, 72, 69, 69, 65, 67, 65, 67, 69, 65, 62, 62, 60, 65
int soundsLength = sizeof(sounds) / sizeof(int);

int playSound = -1;

int acceleration_base = 0;
int acceleration_next = 0;
int acceleration_fillter[50];
int acceleration_fillterCount = 0;
int acceleration_fillterResult = 0;
float lowPassFillter_a = 0.5;

int bend = 0;

unsigned long last = 0;
unsigned long now = 0;

void setup() {
  MIDI.begin(1);
  MIDI.turnThruOff();
  pinMode(2, INPUT); // A
  pinMode(4, INPUT); // B
  initAcceleration_fillter();
  if (debug) Serial.begin(9600);
}

void loop() {
  now = millis();
  if (acceleration_fillterCount < 50) {
    acceleration_fillter[acceleration_fillterCount] = analogRead(2);
    acceleration_fillterCount++;
  }
  if (now - last > 50 && !debug) {
    fillterAcceleration(); // set acceleration_next
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
//      MIDI.sendNoteOn(sounds[playSound], 100, 1);
       MIDI.sendNoteOn(sounds[playSound], map(analogRead(3), 0, 1023, 0, 127), 1);
      acceleration_base = acceleration_next;
    }
    if (!digitalRead(2) && !digitalRead(4)) {
      MIDI.sendNoteOff(sounds[playSound], 0, 1);
    }

    // pitch bend
    bend = (acceleration_next - acceleration_base) * 40;
    MIDI.sendPitchBend(bend, 1);

    // reset buttons
    buttonA = digitalRead(2);
    buttonB = digitalRead(4);

    last = now;
  }
  if (now - last > 50 && debug) {
    fillterAcceleration();
    Serial.print(analogRead(2));
    Serial.print(", ");
    Serial.print(acceleration_next);
    Serial.print("\n");

    last = now;
  }
}

void fillterAcceleration () {
  acceleration_fillterResult = 0;
//  acceleration_base = acceleration_next;
  for (int i = 0; i < acceleration_fillterCount; i++) {
    acceleration_fillterResult += acceleration_fillter[i];
  }
  acceleration_fillterResult /= acceleration_fillterCount;
  acceleration_next = acceleration_fillterResult;
//  acceleration_next = acceleration_base * lowPassFillter_a + acceleration_fillterResult * (1 - lowPassFillter_a );

  initAcceleration_fillter();
}

void initAcceleration_fillter () {
  for (int i = 0; i < 50; i++) {
    acceleration_fillter[i] = -1;
  }
  acceleration_fillterCount = 0;
}
