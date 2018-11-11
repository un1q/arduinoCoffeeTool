#ifndef MELODY_H_
#define MELODY_H_

// Plays melody.
// Be aware, it's not async and it starves main thread

class Melody {
    int buzz_pin;
    int notesCount = 0;
    int *notes; //example: {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4} (include pitches.h)
    int *notesDuration; // note durations: 4 = quarter note, 8 = eighth note, etc.:

  public:
    Melody::Melody(int buzz_pin, int* notes, int* notesDuration, int notesCount);
    ~Melody();
    void play();
};


#endif