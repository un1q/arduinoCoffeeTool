#include "melody.h"
#include "pitches.h"

#include <Arduino.h>

Melody::Melody(int buzz_pin, int* notes, int* notesDuration, int notesCount) : 
  buzz_pin(buzz_pin),
  notes(notes), 
  notesDuration(notesDuration), 
  notesCount(notesCount)
  {
}


Melody::~Melody() {
}

void Melody::play() {
  for (int thisNote = 0; thisNote < notesCount; thisNote++) {
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / notesDuration[thisNote];
    tone(buzz_pin, notes[thisNote], noteDuration);
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(buzz_pin);
  }
}
