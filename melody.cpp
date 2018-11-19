#include "melody.h"
#include "pitches.h"

#include <Arduino.h>

static int Melody::buzzPin;

static void Melody::setPin(int buzzPin) {
  Melody::buzzPin = buzzPin;
  pinMode(buzzPin, OUTPUT);
}

Melody::Melody(int* notes, int* notesDuration, int notesCount) : 
  notes(notes), 
  notesDuration(notesDuration), 
  notesCount(notesCount)
  {
}

Melody::~Melody() {
}

void Melody::play() {
  for (int thisNote = 0; thisNote < notesCount; thisNote++) {
    playNote(notes[thisNote], notesDuration[thisNote]);
  }
}

static void Melody::playNote(int note, int noteDuration) {
  int duration = 1000 / noteDuration;
  tone(buzzPin, note, duration);
  // to distinguish the notes, set a minimum time between them.
  // the note's duration + 30% seems to work well:
  int pauseBetweenNotes = duration * 1.30;
  delay(pauseBetweenNotes);
  noTone(buzzPin);
}

static void Melody::playTone(int freq, int duration) {
  tone(buzzPin, freq, duration);
}
