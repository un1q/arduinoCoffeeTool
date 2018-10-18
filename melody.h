#ifndef Melody_H_
#define Melody_H_

class Melody {
    int buzz_pin;
    int notesCount = 0;
    int *notes; //example: {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4} (include pitches.h)
    int *notesDuration; // note durations: 4 = quarter note, 8 = eighth note, etc.:

  public:
    Melody(int);
    ~Melody();
    void play();
};


#endif